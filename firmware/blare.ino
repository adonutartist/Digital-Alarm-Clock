#include <Adafruit_GFX.h>
#include <Adafruit_ST7789.h>
#include <SPI.h>
#include <WiFi.h>
#include <time.h>
// Fill in your WiFi network here before flashing
const char* WIFI_SSID = "WIFI NAME";
const char* WIFI_PASS = "WIFI PASS";
const char* NTP_SERVER = "pool.ntp.org";
const long GMT_OFFSET_SEC = 5 * 3600 + 1800; // Your timezone here
const int DAYLIGHT_OFFSET_SEC = 0;           // My country doesn't use DST but if your does please tune it accordingly

// --- HARDWARE PINS ---
#define TFT_SCL   8
#define TFT_SDA   10
#define TFT_RST   20
#define TFT_DC    21
#define TFT_CS    5
#define BUZZER_PIN 6
const int SW_PINS[] = {0, 1, 2, 3, 4}; // Menu, Hour, Min, AM/PM, AlarmToggle
class MyST7789 : public Adafruit_ST7789 {
public:
  MyST7789(SPIClass* spiObj, int8_t cs, int8_t dc, int8_t rst)
    : Adafruit_ST7789(spiObj, cs, dc, rst) {}
  void setOffsets(uint8_t col, uint8_t row) {
    _colstart = _colstart2 = col;
    _rowstart = _rowstart2 = row;
  }
};

MyST7789 tft(&SPI, TFT_CS, TFT_DC, TFT_RST);

// --- CLOCK VARIABLES ---
int currHour = 12, currMin = 0, currSec = 0;
bool currIsPM = false;

int alarmHour = 7, alarmMin = 30;
bool alarmIsPM = false;
bool alarmEnabled = false;

enum ClockState { MODE_NORMAL, MODE_SET_ALARM, MODE_RINGING };
ClockState currentState = MODE_NORMAL;

unsigned long lastTick = 0;
bool forceRedraw = true;

bool lastRawState[5]    = {HIGH, HIGH, HIGH, HIGH, HIGH}; 
bool debouncedState[5]  = {HIGH, HIGH, HIGH, HIGH, HIGH}; 
unsigned long lastDebounceTime[5] = {0, 0, 0, 0, 0};

// SIREN STATE (for the loud alarm beep)
unsigned long lastSirenStep = 0;
int sirenFreq = 1500;
int sirenDir = 1; // 1 = rising, -1 = falling
const int SIREN_MIN = 1200;
const int SIREN_MAX = 3200;
const int SIREN_STEP_MS = 8;   // how fast the pitch sweeps - lower = faster/more frantic
const int SIREN_STEP_HZ = 60;  // how big each pitch jump is

bool syncTimeWithWiFi() {
  tft.fillScreen(ST77XX_BLACK);
  tft.setTextSize(2);
  tft.setTextColor(ST77XX_WHITE);
  tft.setCursor(10, 25);
  tft.print("Connecting WiFi...");

  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASS);

  unsigned long startAttempt = millis();
  while (WiFi.status() != WL_CONNECTED && millis() - startAttempt < 15000) {
    delay(300);
  }

  if (WiFi.status() != WL_CONNECTED) {
    tft.fillScreen(ST77XX_BLACK);
    tft.setCursor(10, 25);
    tft.setTextColor(ST77XX_RED);
    tft.print("WiFi sync failed");
    delay(1500);
    WiFi.mode(WIFI_OFF);
    return false;
  }

  tft.fillScreen(ST77XX_BLACK);
  tft.setCursor(10, 25);
  tft.setTextColor(ST77XX_WHITE);
  tft.print("Fetching time...");

  configTime(GMT_OFFSET_SEC, DAYLIGHT_OFFSET_SEC, NTP_SERVER);

  struct tm timeinfo;
  bool got = getLocalTime(&timeinfo, 8000); // wait up to 8s for NTP response

  WiFi.disconnect(true);
  WiFi.mode(WIFI_OFF); // done with it, save power and avoid radio interference

  if (!got) {
    tft.fillScreen(ST77XX_BLACK);
    tft.setCursor(10, 25);
    tft.setTextColor(ST77XX_RED);
    tft.print("Time fetch failed");
    delay(1500);
    return false;
  }

  int hour24 = timeinfo.tm_hour;
  currMin = timeinfo.tm_min;
  currSec = timeinfo.tm_sec;
  currIsPM = (hour24 >= 12);
  currHour = hour24 % 12;
  if (currHour == 0) currHour = 12;

  tft.fillScreen(ST77XX_BLACK);
  tft.setCursor(10, 25);
  tft.setTextColor(ST77XX_WHITE);
  tft.print("Time synced!");
  delay(800);
  return true;
}

void setup() {
  Serial.begin(115200);

  pinMode(BUZZER_PIN, OUTPUT);
  for (int i = 0; i < 5; i++) {
    pinMode(SW_PINS[i], INPUT_PULLUP);
  }

  SPI.begin(TFT_SCL, -1, TFT_SDA, TFT_CS);
  tft.init(76, 284);
  tft.setOffsets(82, 18); 
  tft.invertDisplay(false); 
  tft.setRotation(1);
  tft.fillScreen(ST77XX_BLACK);

  // Startup beep
  int melody[] = {262, 330, 392, 523};
  for (int i = 0; i < 4; i++) { tone(BUZZER_PIN, melody[i], 100); delay(120); }

  syncTimeWithWiFi();
  forceRedraw = true;
}

void loop() {
  unsigned long currentMillis = millis();

  // 1. TIMEKEEPING (Ticks every 1000ms)
  if (currentMillis - lastTick >= 1000) {
    lastTick = currentMillis;

    currSec++;
    if (currSec >= 60) {
      currSec = 0;
      currMin++;
      if (currMin >= 60) {
        currMin = 0;
        currHour++;
        if (currHour == 12) currIsPM = !currIsPM;
        if (currHour > 12) currHour = 1;
      }
    }

    if (currentState == MODE_NORMAL && alarmEnabled &&
        currHour == alarmHour && currMin == alarmMin && currIsPM == alarmIsPM && currSec == 0) {
      currentState = MODE_RINGING;
      sirenFreq = SIREN_MIN;
      sirenDir = 1;
    }

    // Only force a per-second redraw for Normal (blinking colon) and Ringing.
    if (currentState != MODE_SET_ALARM) forceRedraw = true;
  }

  // 2. READ BUTTONS (Non-blocking Edge Detection)
  bool btnPressed[5] = {false, false, false, false, false};
  for (int i = 0; i < 5; i++) {
    bool reading = digitalRead(SW_PINS[i]);

    if (reading != lastRawState[i]) {
      lastDebounceTime[i] = currentMillis;
    }

    if ((currentMillis - lastDebounceTime[i]) > 50) {
      if (reading != debouncedState[i]) {
        debouncedState[i] = reading;
        if (debouncedState[i] == LOW) { 
          btnPressed[i] = true;
          if (currentState != MODE_RINGING) {
            tone(BUZZER_PIN, 1000, 30);
          }
        }
      }
    }

    lastRawState[i] = reading;
  }

  // 3. HANDLE LOGIC BASED ON STATE
  if (currentState == MODE_RINGING) {
    // Loud continuous siren sweep - no silent gaps, pitch rises/falls for urgency
    if (currentMillis - lastSirenStep >= SIREN_STEP_MS) {
      lastSirenStep = currentMillis;
      sirenFreq += sirenDir * SIREN_STEP_HZ;
      if (sirenFreq >= SIREN_MAX) { sirenFreq = SIREN_MAX; sirenDir = -1; }
      if (sirenFreq <= SIREN_MIN) { sirenFreq = SIREN_MIN; sirenDir = 1; }
      tone(BUZZER_PIN, sirenFreq); // no duration = keeps playing until changed/stopped
    }

    // Any button stops the alarm
    if (btnPressed[0] || btnPressed[1] || btnPressed[2] || btnPressed[3] || btnPressed[4]) {
      currentState = MODE_NORMAL;
      noTone(BUZZER_PIN);
      tone(BUZZER_PIN, 800, 60); // one quick confirmation beep that it's off
      forceRedraw = true;
    }
  }
  else {
    // Normal / Menu logic
    if (btnPressed[0]) { // MENU BUTTON - toggles Clock <-> Set Alarm
      if (currentState == MODE_NORMAL) currentState = MODE_SET_ALARM;
      else if (currentState == MODE_SET_ALARM) currentState = MODE_NORMAL;
      forceRedraw = true;
    }

    if (btnPressed[4] && currentState == MODE_NORMAL) { // ALARM TOGGLE
      alarmEnabled = !alarmEnabled;
      forceRedraw = true;
    }

    if (currentState == MODE_SET_ALARM) {
      if (btnPressed[1]) { alarmHour++; if(alarmHour == 12) alarmIsPM = !alarmIsPM; if(alarmHour > 12) alarmHour = 1; forceRedraw = true; }
      if (btnPressed[2]) { alarmMin = (alarmMin + 1) % 60; forceRedraw = true; }
      if (btnPressed[3]) { alarmIsPM = !alarmIsPM; forceRedraw = true; }
    }
  }

  // 4. DRAW DISPLAY
  if (forceRedraw) {
    forceRedraw = false;

    tft.fillRect(0, 0, 284, 76, ST77XX_BLACK);

    uint16_t labelColor = (currentState == MODE_SET_ALARM) ? ST77XX_WHITE : ST77XX_RED;

    tft.setTextSize(1);
    tft.setTextColor(labelColor);
    tft.setCursor(5, 5);

    if (currentState == MODE_NORMAL) tft.print("CLOCK");
    else if (currentState == MODE_SET_ALARM) tft.print("SETTING ALARM");
    else if (currentState == MODE_RINGING) tft.print("WAKE UP!!!");

    tft.setCursor(200, 5);
    if (alarmEnabled) tft.print("ALARM: ON");
    else tft.print("ALARM: OFF");

    // MAIN TIME DISPLAY
    int drawHour = (currentState == MODE_SET_ALARM) ? alarmHour : currHour;
    int drawMin  = (currentState == MODE_SET_ALARM) ? alarmMin : currMin;
    bool drawPM  = (currentState == MODE_SET_ALARM) ? alarmIsPM : currIsPM;

    tft.setTextSize(5);
    tft.setCursor(44, 18); 

    if (currentState == MODE_RINGING) {
      // Flicker red/white while ringing - slowed down further per request
      tft.setTextColor(((millis() / 700) % 2 == 0) ? ST77XX_RED : ST77XX_WHITE);
    } else if (currentState == MODE_SET_ALARM) {
      tft.setTextColor(ST77XX_RED); // swapped scheme for alarm setting
    } else {
      tft.setTextColor(ST77XX_WHITE); // normal + set time
    }

    if (drawHour < 10) tft.print(" ");
    tft.print(drawHour);

    if (currentState == MODE_NORMAL && (currSec % 2 == 0)) tft.print(":");
    else if (currentState != MODE_NORMAL) tft.print(":");
    else tft.print(" ");

    if (drawMin < 10) tft.print("0");
    tft.print(drawMin);

    tft.setTextSize(3);
    tft.setCursor(204, 26);
    tft.setTextColor(labelColor);
    if (drawPM) tft.print("PM");
    else tft.print("AM");
  }

  // While ringing, redraw every loop so the red/white flicker actually animates
  if (currentState == MODE_RINGING) forceRedraw = true;
}
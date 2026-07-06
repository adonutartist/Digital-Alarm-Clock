#include <Adafruit_GFX.h>
#include <Adafruit_ST7789.h>
#include <SPI.h>
#include <WiFi.h>
#include <Preferences.h>
#include <time.h>
const char* ssid = "YOUR_WIFI";
const char* password = "YOUR_PASSWORD";
const char* ntpServer = "pool.ntp.org";
const long gmtOffset_sec = 19800;      // IST
const int daylightOffset_sec = 0;
#define TFT_CS    7
#define TFT_RST   20
#define TFT_DC    21
#define TFT_SCLK  8
#define TFT_MOSI  10
Adafruit_ST7789 tft =
Adafruit_ST7789(
    TFT_CS,
    TFT_DC,
    TFT_MOSI,
    TFT_SCLK,
    TFT_RST
);
#define BTN_HOUR     0
#define BTN_MINUTE   1
#define BTN_AM       2
#define BTN_PM       3
#define BTN_SET      4
#define BUZZER 6
Preferences prefs;
int alarmHour = 6;
int alarmMinute = 0;
bool alarmPM = false;
bool editingAlarm = false;
bool alarmRinging = false;
int currentHour;
int currentMinute;
bool currentPM;
void setup()
{
    Serial.begin(115200);
    pinMode(BTN_HOUR,INPUT_PULLUP);
    pinMode(BTN_MINUTE,INPUT_PULLUP);
    pinMode(BTN_AM,INPUT_PULLUP);
    pinMode(BTN_PM,INPUT_PULLUP);
    pinMode(BTN_SET,INPUT_PULLUP);
    pinMode(BUZZER,OUTPUT);
    digitalWrite(BUZZER,LOW);
    setupDisplay();
    connectWiFi();
    syncTime();
    loadAlarm();
    Serial.println("Setup Complete!");
}
void loop()
{
    readButtons();
    updateClock();
    checkAlarm();
    updateAlarm();
    drawScreen();
    delay(20);
}
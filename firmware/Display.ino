bool wifiConnected = false;
void setupDisplay()
{
    tft.init(284, 76);
    tft.setColRowStart(82, 18);
    tft.setRotation(2);
    tft.fillScreen(ST77XX_BLACK);
    tft.setTextWrap(false);
    tft.setTextColor(ST77XX_WHITE);
    drawBootScreen();
    delay(1000);
}
void drawBootScreen()
{
    tft.fillScreen(ST77XX_BLACK);
    tft.setTextSize(2);
    tft.setCursor(20, 15);
    tft.print("BLARE");
    tft.setTextSize(1);
    tft.setCursor(20, 40);
    tft.print("Starting...");
}
void drawScreen()
{
    static unsigned long previousDraw = 0;
    if (millis() - previousDraw < 250)
        return;
    previousDraw = millis();
    tft.fillScreen(ST77XX_BLACK);
    drawCurrentTime();
    drawAlarmTime();
    drawWiFiStatus();
}
void drawCurrentTime()
{
    char buffer[20];
    struct tm timeinfo;
    if (!getLocalTime(&timeinfo))
    {
        tft.setCursor(10, 10);
        tft.setTextSize(2);
        tft.print("--:--");
        return;
    }
    strftime(buffer, sizeof(buffer), "%I:%M %p", &timeinfo);
    tft.setTextSize(3);
    tft.setCursor(10, 5);
    tft.print(buffer);
}
void drawAlarmTime()
{
    tft.setTextSize(2);
    tft.setCursor(10, 48);
    tft.print("Alarm ");
    if(editingAlarm)
    {
        if((millis()/500)%2)
            return;
    }
    if(alarmHour < 10)
        tft.print("0");
    tft.print(alarmHour);
    tft.print(":");
    if(alarmMinute < 10)
        tft.print("0");
    tft.print(alarmMinute);
    tft.print(" ");
    if(alarmPM)
        tft.print("PM");
    else
        tft.print("AM");
}
void drawWiFiStatus()
{
    tft.setTextSize(1);

    tft.setCursor(225, 5);

    if(wifiConnected)
        tft.print("WiFi");
    else
        tft.print("----");
}
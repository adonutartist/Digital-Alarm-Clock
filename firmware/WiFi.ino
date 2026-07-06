unsigned long previousReconnectAttempt = 0;
void connectWiFi()
{
    Serial.println();
    Serial.println("Connecting to WiFi...");
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);
    tft.fillScreen(ST77XX_BLACK);
    tft.setCursor(10, 20);
    tft.setTextSize(2);
    tft.print("Connecting...");
    int dots = 0;
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
        tft.print(".");
        dots++;
        if (dots > 3)
        {
            dots = 0;
            tft.fillRect(140, 20, 100, 20, ST77XX_BLACK);
            tft.setCursor(140, 20);
        }
    }
    wifiConnected = true;
    Serial.println();
    Serial.println("WiFi Connected I guess");
    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());
    tft.fillScreen(ST77XX_BLACK);
    tft.setCursor(10, 20);
    tft.print("Hopefully Connected");
    delay(1000);
}
void syncTime()
{
    configTime(
        gmtOffset_sec,
        daylightOffset_sec,
        ntpServer
    );
    Serial.println("Waiting for NTP...");
    struct tm timeinfo;
    while (!getLocalTime(&timeinfo))
    {
        delay(500);
        Serial.print(".");
    }
    Serial.println();
    Serial.println("Time Synced!");
}
void updateClock()
{
    if (WiFi.status() == WL_CONNECTED)
    {
        wifiConnected = true;
        return;
    }
    wifiConnected = false;
    if (millis() - previousReconnectAttempt < 10000)
        return;
    previousReconnectAttempt = millis();
    Serial.println("WiFi Lost xd");
    WiFi.disconnect();
    WiFi.begin(ssid, password);
    unsigned long start = millis();
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(250);
        if (millis() - start > 5000)
            return;
    }
    wifiConnected = true;
    syncTime();
    Serial.println("Reconnected lol");
}
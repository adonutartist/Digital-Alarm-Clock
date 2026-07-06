bool alarmTriggeredToday = false;
void setupAlarm()
{
    digitalWrite(BUZZER, LOW);
}
void checkAlarm()
{
    struct tm timeinfo;
    if (!getLocalTime(&timeinfo))
        return;
    int hour = timeinfo.tm_hour;
    int minute = timeinfo.tm_min;
    bool isPM = false;
    if(hour >= 12)
        isPM = true;
    int displayHour = hour % 12;
    if(displayHour == 0)
        displayHour = 12;
    if(hour == 0 && minute == 0)
    {
        alarmTriggeredToday = false;
    }
    if(alarmTriggeredToday)
        return;
    if(displayHour == alarmHour &&
       minute == alarmMinute &&
       isPM == alarmPM)
    {
        ringAlarm();
        alarmTriggeredToday = true;
    }
}

void ringAlarm()
{
    Serial.println("ALARM!");
    alarmRinging = true;
}
void stopAlarm()
{
    alarmRinging = false;
    digitalWrite(BUZZER, LOW);
    Serial.println("Alarm Stopped");
}
void updateAlarm()
{
    if(!alarmRinging)
        return;
    static unsigned long previousBeep = 0;
    static bool buzzerState = false;
    if(millis() - previousBeep >= 350)
    {
        previousBeep = millis();
        buzzerState = !buzzerState;
        digitalWrite(BUZZER, buzzerState);
    }
}
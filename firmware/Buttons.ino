bool lastHourState = HIGH;
bool lastMinuteState = HIGH;
bool lastAMState = HIGH;
bool lastPMState = HIGH;
bool lastSetState = HIGH;
unsigned long lastButtonPress = 0;
const unsigned long debounceDelay = 150;
void readButtons()
{
    if (millis() - lastButtonPress < debounceDelay)
        return;
    bool hourState = digitalRead(BTN_HOUR);
    bool minuteState = digitalRead(BTN_MINUTE);
    bool amState = digitalRead(BTN_AM);
    bool pmState = digitalRead(BTN_PM);
    bool setState = digitalRead(BTN_SET);
    if(hourState == LOW && lastHourState == HIGH)
    {
        if(editingAlarm)
        {
            alarmHour++;
            if(alarmHour > 12)
                alarmHour = 1;
            Serial.print("Alarm Hour: ");
            Serial.println(alarmHour);
        }
        lastButtonPress = millis();
    }
    if(minuteState == LOW && lastMinuteState == HIGH)
    {
        if(editingAlarm)
        {
            alarmMinute++;
            if(alarmMinute > 59)
                alarmMinute = 0;
            Serial.print("Alarm Minute: ");
            Serial.println(alarmMinute);
        }
        lastButtonPress = millis();
    }
    if(amState == LOW && lastAMState == HIGH)
    {
        if(editingAlarm)
        {
            alarmPM = false;
            Serial.println("Alarm AM");
        }
        lastButtonPress = millis();
    }
    if(pmState == LOW && lastPMState == HIGH)
    {
        if(editingAlarm)
        {
            alarmPM = true;
            Serial.println("Alarm PM");
        }
        lastButtonPress = millis();
    }
    if(setState == LOW && lastSetState == HIGH)
    {
        if(alarmRinging)
        {
            stopAlarm();
            lastButtonPress = millis();
        }
        else
        {
            editingAlarm = !editingAlarm;
            if(!editingAlarm)
            {
                saveAlarm();

                Serial.println("Alarm Saved");
            }
            else
            {
                Serial.println("Editing Alarm");
            }
            lastButtonPress = millis();
        }
    }
    lastHourState = hourState;
    lastMinuteState = minuteState;
    lastAMState = amState;
    lastPMState = pmState;
    lastSetState = setState;
}
void loadAlarm()
{
    prefs.begin("alarm", true);
    alarmHour = prefs.getInt("hour", 6);
    alarmMinute = prefs.getInt("minute", 0);
    alarmPM = prefs.getBool("pm", false);
    prefs.end();
    Serial.println("Alarm Loaded");
    Serial.print("Hour: ");
    Serial.println(alarmHour);
    Serial.print("Minute: ");
    Serial.println(alarmMinute);
    Serial.print("PM: ");
    Serial.println(alarmPM);
}
void saveAlarm()
{
    prefs.begin("alarm", false);
    prefs.putInt("hour", alarmHour);
    prefs.putInt("minute", alarmMinute);
    prefs.putBool("pm", alarmPM);
    prefs.end();

    Serial.println("Alarm Saved to Flash");
}
#define SCHEDULE_DEBUG 0

int valvesStatus[CNT_VALVES];
boolean manual = false;

void scheduleSetup(){
    // initilize all alarms (see Alarms.h file)
    initAlarms();
}

void scheduleTick(){
    
    // Execute this function once a second
    if(millis() % 1000 != 0) {
        return;
    }
        
    updateWeather();           // read weather data

    // do not operate if set to manual
    if(manual){
        return;   
    }

    // Turn off all valves status
    for(int i=0; i<CNT_VALVES; i++){
        valvesStatus[i] = HIGH;
    }
    
    // Check wich valves to open
    for(int i=0; i<CNT_ALARMS; i++){
        if(
            (hour() >= alarms[i].from_hour && hour() <= alarms[i].to_hour && // Check time
             (hour() < alarms[i].to_hour || minute() >= alarms[i].from_min && minute() <= alarms[i].to_min))
             &&
            (weather.temperature >= alarms[i].min_temp && weather.temperature <= alarms[i].max_temp && // Check weather
             weather.humidity >= alarms[i].min_hum && weather.humidity <= alarms[i].max_hum)
        ){
                Serial.print("Alarm ");
                Serial.print(i);
                Serial.print(" is on: Valve ");
                Serial.print(alarms[i].valve);
                Serial.println(" is open.");
               // turn on valve of alarm
               valvesStatus[alarms[i].valve] = LOW;
        }
    }

    // Open the valves if needed
    for(int i=0; i<CNT_VALVES; i++){
        // Do not write the same value several times
        if(digitalRead(valves[i]) != valvesStatus[i]){
            digitalWrite(valves[i], valvesStatus[i]);
        }
    }
    Serial.println(valvesStatus[0]);

    #if SCHEDULE_DEBUG
        // Display Time and Weather
        digitalClockDisplay();
        Serial.print(" ");
        digitalWeatherDisplay();
        Serial.println();
    #endif
}

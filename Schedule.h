#define INDICATOR_LIGHT 13
#define SCHEDULE_DEBUG 0

int valvesStatus[CNT_VALVES];

void scheduleSetup(){
    // initilize all alarms (see Alarms.h file)
    initAlarms();

    // Indicator light to show an open valve
    pinMode(INDICATOR_LIGHT, OUTPUT);
}

void scheduleTick(){
    //delay(2000);               // wait for a couple of seconds
    
    updateWeather();           // read weather data

    // Turn off all valves status
    for(int i=0; i<CNT_VALVES; i++){
        valvesStatus[i] = HIGH;
    }
    // turn off indicator light
    digitalWrite(INDICATOR_LIGHT, LOW);
    
    // Check wich valves to open
    for(int i=0; i<CNT_ALARMS; i++){
        if(
            (hour() >= alarms[i].from_hour && hour() <= alarms[i].to_hour && // Check time
             minute() >= alarms[i].from_min && minute() <= alarms[i].to_min) &&
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
               // turn on indicator light
               digitalWrite(INDICATOR_LIGHT, HIGH);
        }
    }

    // Open the valves if needed
    for(int i=0; i<CNT_VALVES; i++){
        digitalWrite(valves[i], valvesStatus[i]);
    }

    #if SCHEDULE_DEBUG
        // Display Time and Weather
        digitalClockDisplay();
        Serial.print(" ");
        digitalWeatherDisplay();
        Serial.println();
    #endif
}

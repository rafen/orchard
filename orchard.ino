#define CNT_VALVES 2

#include <Arduino.h>
#include <Time.h>
#include <Wire.h>
#include <DS1307RTC.h>
#include <dht11.h>

int valves[CNT_VALVES];

#include "OrchardClock.h"
#include "Weather.h"
#include "Alarms.h"
#include "Schedule.h"

void setup() {
    Serial.begin(9600);
    
    // Init Valves
    valves[0] = 2;    
    valves[1] = 3;    
    for(int i=0; i<CNT_VALVES; i++){
        pinMode(valves[i], OUTPUT);
        pinMode(valves[i], HIGH);
    }
    
    // Init Clock
    clockSetup();
    
    // Init Schedule
    scheduleSetup();
}

void loop() {
    scheduleTick();
}

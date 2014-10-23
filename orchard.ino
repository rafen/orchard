#define CNT_VALVES 2

#include <Arduino.h>
#include <Time.h>
#include <Wire.h>
#include <DS1307RTC.h>
#include <dht11.h>
#include <UIPEthernet.h> // Used for Ethernet

int valves[CNT_VALVES];

#include "OrchardClock.h"
#include "Weather.h"
#include "Alarms.h"
#include "Schedule.h"
#include "Web.h"

void setup() {    
    // Init Valves
    valves[0] = 4;    
    valves[1] = 5;    
    for(int i=0; i<CNT_VALVES; i++){
        pinMode(valves[i], OUTPUT);
        pinMode(valves[i], HIGH);
    }
    Serial.begin(9600);
    
    // Init Clock
    clockSetup();
    
    // Init Schedule
    scheduleSetup();
    
    webSetup();
}

void loop() {
    scheduleTick();
    webLoop();
}

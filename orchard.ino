#define CNT_VALVES 2

#include <Arduino.h>
#include <Time.h>
#include <Wire.h>
#include <DS1307RTC.h>

int valves[CNT_VALVES];

#include "OrchardClock.h"
#include "Alarms.h"
#include "Schedule.h"

void setup() {
    // Init Valves
    valves[0] = 11;
    valves[1] = 10;
    for(int i=0; i<CNT_VALVES; i++){
        pinMode(valves[i], OUTPUT);
        pinMode(valves[i], HIGH);
    }
    Serial.begin(9600);

    // Init Clock
    clockSetup();

    // Init Schedule
    scheduleSetup();
}

void loop() {
    scheduleTick();
}

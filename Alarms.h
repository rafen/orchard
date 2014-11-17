// Alarm definition
struct Alarm {
    int from_hour;
    int from_min;
    int to_hour;
    int to_min;

    int min_temp;
    int max_temp;
    
    int max_hum;
    int min_hum;
    
    int valve;
};

#define CNT_ALARMS 2
struct Alarm alarms[CNT_ALARMS];


void initAlarms(){
    
    /////////////////////
    // Setup for Alarm 0
    alarms[0].from_hour = 20;
    alarms[0].from_min = 5;
   
    alarms[0].to_hour = 20;
    alarms[0].to_min = 20;
   
    alarms[0].min_temp = 0;
    alarms[0].max_temp = 100;

    alarms[0].min_hum = 0;
    alarms[0].max_hum = 100;

    alarms[0].valve = 2;

    /////////////////////
    // Setup for Alarm 1
    alarms[1].from_hour = 14;
    alarms[1].from_min = 0;
    
    alarms[1].to_hour = 14;
    alarms[1].to_min = 8;
    
    alarms[1].min_temp = 26;
    alarms[1].max_temp = 100;

    alarms[1].min_hum = 0;
    alarms[1].max_hum = 80;

    alarms[1].valve = 4;

}

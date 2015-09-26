// Alarm definition
struct Alarm {
    int from_hour;
    int from_min;
    int to_hour;
    int to_min;
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
   
    alarms[0].valve = 11;

    /////////////////////
    // Setup for Alarm 1
    alarms[1].from_hour = 9;
    alarms[1].from_min = 0;
    
    alarms[1].to_hour = 9;
    alarms[1].to_min = 20;
    
    alarms[1].valve = 11;

}

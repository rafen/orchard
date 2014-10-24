// **** ETHERNET SETTING ****
byte mac[] = { 0x54, 0x34, 0x41, 0x30, 0x30, 0x31 };                                       
IPAddress ip(192, 168, 0, 116);                        
EthernetServer server(80);


void webSetup () {
  // start the Ethernet connection and the server:
  Ethernet.begin(mac, ip);
  server.begin();

  Serial.print("IP Address: ");
  Serial.println(Ethernet.localIP());
}

void printData(EthernetClient client){
    client.print("{");
    client.print("\"temp\":");
    client.print(weather.temperature);
    client.print(",");
    client.print("\"hum\":");
    client.print(weather.humidity);
    client.print(",");
    client.print("\"h\":");
    client.print(hour());
    client.print(",");
    client.print("\"m\":");
    client.print(minute());
    client.print(",");
    client.print("\"s\":");
    client.print(second());
    client.print(",");
    client.print("\"manual\":");
    client.print(manual);
    client.print(",");
    client.print("\"valves\":[");    
    for(int i=0; i<CNT_VALVES; i++){
        client.print("{\"id\":");
        client.print(i);
        client.print(",");
        client.print("\"status\":");
        client.print(valvesStatus[i]);
        client.print("}");
        if(i<CNT_VALVES-1){
            client.print(",");
        }
    }    
    client.print("]");
    client.print(",");
    client.print("\"alarms\":[");    
    for(int i=0; i<CNT_ALARMS; i++){
        client.print("{\"id\":");
        client.print(i);
        client.print(",");
        client.print("\"fh\":");
        client.print(alarms[i].from_hour);
        client.print(",");
        client.print("\"fm\":");
        client.print(alarms[i].from_min);
        client.print(",");
        client.print("\"th\":");
        client.print(alarms[i].to_hour);
        client.print(",");
        client.print("\"tm\":");
        client.print(alarms[i].to_min);
        client.print(",");
        client.print("\"valve\":");
        client.print(alarms[i].valve);
        client.print(",");
        client.print("\"mint\":");
        client.print(alarms[i].min_temp);
        client.print(",");
        client.print("\"maxt\":");
        client.print(alarms[i].max_temp);
        client.print(",");
        client.print("\"minh\":");
        client.print(alarms[i].min_hum);
        client.print(",");
        client.print("\"maxh\":");
        client.print(alarms[i].max_hum);
        client.print("}");
        if(i<CNT_ALARMS-1){
            client.print(",");
        }
    }    
    client.print("]");
    client.print("}");
}


void webLoop () {
  // listen for incoming clients
  EthernetClient client = server.available();
  size_t size;
  
  if (client) 
  {  
    while (client.connected()) 
    {
      if (size = client.available()) 
      {
          for(int i=0;i<size;i++){
              char c = client.read();
              processIncomingByte(c);
          }
        printData(client);
        break;
      } 
    }

    // give the web browser time to receive the data
    delay(10);

    // close the connection:
    client.stop();
  }
}

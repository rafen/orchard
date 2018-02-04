#include <DHT.h>
#include <DHT_U.h>

#define DEBUG 1

// Relays
#define RELAY_K1 8
#define RELAY_K2 9
#define RELAY_K3 10
#define RELAY_K4 11

// Temp and hum
#define DHTPIN 7
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);  


void setup() {
  #if DEBUG
    Serial.begin(9600);
  #endif

  // Set output ports
  pinMode(RELAY_K1, OUTPUT);
  pinMode(RELAY_K2, OUTPUT);
  pinMode(RELAY_K3, OUTPUT);
  pinMode(RELAY_K4, OUTPUT);

  // initial state
  digitalWrite(RELAY_K1, HIGH);
  digitalWrite(RELAY_K2, HIGH);
  digitalWrite(RELAY_K3, HIGH);
  digitalWrite(RELAY_K4, HIGH);  

  // Temp and humidity
  dht.begin();
}

void loop() {
    // Esperamos 5 segundos entre medidas
  delay(5000);
  print_temp();
  print_hum();
}

void print_temp() {
  float t = dht.readTemperature();

  if (isnan(t)) {
    #if DEBUG
      Serial.println("Error reading DHT11");
    #endif
    return;
  }
  
  #if DEBUG
    Serial.print("T: ");
    Serial.print(t);
    Serial.print(" - ");
  #endif
}

void print_hum() {
  float h = dht.readHumidity();

  if (isnan(h)) {
    #if DEBUG
      Serial.println("Error reading DHT11");
    #endif
    return;
  }

  #if DEBUG
    Serial.print("H: ");
    Serial.print(h);
    Serial.println("");
  #endif
}


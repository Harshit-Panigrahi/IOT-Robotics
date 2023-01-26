#include "DHT.h"

#define DHTPIN 26
#define DHTTYPE DHT11 

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("DHT11 Sensor");
  dht.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read data");
    return;
  }
  Serial.print("Humidity: ");
  Serial.print(h);
  Serial.print(", Temperature: ");
  Serial.println(t);
  delay(1000);
}

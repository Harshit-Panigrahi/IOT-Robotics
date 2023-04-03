#include <WiFi.h>
#include <WiFiClient.h>
#include <Adafruit_BMP085.h>
#include "DHT.h"

#define DHT_PIN 21
#define DHT_TYPE DHT11
DHT dht(DHT_PIN, DHT_TYPE);

#define WLAN_SSID "virusnet"
#define WLAN_PASS "air@6999"

Adafruit_BMP085 bmp;

void setup() {
  Serial.begin(9600);
  
  WiFi.begin(WLAN_SSID, WLAN_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print("*");
    delay(500);
  }
  Serial.println("\nWifi has been connected.");
  Serial.print("IP Addr: ");
  Serial.println(WiFi.localIP());

  if (!bmp.begin()) {
    Serial.println("BMP180 Sensor not found");
    while (1) {}
  }

  dht.begin();
}

void loop() {
  if (WiFi.status() == WL_CONNECTED) {
    WiFiClient cli;
    p = bmp.readPressure();
    t = bmp.readTemperature();
    a = bmp.readAltitude();
    Serial.print("\nPressure: ");
    Serial.println(p);
    Serial.print("Temperature: ");
    Serial.println(t);
    Serial.print("Altitude: ");
    Serial.println(a);
    
    float h = bmp.readHumidity();
    if (isnan(h)) {
      Serial.print("Failed to read himidity");    
      return;
    } else {
      Serial.print("Humidity: ");
      Serial.println(h);
    }
  }
  else Serial.println("WiFi disconnected");
}

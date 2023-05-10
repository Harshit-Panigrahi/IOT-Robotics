#include <DHT.h>
#include <WiFi.h>
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"

DHT dht(5, DHT11);

#define WLAN_SSID "virusnet"
#define WLAN_PASS "air@6999"
#define AIO_USERNAME "harshit08"
#define AIO_KEY "aio_srvu80ym9ldgBmlp8pIBq5tvdhwN"

WiFiClient client;
Adafruit_MQTT_Client mqtt(&client, "io.adafruit.com", 1883, AIO_USERNAME, AIO_KEY);
Adafruit_MQTT_Publish tempC = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/temp-c");
Adafruit_MQTT_Publish tempF = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/temp-f");
Adafruit_MQTT_Publish tempK = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/temp-k");
Adafruit_MQTT_Publish humidity = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/humidity");
Adafruit_MQTT_Publish dewPoint = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/dew-point");
Adafruit_MQTT_Subscribe red = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/out.red");
Adafruit_MQTT_Subscribe green = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/out.green");
Adafruit_MQTT_Subscribe blue = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/out.blue");

// channel
const byte r = 0;
const byte g = 1;
const byte b = 2;

void MQTT_Connect() {
  int8_t ret;  // Stop if already connected.
  if (mqtt.connected()) {
    return;
  }
  Serial.print("\nConnecting to MQTT... ");
  ret = mqtt.connect()
  while (ret != 0) {
    Serial.print("*");
    mqtt.disconnect();
    delay(3000);
  }
  Serial.println("\nMQTT Connected");
}

void subData(){
  Adafruit_MQTT_Subscribe *sub;
  while((sub = mqtt.readSubscription(3000))){
    int rRead, gRead, bRead;
    if (sub = &red) {
      rRead = atoi((char *)red.lastread);
    } if (sub = &green) {
      gRead = atoi((char *)green.lastread);
    } if (sub = &blue) {
      bRead = atoi((char *)blue.lastread);
    }
    ledcWrite(r, rRead);
    ledcWrite(g, gRead);
    ledcWrite(b, bRead);
  }
}

void setup(){
  Serial.begin(115200);

  ledcAttachPin(21, r);  
  ledcAttachPin(22, g);
  ledcAttachPin(23, b);
  ledcSetup(r, 5000, 8);
  ledcSetup(g, 5000, 8);
  ledcSetup(b, 5000, 8);
  ledcWrite(r, 0);
  ledcWrite(g, 0);
  ledcWrite(b, 0);

  // WiFi
  WiFi.begin(WLAN_SSID, WLAN_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print("•");
    delay(500);
  }
  Serial.println("\nWifi connected. IP Addr:");
  Serial.println(WiFi.localIP());

  //MQTT
  mqtt.subscribe(&red);
  mqtt.subscribe(&green);
  mqtt.subscribe(&blue);

  dht.begin();
}

void loop(){
  //Read data
  float h = dht.readHumidity();
  float c = dht.readTemperature();
  delay(2000);
  if (isnan(h) or isnan(c)) {
    Serial.println("Failed to read data");
    return;
  }
  float f = (c * 1.8) + 32;
  float k = c + 273.15;
  float dp = c - ((100 - h) / 5);
  
  //  print all the values
  /*Serial.print("Temperature(C): ");
  Serial.println(c);
  Serial.print("Temperature(F): ");
  Serial.println(f);
  Serial.print("Temperature(K): ");
  Serial.println(k);
  Serial.print("Humidity (%): ");
  Serial.println(h);
  Serial.print("Dew Point (C): ");
  Serial.println(dp);
  Serial.println("************");*/

  MQTT_Connect();

  // Publish values
  if (!tempC.publish(c)){
    Serial.println("Publish temp-c failed");
  } if (!tempF.publish(f)){
    Serial.println("Publish temp-f failed");
  } if (!tempK.publish(k)){
    Serial.println("Publish temp-k failed");
  } if (!humidity.publish(h)){
    Serial.println("Publish humidity failed");
  } if (!dewPoint.publish(dp)){
    Serial.println("Publish dew-point failed");
  }
  // Set RGB Led
  subData();
}

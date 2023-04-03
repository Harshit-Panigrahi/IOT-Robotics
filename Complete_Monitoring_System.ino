#include <WiFi.h>
#include <Adafruit_BMP085.h>
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"

// MQTT: Message Queue Telemetry Transport

#define AIO_SERVER "io.adafruit.com"
#define AIO_SERVER_PORT 1883
#define AIO_USERNAME "harshit08"
#define AIO_KEY "aio_srvu80ym9ldgBmlp8pIBq5tvdhwN"

#define WLAN_SSID "virusnet"
#define WLAN_PASS "air@6999"

#define PREAMBLE "/feeds/"
#define TPATH "Temperature"
#define PPATH "Pressure"
#define SPATH "Room Light"
const char TEMP_FEED[] PROGMEM = AIO_USERNAME PREAMBLE TPATH;
const char PRESS_FEED[] PROGMEM = AIO_USERNAME PREAMBLE PPATH;
const char LIGHT_FEED[] PROGMEM = AIO_USERNAME PREAMBLE SPATH;

WiFiClient client;
Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, AIO_SERVER_PORT, AIO_USERNAME, AIO_KEY);
Adafruit_MQTT_Publish temperature = Adafruit_MQTT_Publish(&mqtt, TEMP_FEED);
Adafruit_MQTT_Publish pressure = Adafruit_MQTT_Publish(&mqtt, PRESS_FEED);
Adafruit_MQTT_Subscribe roomlight = Adafruit_MQTT_Subscribe(&mqtt, LIGHT_FEED);

void MQTT_Connect() {
  int8_t ret;  // Stop if already connected.
  if (mqtt.connected()) {
    return;
  }
  Serial.print("Connecting to MQTT... ");
  while ((ret = mqtt.connect()) != 0) {
    // connect will return 0 for connected
    Serial.println(mqtt.connectErrorString(ret));
    Serial.println("Retrying MQTT connection in 5 seconds...");
    mqtt.disconnect();
    delay(5000);  // wait 5 seconds
  }
  Serial.println("MQTT Connected!");
}

const int led = 5;
float p, q;
String str1;
Adafruit_BMP085 bmp;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(led, OUTPUT);
  digitalWrite(led, LOW);
  WiFi.begin(WLAN_SSID, WLAN_PASS);
  Serial.println();
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print("*");
    delay(500);
  }
  Serial.println("\nWifi has been connected.");
  Serial.print("IP Addr: ");
  Serial.println(WiFi.localIP());
  mqtt.subscribe(&roomlight);
  if (!bmp.begin()) {
    Serial.println("BMP180 Sensor not found");
    while (1) {}
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  p = bmp.readPressure();
  q = bmp.readTemperature();
  delay(100);
  Serial.print("\nPressure: ");
  Serial.println(p);
  Serial.print("Temperature: ");
  Serial.println(q);

  MQTT_Connect();
  Serial.println("Connected");

  Adafruit_MQTT_Subscribe *subscription = mqtt.readSubscription(1000);
  while(subscription) {
    Serial.println("In loop");
    str1 = (char*) roomlight.lastread;
    Serial.println(str1);
    if (subscription == &roomlight) {
      if (str1 == "ON") {
        digitalWrite(led, HIGH);
      }
      if (str1 == "OFF") {
        digitalWrite(led, LOW);
      }
    }
    if (!pressure.publish(p)) {
      Serial.println("Pressure level failed");
    }
    if (!temperature.publish(q)) {
      Serial.println("Temperature level failed");
    }
  }
  if (!subscription) {
    Serial.println("Subscription undefined");
  }
}

#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include <ESPmDNS.h>

const char* ssid = "virusnet_5G";
const char* password = "air@6999";

String button = "<html><body id='body1' style='height:100px; width:100px'>";
WebServer server(80);

void handleRoot() {
  server.send(200, "text/html", button);
}

void handleNotFound() {
  String msg = "Resource not found\n\nuri: ";
  msg += server.uri();
  msg += "\nmethod: ";
  msg += (server.method() == HTTP_GET) ? "GET" : "POST";
  msg += "\nargs: ";
  msg += server.args();
  server.send(404, "text/plain", msg);
}

const int LED1 = 33;
const int BUZZER1 = 32;

void setup() {
  // put your setup code here, to run once:
  pinMode(LED1, OUTPUT);
  pinMode(BUZZER1, OUTPUT);
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }
  Serial.print("\nConnected to: ");
  Serial.println(ssid);
  Serial.print("IP Addr: ");
  Serial.println(WiFi.localIP());

  if (MDNS.begin("esp32")) {
    Serial.println("MDNS responder working");
  }
  
  server.on("/", handleRoot);
  server.on("/roomLight/on", []() {
    server.send(200, "text/html", button);
    digitalWrite(LED1, HIGH);
  });
  server.on("/roomLight/off", []() {
    server.send(200, "text/html", button);
    digitalWrite(LED1, LOW);
  });
  server.on("/roomBuzzer/on", []() {
    server.send(200, "text/html", button);
    digitalWrite(BUZZER1, HIGH);
  });
  server.on("/roomBuzzer/off", []() {
    server.send(200, "text/html", button);
    digitalWrite(BUZZER1, LOW);
  });
  server.onNotFound(handleNotFound);
  server.begin();
  Serial.println("Server has started");
  digitalWrite(LED1, LOW);
  digitalWrite(BUZZER1, LOW);
}

void loop() {
  // put your main code here, to run repeatedly:
  server.handleClient();
}

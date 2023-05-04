#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include <ESPmDNS.h>

const char* ssid = "virusnet";
const char* password = "air@6999";

String body = "<html><body id='body1' style='height:100px; width:100px'>";
WebServer server(80);

void handleNotFound() {
  String msg = "Resource not found\n\nuri: ";
  msg += server.uri();
  msg += "\nmethod: ";
  msg += (server.method() == HTTP_GET) ? "GET" : "POST";
  msg += "\nargs: ";
  msg += server.args();
  server.send(404, "text/plain", msg);
}

#define r 0
#define g 1
#define b 2

void setup() {
  ledcAttachPin(21, r);
  ledcAttachPin(22, g);
  ledcAttachPin(23, b);
  ledcSetup(r, 5000, 8);
  ledcSetup(g, 5000, 8);
  ledcSetup(b, 5000, 8);
  
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(100);
  }
  Serial.print("\nConnected to: ");
  Serial.println(ssid);
  Serial.print("IP Addr: ");
  Serial.println(WiFi.localIP());

  if (MDNS.begin("esp32")) {
    Serial.println("MDNS responder working");
  }

  server.onNotFound(handleNotFound);
  server.on("/", []() {
    body += "<a href='/red'><button>Red</button></a>";
    body += "<a href='/green'><button>Green</button></a>";
    body += "<a href='/blue'><button>Blue</button></a>";
    body += "<a href='/cyan'><button>Cyan</button></a>";
    body += "<a href='/magenta'><button>Magenta</button></a>";
    body += "<a href='/yellow'><button>Yellow</button></a></body>";
    body += "<a href='/white'><button>White</button></a></body>";
    body += "<a href='/off'><button>Off</button></a></body>";
    server.send(200, "text/html", body);
  });
  server.on("/red", []() {
    ledcWrite(r, 255);
    ledcWrite(g, 0);
    ledcWrite(b, 0);
  });
  server.on("/green", []() {
    ledcWrite(r, 0);
    ledcWrite(g, 255);
    ledcWrite(b, 0);
  });
  server.on("/blue", []() {
    ledcWrite(r, 0);
    ledcWrite(g, 0);
    ledcWrite(b, 255);
  });
  server.on("/cyan", []() {
    ledcWrite(r, 0);
    ledcWrite(g, 255);
    ledcWrite(b, 255);
  });
  server.on("/magenta", []() {
    ledcWrite(r, 255);
    ledcWrite(g, 0);
    ledcWrite(b, 255);
  });
  server.on("/yellow", []() {
    ledcWrite(r, 255);
    ledcWrite(g, 255);
    ledcWrite(b, 0);
  });
  server.on("/white", []() {
    ledcWrite(r, 255);
    ledcWrite(g, 255);
    ledcWrite(b, 255);
  });
  server.on("/off", []() {
    ledcWrite(r, 0);
    ledcWrite(g, 0);
    ledcWrite(b, 0 );
  });
  server.begin();
  Serial.println("Server has started");
  ledcWrite(r, 0);
  ledcWrite(g, 0);
  ledcWrite(b, 0);
}

void loop() {
  server.handleClient();
}

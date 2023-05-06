#include<DHT.h>

DHT dht(5, DHT11);

// channel
const byte r = 0;
const byte g = 1;
const byte b = 2;

void setup(){
  Serial.begin(115200);
  dht.begin();
  
  ledcSetup(r, 5000, 8);
  ledcSetup(g, 5000, 8);
  ledcSetup(b, 5000, 8);
  ledcAttachPin(21, r);
  ledcAttachPin(22, g);
  ledcAttachPin(23, b);
}

void loop(){
  float humidity = dht.readHumidity();
  float temp_c = dht.readTemperature();
  
  if (isnan(humidity) || isnan(temp_c)) {
    Serial.println("Failed to read data");
    return;
  }

  float temp_f = (temp_c * 1.8) + 32;
  float temp_k = temp_c + 273;
  float dew_point = temp_c - ((100 - humidity) / 5);
  
  //  print all the values
  Serial.print("Temperature(C): ");
  Serial.println(temp_c);
  Serial.print("Temperature(F): ");
  Serial.println(temp_f);
  Serial.print("Temperature(K): ");
  Serial.println(temp_k);
  Serial.print("Humidity (%): ");
  Serial.println(humidity);
  Serial.print("Dew Point (C): ");
  Serial.println(dew_point);
  Serial.println("*****");
  
  delay(2000);
  
}

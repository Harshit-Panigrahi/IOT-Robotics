const int POTENTIOMETER_PIN = 15;
const int LED_PIN = 5;

void setup() {
  Serial.begin(9600);
  pinMode(POTENTIOMETER_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);
}

void loop() {
  int analogVal = analogRead(POTENTIOMETER_PIN);
  int brightness = map(analogVal, 0, 4095, 0, 255);
  
  Serial.print(brightness);
  ledcWrite(uint8_t channel, uint32_t duty)
  digitalWrite(LED_PIN, LOW);

  delay(500);
}


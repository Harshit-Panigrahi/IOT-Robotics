const int POTENTIOMETER_PIN = 15;
const int BUZZER_PIN = 5;

void setup() {
  Serial.begin(9600);
  pinMode(POTENTIOMETER_PIN, INPUT);
  pinMode(BUZZER_PIN, OUTPUT);
}

void loop() {
  int analogVal = analogRead(POTENTIOMETER_PIN);
  int volume = map(analogVal, 0, 4095, 0, 255);
  
  Serial.print(volume);
  if (volume >= 150) {
    Serial.println(" HIGH");
    digitalWrite(BUZZER_PIN, HIGH);
  } else {
    Serial.println(" LOW");
    digitalWrite(BUZZER_PIN, LOW);
  }

  delay(1500);
}


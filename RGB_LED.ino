#define RLED 23
#define GLED 22
#define BLED 21
#define R_CHANNEL 0
#define G_CHANNEL 1
#define B_CHANNEL 2
#define PWM_FREQUENCY 5000
#define PWM_RESOLUTION 8

void setup() {
  // put your setup code here, to run once:
  ledcAttachPin(RLED, R_CHANNEL);
  ledcAttachPin(GLED, G_CHANNEL);
  ledcAttachPin(BLED, B_CHANNEL);
  
  ledcSetup(R_CHANNEL, PWM_FREQUENCY, PWM_RESOLUTION);
  ledcSetup(G_CHANNEL, PWM_FREQUENCY, PWM_RESOLUTION);
  ledcSetup(B_CHANNEL, PWM_FREQUENCY, PWM_RESOLUTION);
}

void RGB_Color(int r, int g, int b) {
  ledcWrite(R_CHANNEL, r);
  ledcWrite(G_CHANNEL, g);
  ledcWrite(B_CHANNEL, b);
}

void loop() {
  // put your main code here, to run repeatedly:
  RGB_Color(255, 0, 0);
  delay(500);
  RGB_Color(0, 255, 0);
  delay(500);
  RGB_Color(0, 0, 255);
  delay(500);
}

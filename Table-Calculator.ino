#include <ezButton.h>

const int btn1 = 4;
const int btn2 = 22;
int num = 0;

ezButton pushBtn1(btn1);
ezButton pushBtn2(btn2);

void setup() {
  Serial.begin(115200);
  pushBtn1.setDebounceTime(50);
  pushBtn2.setDebounceTime(50);
}

void loop() {
  pushBtn1.loop();
  pushBtn2.loop();
  
  if (pushBtn1.isPressed()) {
    num++;
    Serial.print("Number: ");
    Serial.println(num);
  }

  else if (pushBtn2.isPressed()) {
    Serial.print("Table of ");
    Serial.println(num);

    for (int i=1; i <= 10; i++) {
      Serial.print(num);
      Serial.print('*');
      Serial.print(i);
      Serial.print('\t');
      Serial.print('=');
      Serial.print('\t');
      Serial.println(num*i);
    }
    
    num = 0;
  }
}

/* 
  Sketch generated by the Arduino IoT Cloud Thing "LED System"
  https://create.arduino.cc/cloud/things/45fe9f9e-6647-445c-9b1d-d1c2403afc26 

  Arduino IoT Cloud Variables description

  The following variables are automatically generated and updated when changes are made to the Thing

  CloudLight lED;

  Variables which are marked as READ/WRITE in the Cloud Thing will also have functions
  which are called when their values are changed from the Dashboard.
  These functions are generated with the Thing and added at the end of this sketch.
*/

#include "thingProperties.h"
int led_pin = 5;

void setup() {
  Serial.begin(9600);
  delay(1500);
  pinMode(led_pin, OUTPUT);

  initProperties();

  ArduinoCloud.begin(ArduinoIoTPreferredConnection);
  
  /*
     The following function allows you to obtain more information
     related to the state of network and IoT Cloud connection and errors
     the higher number the more granular information you’ll get.
     The default is 0 (only errors).
     Maximum is 4
 */
  setDebugMessageLevel(2);
  ArduinoCloud.printDebugInfo();
}

void loop() {
  ArduinoCloud.update();
}


void onLEDChange()  {
  // Add your code here to act upon LED change
  if (lED == 1) {
    digitalWrite(led_pin, HIGH);
  } else {
    digitalWrite(led_pin, LOW);
  }
}

#include <Servo.h>

Servo myservo;  // create servo object to control a servo

// twelve servo objects can be created on most boards

int pos = 0;    // variable to store the servo position

void setup() {
   Serial.begin(9600);
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object
}


void loop() {
myservo.write(0);
delay(2000);
myservo.write(180);
delay(2000);
/*delay(500);
myservo.write(180);                    //pin 9
delay(2000);*/
}

/* Sweep
 by BARRAGAN <http://barraganstudio.com>
 This example code is in the public domain.

 modified 8 Nov 2013
 by Scott Fitzgerald
 https://www.arduino.cc/en/Tutorial/LibraryExamples/Sweep
*/

#include <Servo.h>
#define S0 4
#define S1 5
#define S2 6
#define S3 7
#define sensorOut 8
int frequency = 0;

Servo sorting_servo;  // create servo object to control a servo
Servo bot_shooting_servo;
Servo rubb_shooting_servo;
Servo closing_shooting_servo;

// twelve servo objects can be created on most boards

int pos_drop = 0;    // variable to store the servo position
int pos_detect= 98;
int pos_take = 128;

int color=0;

void setup() {
  sorting_servo.attach(9);  // attaches the servo on pin 9 to the servo object
  bot_shooting_servo.attach(10);
  rubb_shooting_servo.attach(3);
  closing_shooting_servo.attach(11);
  
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(sensorOut, INPUT);
  
  // Setting frequency-scaling to 20%
  digitalWrite(S0,HIGH);
  digitalWrite(S1,LOW);
  
  Serial.begin(9600);
  
  

}

void loop() 
{
  bot_shooting_servo.write(80); // its zero refe.
  rubb_shooting_servo.write(0);
  closing_shooting_servo.write(0);

   sorting_servo.write(pos_take);
  delay(2000);
   for(int i=pos_take; i>pos_detect; i--)
        {
          sorting_servo.write(i);
          delay(25);
        }
        delay(4000); //to read the color
Serial.print("READING THE COLOR: ");
        color = Color();
  delay(15);  
  switch (color) {
    case 1: //yellow
    bot_shooting_servo.write(40);
    delay(1000);
    closing_shooting_servo.write(90); // to close on the hand
    delay(500);
    rubb_shooting_servo.write(180);
    
    
    break;
    case 2: //red

    bot_shooting_servo.write(120);
    delay(1000);
    closing_shooting_servo.write(90); // to close on the hand
    delay(500);
    rubb_shooting_servo.write(180);
    break;
    
    case 0:
    break;
  }
        
        for(int i= pos_detect ; i> pos_drop ; i--)
    {
        sorting_servo.write(i);
        delay(25);
     }
     
        delay(1000);

        for(int i=pos_drop; i<pos_take; i++)
        {
          sorting_servo.write(i);
          delay(15);
        }
        delay(1000);
        
        
    
}

  

int Color() {
  // Setting red filtered photodiodes to be read
  digitalWrite(S2, LOW);
  digitalWrite(S3, LOW);
  // Reading the output frequency
  delay(100);
  frequency = pulseIn(sensorOut, LOW);
  int R = frequency;
  // Printing the value on the serial monitor
  Serial.print("R= ");//printing name
  Serial.print(frequency);//printing RED color frequency
  Serial.print("  ");
  delay(50);
  // Setting Green filtered photodiodes to be read
  digitalWrite(S2, HIGH);
  digitalWrite(S3, HIGH);
  // Reading the output frequency
  delay(100);
  frequency = pulseIn(sensorOut, LOW);
  int G = frequency;
  // Printing the value on the serial monitor
  Serial.print("G= ");//printing name
  Serial.print(frequency);//printing RED color frequency
  Serial.print("  ");
  delay(50);
  // Setting Blue filtered photodiodes to be read
  digitalWrite(S2, LOW);
  digitalWrite(S3, HIGH);
  // Reading the output frequency
  delay(100);
  frequency = pulseIn(sensorOut, LOW);
  int B = frequency;
  // Printing the value on the serial monitor
  Serial.print("B= ");//printing name
  Serial.print(frequency);//printing RED color frequency
  Serial.println("  ");
  delay(50);
  if(B<280 && B>240 && R> 250 && R<290){
    color = 1; // yellow
    Serial.println(" it is yellow ") ;

   
  }
  if(R<250 && R>230 && G>340 && G<370){
    color = 2; // red
    Serial.println(" it is red ") ;


  }
  return color;  
}

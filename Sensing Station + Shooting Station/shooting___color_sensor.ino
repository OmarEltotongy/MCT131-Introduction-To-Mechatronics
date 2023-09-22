//marbel project (shooting + color sensor)

// include the library code for lcd:
#include <LiquidCrystal.h>

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 6;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

int motion_sensor_Pin = 2;                 // motion_sensor 
int motion_sensor_Stat = 0;                   //motion_sensor state

void setup() {
  // set up the LCD's number of columns and rows:
  
  lcd.begin(16, 2);
  pinMode(ledPin, OUTPUT);     
  pinMode(motion_sensor_Pin, INPUT); 
      
  Serial.begin(9600);
 
}
void loop(){
   motion_sensor_Stat = digitalRead(motion_sensor_Pin); 
  if (motion_sensor_Stat == LOW) // if motion detected //Low ==1 for motion sensor
  {            
    // Print a message to the LCD.
    lcd.print("Hey, there is a"); // we will display it on lcd
    lcd.setCursor(0, 6); // to make at almost at the mid in second line
    lcd.print("ball!!!");
    
   
 } 
 else {
   digitalWrite(ledPin, LOW); // turn LED OFF if we have no motion
   Serial.println("Hey, it's calm up there");

 }
} 

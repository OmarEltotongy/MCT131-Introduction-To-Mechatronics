//variables:
#include <LiquidCrystal.h>
#include <Servo.h>

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const byte rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 6;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

//lifting
//we will use motor A
const int IN1 = 7;
const int IN2 = 6;
const int ENA = 9;

//sorting 

int motion_sensor_Pin = 2;                 // motion_sensor
int  motion_sensor_led =13;                 //motion sensor led
int motion_sensor_Stat = 0;                   //motion_sensor state
int MS_counter = 0 ;
int sorting_servo_pin = 8;
int sorting_servo_pos0 = 0;                  //at the cylinder
int sorting_servo_pos1 = 0;                  //at the color sensor------------------------------------------------ hyt3dl
int sorting_servo_pos2 = 0;                  //to the track--------------------------------------------------------hyt3dl
Servo sorting_servo ;

int color = 0;
int frequency = 0;

#define S0 2
#define S1 3
#define S2 4
#define S3 5
#define sensorOut 6

const int turning_time = 1500;


//shooting
int shooting_servo_pin = 10;
int shooting_servo_pos0 = 0;            //at the mid
int shooting_servo_pos1 = 0;            //to the right resiv
int shooting_servo_pos2 = 0;            //to the left resiv
int shooting_dc1=0;
int shooting_dc2=0;

Servo shooting_servo ;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  //at the begining:
  lcd.begin(16, 2);
  lcd.print("Welcome to our");
  lcd.setCursor(6,1); // to make at almost at the mid in second line
  lcd.print("Project");

  //lifitng
  pinMode (IN1, OUTPUT);
  pinMode (IN2, OUTPUT);
  pinMode (ENA, OUTPUT);

  //sorting
  pinMode(motion_sensor_Pin, INPUT_PULLUP); 
  attachInterrupt(digitalPinToInterrupt(motion_sensor_Pin),interrupt_motion,FALLING) ; // as the motion sensor dropped from 1 to 0
  sorting_servo.attach(sorting_servo_pin);
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(sensorOut, INPUT); 
  digitalWrite(S0, HIGH); //20% scalling
  digitalWrite(S1, LOW);

  //shooting
  shooting_servo.attach(shooting_servo_pin);
  
}

void loop() {
  //for lifting:
  
//control speed of the motor "3la 7sb elsor3a elly 3ayzenha"---------------------------------------------------------------hyt3dl
  analogWrite(ENA, 255);
//control direction CW
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);

  //for sorting
 motion_sensor_Stat = digitalRead(motion_sensor_Pin); 
  if (motion_sensor_Stat == LOW) // if motion detected //Low ==1 for motion sensor
  {            
    // Print a message to the LCD.
    lcd.print("Hey, there is a"); // we will display it on lcd
    lcd.setCursor(6,1); // to make at almost at the mid in second line
    lcd.print("ball!!!");
    //(sorting code with motion sensor)
    for (int i=0 ; i<= MS_counter ; i++)
    {
      if (MS_counter ==0)
      {
        break;
      }
      delay(4000);                                    //time from motion sensor to sorting servo --------------------------------hyt3dl
      for( int j =83; j>sorting_servo_pos1 ; j--)                     //  ---------------------------------------------------------------------hyt3dl
      {
        sorting_servo.write(j);     
        delay(2);   
      }
      
      color = readColor(); //read the value from color sensor and put the bottom servo in the right path
       delay(10);  
      switch (color)              
      {
        
      case 1:
      shooting_servo.write(shooting_servo_pos1);
      digitalWrite(shooting_dc1,HIGH);
      digitalWrite(shooting_dc2,HIGH);
      sorting_servo.write(sorting_servo_pos2);

      break;
      
      case 2:
      shooting_servo.write(shooting_servo_pos2);
      digitalWrite(shooting_dc1,HIGH);
      digitalWrite(shooting_dc2,HIGH);
      sorting_servo.write(sorting_servo_pos2);

      break;
      
       }
      
      sorting_servo.write(sorting_servo_pos0);
      shooting_servo.write(shooting_servo_pos0);
      MS_counter--;
    }
 } 
 else {
  
   lcd.print("Hey, it's calm");
   lcd.setCursor(4,1);
   lcd.print("up there");
   digitalWrite(motion_sensor_led,LOW);

 }
  


}



int readColor() { //color sensor function to read the color
  
  // Setting red
  digitalWrite(S2, LOW);
  digitalWrite(S3, LOW);
  frequency = pulseIn(sensorOut, LOW);
  int R = frequency;
  Serial.print("R= ");
  Serial.print(frequency);
  Serial.print("  ");
  delay(50);
  
  // Setting Green
  digitalWrite(S2, HIGH);
  digitalWrite(S3, HIGH);
  frequency = pulseIn(sensorOut, LOW);
  int G = frequency;
  Serial.print("G= ");
  Serial.print(frequency);
  Serial.print("  ");
  delay(50);
  if(R<65 & R>50 & G>83 & G<95){        //---------------------------------------------
    color = 1; // Red
  }
  if(G<70 & G>55 & R<75 & R>65)      // -------------------------------------------------
  {
    color = 2; // Green
  }
  
  return color;  
}

void interrupt_motion()
{
digitalWrite(motion_sensor_led,HIGH);
    MS_counter++ ;
}

int en1 = 12;
int en2 = 13;
int pwm =9;
void setup() {
  // put your setup code here, to run once:
pinMode(en1 , OUTPUT);
pinMode(en2 , OUTPUT);
pinMode(pwm , OUTPUT);
analogWrite(pwm, 100);
}

void loop() {
  // put your main code here, to run repeatedly:
digitalWrite(en2,HIGH); // to rotate the screw in an upward direction.
digitalWrite(en1,LOW);

}

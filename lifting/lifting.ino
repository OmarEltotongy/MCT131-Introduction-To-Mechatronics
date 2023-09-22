//project of marble track (lifting):
//we will use motor A
const int IN1 = 7;
const int IN2 = 6;
const int ENA = 9;


void setup() {

  pinMode (IN1, OUTPUT);
  pinMode (IN2, OUTPUT);
  pinMode (ENA, OUTPUT);

}

void loop() {
//control speed of the motor "3la 7sb elsor3a elly 3ayzenha"
  analogWrite(ENA, 255);
//control direction CW
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  
}

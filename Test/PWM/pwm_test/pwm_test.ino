int motorPin = 3;
int motorSpeed = 0;
int ledPin = 9;

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  motorSpeed=160;
   
}

void loop() {
  // full speed
  analogWrite(motorPin, motorSpeed);
  digitalWrite(LED_BUILTIN,HIGH);
  delay(500);
  digitalWrite(LED_BUILTIN,LOW);
  delay(4500);
  motorSpeed=motorSpeed+10;
  if (motorSpeed==210) {
    motorSpeed=160;
  }
  
}

int motorPin = 3;
int motorSpeed = 0;
int ledPin = 9;

void setup() {
  pinMode(ledPin, OUTPUT);
}

void loop() {
  // full speed
  analogWrite(motorPin, 52);
  delay(3000);
  analogWrite(motorPin, 39);
  delay(3000);
  analogWrite(motorPin, 26);
  delay(3000);
  analogWrite(motorPin, 13);
  delay(3000);
  analogWrite(motorPin, 0);
  delay(3000);
}

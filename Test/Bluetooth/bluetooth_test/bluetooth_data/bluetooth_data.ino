#include <SoftwareSerial.h>


#define btTX 10
#define btRX 11

SoftwareSerial btSerial(btTX, btRX);

void setup() {
  // put your setup code here, to run once:
  pinMode(btTX, INPUT);
  pinMode(btRX, OUTPUT);
  Serial.begin(57600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  Serial.println("Setup Start");
  btSerial.begin(38400);
  btSerial.setTimeout(100);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (btSerial.available()) {
      Serial.write(btSerial.read());
  }   
}

#include <SoftwareSerial.h>


#define btTX 10
#define btRX 11
#define btKEY 12

SoftwareSerial btSerial(btTX, btRX);

long baudRates[] = {
  4800,
  9600,
  19200,
  38400,
  57600,
  115200  
};

long btBaudRate;
int i;

int sendCmd2Bt(char cmd[])
{
  btSerial.println(cmd);
  delay(100);
  return btSerial.find("OK\r\n");
}

void setup() {
  btBaudRate=-1;
  pinMode(btTX, INPUT);
  pinMode(btRX, OUTPUT);
  pinMode(btKEY, OUTPUT);
  digitalWrite(btKEY, HIGH);
  Serial.begin(57600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  Serial.println("Setup Start");
  for(i=0;i<(sizeof(baudRates)/sizeof(long));i++) {
    Serial.print("Try baud rate:");
    Serial.println(baudRates[i],DEC);
    btSerial.begin(baudRates[i]);
    btSerial.setTimeout(100);
    btSerial.print("\r\n");
    btSerial.println("AT");
    if (btSerial.find("OK")) {
      Serial.println("Baud rate found");
      btBaudRate=baudRates[i];
      break;
    }
    btSerial.end();
    delay(100);
  }
  if (btBaudRate!=-1) {
    sendCmd2Bt("AT+NAME=PLARAIL");
    sendCmd2Bt("AT+PSWD=0000");
  }  
  digitalWrite(btKEY, LOW);
  Serial.println("Setup Done!");
}

void loop() {
  if (btBaudRate!=-1) {
    if (btSerial.available()) {
      Serial.write(btSerial.read());
    }       
  }
}

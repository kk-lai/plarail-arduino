#include <SoftwareSerial.h>

#define btTX 10
#define btRX 11
#define motorPin 3

#define COM1 Serial
#define COM2 btSerial
#define COM COM2
#define RX_BUFFER_LEN 32
SoftwareSerial btSerial(btTX, btRX);


char cmd[RX_BUFFER_LEN];
int rxIdx = 0;
int trainSpeed = 0;

const char STX[] = "STX ";
const int stxSize = sizeof(STX)-1;
const char ETX = '\r';
const int trainSpeeds[] = { 0, 140,150,160,170 };
const int trainSpeedsSize = sizeof(trainSpeeds)/sizeof(int);
const char minSpeed = '0';
const char maxSpeed = '0'+trainSpeedsSize-1;
const char *commands[] = {
  "SPEED=",
  "CHARGE="
};
const int commandsSize = sizeof(commands)/sizeof(char *);
const char RES_ERR[] = "ERR\r\n";
const char RES_OK[] = "OK\r\n";


void receiveCmd()
{
  int l;
  int b;
  l = COM.available();
  while (l>0) {
    b = COM.read();
    /*Serial.print(b, DEC);
    Serial.print(",");
    Serial.println(rxIdx,DEC);*/
    if (rxIdx >= stxSize) {
      if (b==ETX) {
        cmd[rxIdx-stxSize]=0;
        rxIdx=0;
        executeCmd();        
      } else {
        cmd[rxIdx-stxSize]=b;
        rxIdx++;  
        if (rxIdx-stxSize==RX_BUFFER_LEN) {
          rxIdx=0;
        }
      }      
    } else {
      if (b==STX[rxIdx]) {
        rxIdx++;
      } else {
        rxIdx=0;
      }
    }
    l--;
  }  
}

void executeCmd()
{
  int cmdi;
  const char *c;
  int p;

  Serial.print("Received command:");
  Serial.println(cmd);

  for(cmdi=0;cmdi<commandsSize;cmdi++) 
  {
    c = commands[cmdi];
    for(p=0;*(c+p)!=0;) {
      if (cmd[p]==*(c+p)) {
        p++;
      } else {
        break;
      }
    }
    if (*(c+p)==0) {
      break;
    }
  }
  switch(cmdi) {
  case 0:
    // set speed
    if (cmd[p]>=minSpeed && cmd[p]<=maxSpeed) {
      Serial.print("Set Speed=");
      Serial.print(cmd[p]);
      Serial.print(",");
      Serial.println(trainSpeeds[cmd[p]-minSpeed], DEC);
      analogWrite(motorPin, trainSpeeds[cmd[p]-minSpeed]);
      responseOK();
    } else {
      Serial.println("Invalid Speed");
      responseError();
    }
    break;
  case 1:
    responseOK();
    break;
  default:
    responseError();
  }
}

void responseOK()
{
  COM.write(RES_OK);
  digitalWrite(LED_BUILTIN,HIGH);
  delay(100);
  digitalWrite(LED_BUILTIN,LOW);
}

void responseError()
{
  COM.write(RES_ERR);
  digitalWrite(LED_BUILTIN,HIGH);
  delay(100);
  digitalWrite(LED_BUILTIN,LOW);
  delay(100);
  digitalWrite(LED_BUILTIN,HIGH);
  delay(100);
  digitalWrite(LED_BUILTIN,LOW);
}

void setup() {
  Serial.begin(57600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  pinMode(btTX, INPUT);
  pinMode(btRX, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  analogWrite(motorPin,0);
  btSerial.begin(38400);
  Serial.println("Setup End"); 
}

void loop() {
  receiveCmd();
  
}




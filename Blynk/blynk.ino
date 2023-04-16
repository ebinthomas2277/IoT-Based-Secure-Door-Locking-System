#include <BlynkSimpleStream.h>
#include <SoftwareSerial.h>

#define BLYNK_TEMPLATE_ID           "TMPLxxxxxx"
#define BLYNK_DEVICE_NAME           "Device"
#define BLYNK_AUTH_TOKEN            "_nPPm5qZny_895rC6dVFOJOAnXc-aeSS"

SoftwareSerial mySerial(2, 3);

char auth[] = BLYNK_AUTH_TOKEN;
const int baudRate1 = 9600;
const int baudRate2 = 19200;

const int relayPin = 4;
const int magneticPin = 5;
const int greenPin = 50;
const int yellowPin = 51;
const int redPin = 52;
const int buzzerPin = 53;


BLYNK_WRITE(V1)
{
  int pinValue = param.asInt(); // assigning incoming value from pin V1 to a variable
  if(pinValue == 1){
    mySerial.println("Door Unlocked");
    digitalWrite(relayPin, HIGH);
    digitalWrite(magneticPin, LOW);
    digitalWrite(greenPin, HIGH);
    digitalWrite(yellowPin, LOW);
    digitalWrite(redPin, LOW);
    digitalWrite(buzzerPin, HIGH);
  }
  if(pinValue == 0){
    mySerial.println("Door Locked");
    digitalWrite(relayPin, LOW);
    digitalWrite(magneticPin, LOW);
    digitalWrite(greenPin, LOW);
    digitalWrite(yellowPin, HIGH);
    digitalWrite(redPin, LOW);
    digitalWrite(buzzerPin, LOW);
    
  }
  

}

void setup()
{

  Serial.begin(baudRate1);
  mySerial.begin(baudRate2);
  
  Blynk.begin(Serial, auth);

  pinMode(relayPin, OUTPUT);
  pinMode(magneticPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(yellowPin, OUTPUT);
  pinMode(redPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);

  digitalWrite(relayPin, LOW);
  digitalWrite(magneticPin, LOW);
  digitalWrite(greenPin, LOW);
  digitalWrite(yellowPin, LOW);
  digitalWrite(redPin, LOW);
  digitalWrite(buzzerPin, LOW);
}

void loop()
{
  Blynk.run();
  int magneticValue = digitalRead(magneticPin);
  if(magneticValue == 1){
    Blynk.notify("Tampering Detected");
  }
}

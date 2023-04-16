#include <LiquidCrystal.h>
#include <SoftwareSerial.h>

// Sensor intialisation

const int relayPin = 4;
const int magneticPin = 5;
const int vibrationPin = 6;
const int irPin = 7;

// Lcd Display Connections

const int RS = 22;
const int EN = 23;
const int D4 = 24;
const int D5 = 25;
const int D6 = 26;
const int D7 = 27;

// Intaializing Lcd and Serial Connections
LiquidCrystal myLcd(RS, EN, D4, D5, D6, D7);
SoftwareSerial mySerial(2,3);

// Led intializing
const int greenPin = 50;
const int yellowPin = 51;
const int redPin = 52;
const int buzzerPin = 53;


// Decclaring Sesnor Variables
int vibrationValue;
int magneticValue;
int irValue;
String message;
int doorStatus = 0;
int timer;

// Setting up baudrate 
const int baudRate1 = 19200;
const int baudRate2= 9600;

void setup()
{
  // Establishing Serial Connection
  Serial.begin(baudRate1);
  mySerial.begin(baudRate2);


  // Setting up the sensors based on their duty.
  
  pinMode(relayPin, OUTPUT);
  pinMode(magneticPin, OUTPUT);
  pinMode(vibrationPin, OUTPUT);
  pinMode(irPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(yellowPin, OUTPUT);
  pinMode(redPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);

  digitalWrite(relayPin, LOW);
  digitalWrite(magneticPin, LOW);
  digitalWrite(vibrationPin, LOW);
  digitalWrite(irPin, LOW);
  digitalWrite(greenPin, LOW);
  digitalWrite(yellowPin, LOW);
  digitalWrite(redPin, LOW);
  digitalWrite(buzzerPin, LOW);

  myLcd.begin(16, 2);
  myLcd.clear();
  myLcd.setCursor(0, 0);

  myLcd.print("System Starting");
  myLcd.setCursor(0, 1);
  for (int i = 0; i <= 15; i++) {
    myLcd.print(".");
    delay(60);
  }

  myLcd.clear();
  myLcd.setCursor(0, 0);
  myLcd.print("Loading Completed! ");
  delay(250);
  myLcd.clear();
  myLcd.setCursor(0, 0);
  myLcd.print("System Active");
  delay(250);
  myLcd.clear();

}

void checkForThreat()
{
  vibrationValue = digitalRead(vibrationPin);
  magneticValue = digitalRead(magneticPin);

  while ((vibrationValue == 1 && doorStatus == 0) || (magneticValue == 1 && doorStatus == 0))
  {
    digitalWrite(greenPin, LOW);
    digitalWrite(yellowPin, LOW);
    digitalWrite(redPin, HIGH);
    digitalWrite(buzzerPin, HIGH);

    if (magneticValue == 1 && vibrationValue == 0 && doorStatus == 0 || magneticValue == 1 && vibrationValue == 1 && doorStatus == 0)
    {
      myLcd.clear();
      myLcd.setCursor(0, 0);
      myLcd.print("Threat Detected");
      myLcd.setCursor(0, 1);
      myLcd.print("Break In!");
      delay(100);
    }

    if (vibrationValue == 1 && magneticValue == 0 && doorStatus == 0)
    {
      myLcd.clear();
      myLcd.setCursor(0, 0);
      myLcd.print("Threat Detected");
      myLcd.setCursor(0, 1);
      myLcd.print("Tampering!");
      delay(100);
    }


    vibrationValue = digitalRead(vibrationPin);
    magneticValue = digitalRead(magneticPin);
  }
  myLcd.clear();
  digitalWrite(greenPin, LOW);
  digitalWrite(yellowPin, LOW);
  digitalWrite(redPin, LOW);
  digitalWrite(buzzerPin, LOW);
}

void unlock()
{

  digitalWrite(greenPin, HIGH);
  digitalWrite(yellowPin, LOW);
  digitalWrite(redPin, LOW);
  digitalWrite(buzzerPin, HIGH);
  digitalWrite(relayPin, HIGH);

  doorStatus = 1;

  myLcd.clear();
  myLcd.setCursor(0, 0);
  myLcd.print("Door Unlocked!");
  delay(300);

  digitalWrite(greenPin, LOW);
  digitalWrite(yellowPin, LOW);
  digitalWrite(redPin, LOW);
  digitalWrite(buzzerPin, LOW);
  myLcd.clear();
  timer = millis();

}

void lock()
{

  digitalWrite(greenPin, LOW);
  digitalWrite(yellowPin, HIGH);
  digitalWrite(redPin, LOW);
  digitalWrite(buzzerPin, HIGH);
  digitalWrite(relayPin, LOW);

  doorStatus = 0;
  myLcd.clear();
  myLcd.setCursor(0, 0);
  myLcd.print("Door Locked!");
  delay(300);

  digitalWrite(redPin, LOW);
  digitalWrite(greenPin, LOW);
  digitalWrite(yellowPin, LOW);
  digitalWrite(buzzerPin, LOW);
  myLcd.clear();

}

void invalid()
{

  digitalWrite(greenPin, LOW);
  digitalWrite(yellowPin, HIGH);
  digitalWrite(redPin, HIGH);
  digitalWrite(buzzerPin, HIGH);
  digitalWrite(relayPin, LOW);

  doorStatus = 0;
  myLcd.clear();
  myLcd.setCursor(0, 0);
  myLcd.print("Invalid Entry!");
  delay(300);
  myLcd.clear();
  myLcd.setCursor(0, 0);
  myLcd.print("Door Locked!");
  delay(300);

  digitalWrite(greenPin, LOW);
  digitalWrite(yellowPin, LOW);
  digitalWrite(redPin, LOW);
  digitalWrite(buzzerPin, LOW);
  digitalWrite(relayPin, LOW);
  myLcd.clear();

}
void autoTimer() {

  while ((millis() - timer >= 1500) && doorStatus == 1) {
    
      if ( magneticValue == 0)
      {
        doorStatus = 0;
        digitalWrite(greenPin, LOW);
        digitalWrite(yellowPin, HIGH);
        digitalWrite(redPin, LOW);
        digitalWrite(buzzerPin, HIGH);
        digitalWrite(relayPin, LOW);
  
        myLcd.clear();
        myLcd.setCursor(0, 0);
        myLcd.print("Auto Lock");
        myLcd.setCursor(0, 1);
        myLcd.print("Activated!");
  
        delay(300);
  
        digitalWrite(greenPin, LOW);
        digitalWrite(yellowPin, LOW);
        digitalWrite(redPin, LOW);
        digitalWrite(buzzerPin, LOW);
        digitalWrite(relayPin, LOW);
        break;
      }
      if ( magneticValue == 1)
      {
        digitalWrite(greenPin, LOW);
        digitalWrite(yellowPin, HIGH);
        digitalWrite(redPin, HIGH);
        digitalWrite(buzzerPin, HIGH);
        digitalWrite(relayPin, LOW);
  
        doorStatus = 1;
        myLcd.clear();
        myLcd.setCursor(0, 0);
        myLcd.print("Auto Lock!");
        myLcd.setCursor(0, 1);
        myLcd.print("Not Activated");
        delay(300);
        myLcd.clear();
        myLcd.setCursor(0, 0);
        myLcd.print("Please!");
        myLcd.setCursor(0, 1);
        myLcd.print("Close The Door");
        delay(300);
  
        digitalWrite(greenPin, LOW);
        digitalWrite(yellowPin, LOW);
        digitalWrite(redPin, LOW);
        digitalWrite(buzzerPin, LOW);
        digitalWrite(relayPin, LOW);
        myLcd.clear();
        break;
      }
  }
}

void fromInside() {

  vibrationValue = digitalRead(vibrationPin);
  magneticValue = digitalRead(magneticPin);
  irValue = digitalRead(irPin);

  if (irValue == 1 && doorStatus == 0 && vibrationValue == 0 && magneticValue == 0) {

    digitalWrite(greenPin, HIGH);
    digitalWrite(yellowPin, LOW);
    digitalWrite(redPin, LOW);
    digitalWrite(buzzerPin, HIGH);
    digitalWrite(relayPin, HIGH);

    doorStatus = 1;

    myLcd.clear();
    myLcd.setCursor(0, 0);
    myLcd.print("Door Unlocked!");
    myLcd.setCursor(0, 1);
    myLcd.print("From Inside");
    delay(300);

    digitalWrite(greenPin, LOW);
    digitalWrite(yellowPin, LOW);
    digitalWrite(redPin, LOW);
    digitalWrite(buzzerPin, LOW);
    myLcd.clear();
    timer = millis();
  }

}

void loop()
{
  Serial.print("Enter the command: ");
  while (Serial.available() == 0)
  {
    fromInside();
    checkForThreat();
    autoTimer();
  }
  message = Serial.readString();
  Serial.println(message);
  if (message == "open" || message == "OPEN" || message == "Open")
  {
    unlock();
  }
  else if (message == "close" || message == "CLOSE" || message == "Close")
  {
    lock();
  }
  else
  {
    invalid();
  }
}

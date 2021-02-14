const int ledPin = 13;

const int ldrPin = A0;

#include <EEPROM.h>

int addr = 0;

void setup() {

  Serial.begin(9600);

  pinMode(ledPin, OUTPUT);

  Serial.println("ProjectIR V1.0");

  Serial.println("Logger is starting in 30 Seconds and ALL IR Data will be erased");

  digitalWrite(ledPin, HIGH);

  delay(30000);

  digitalWrite(ledPin, LOW);

  Serial.println("Erasing EEPROM");

  for (int i = 0 ; i < EEPROM.length() ; i++) {
    EEPROM.write(i, 0);
  }

  Serial.println("Erase Done");

  Serial.println("Logger Started");

  pinMode(ldrPin, INPUT);

}

void loop() {

  int ldrStatus = analogRead(ldrPin);

  Serial.println(ldrStatus);

  int val = ldrStatus;

  EEPROM.write(addr, val);

  addr = addr + 1;

  if (addr == EEPROM.length()) {

    addr = 0;

  }

  digitalWrite(ledPin, HIGH);

  delay(100);

  digitalWrite(ledPin, LOW);

  delay(60000);

}

const int ledPin = 13;

const int ldrPin = A0;

#include <EEPROM.h>

int addr = 0;

void setup() {

  Serial.begin(9600);

  pinMode(ledPin, OUTPUT);

  Serial.println("ProjectIR V1.1");

  Serial.println("Please Note: If you want to read the data, Use the included eeprom_read.ino file!");

  Serial.println("Logger is starting in 30 Seconds and ALL IR Data will be erased");

  digitalWrite(ledPin, HIGH);

  delay(30000); // Wait for 30 seconds, If data was written the user has 30 secs before all data is erased.

  digitalWrite(ledPin, LOW);

  Serial.println("Erasing EEPROM");

  for (int i = 0 ; i < EEPROM.length() ; i++) {
    EEPROM.write(i, 0);
  }

  Serial.println("Erase Done");

  Serial.println("Logger Started");

  Serial.println("If you forgot to upload the read code leave this device outside for about 30 mins or more then after that replug this data logger and upload the read eeprom code!");

  pinMode(ldrPin, INPUT);

}

void loop() {

  int ldrStatus = analogRead(ldrPin); // read A0 and set it as ldrStatus

  Serial.println(ldrStatus); // Used for debugging

  int val = ldrStatus; // Change ldtStatus to val

  EEPROM.update(addr, val); // Used update for better EEPROM Lifespan

  addr = addr + 1;

  if (addr == EEPROM.length()) {

    addr = 0;

  }

  digitalWrite(ledPin, HIGH); // Blink LED for write success

  delay(100);

  digitalWrite(ledPin, LOW);

  delay(60000); // Wait for 1 minute

}

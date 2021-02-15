/*
ProjectIR

This is ProjectIR, Its a IR light logger, Use it for Weather, Science or just for fun!
Made by Owen Hurst
All code here is tested.

The 2021 IR Project
*/

const int ledPin = 13;

const int ldrPin = A0;

#include <EEPROM.h>

#include <LowPower.h>

int addr = 0;

void setup() {

  Serial.begin(9600);

  pinMode(ledPin, OUTPUT);

  Serial.println("ProjectIR V1.2");

  Serial.println("Firmware V1.0");

  Serial.println("Please Note: If you want to read the data, Use the included eeprom_read.ino file!");

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

  Serial.println("If you forgot to upload the read code leave this device outside for about 30 mins or more then after that replug this data logger and upload the read eeprom code!");

  pinMode(ldrPin, INPUT);

}

void loop() {

  int ldrStatus = analogRead(ldrPin);

  Serial.println(GetTemp(), 1);

  Serial.println(ldrStatus);

  int val = ldrStatus;

  EEPROM.update(addr, val);

  addr = addr + 1;

  if (addr == EEPROM.length()) {

    addr = 0;

  }

  Serial.println("Data Saved!");

  Serial.println("Logging Stop");

  digitalWrite(ledPin, HIGH); 

  delay(100);

  digitalWrite(ledPin, LOW);

  delay(60000);

  Serial.println("Logging Start");

}

double GetTemp(void)

{

  unsigned int wADC;

  double t;

  ADMUX = (_BV(REFS1) | _BV(REFS0) | _BV(MUX3));

  ADCSRA |= _BV(ADEN);

  delay(20);

  ADCSRA |= _BV(ADSC);

  while (bit_is_set(ADCSRA, ADSC));

  wADC = ADCW;

  t = (wADC - 324.31 ) / 1.22;

  return (t);

}

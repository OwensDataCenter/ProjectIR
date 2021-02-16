/*
  ProjectIR

  This is ProjectIR, Its a IR light logger, Use it for Weather, Science or just for fun!
  Made by Owen Hurst
  All code here is tested.

  The 2021 IR Project
*/

const int ledPin = 13;

const int tonePin = 11;

const int irPin = A0;

#include <EEPROM.h>

int addr = 0;

void setup() {

  Serial.begin(9600);

  pinMode(ledPin, OUTPUT);

  Serial.println("ProjectIR V1.4");

  Serial.println("Firmware V1.0");

  Serial.println("Please Note: If you want to read the data, Use the included eeprom_read.ino file!");

  Serial.println("Logger is starting in 30 Seconds and ALL IR Data will be erased");

  digitalWrite(ledPin, HIGH);

  delay(30000);

  digitalWrite(ledPin, LOW);

  tone(tonePin, 440, 500);

  Serial.println("Erasing EEPROM");

  for (int i = 0 ; i < EEPROM.length() ; i++) {

    EEPROM.write(i, 0);

  }

  Serial.println("Erase Done");

  Serial.println("Logger Started");

  Serial.println("If you forgot to upload the read code leave this device outside for about 30 mins or more then after that replug this data logger and upload the read eeprom code!");

  pinMode(irPin, INPUT);

}

void loop() {

  int irStatus = analogRead(irPin);

  Serial.println(GetTemp(), 1);

  Serial.println(irStatus);

  int input = irStatus;
  int constrainedInput = constrain(input, 50, 200);


  int val = constrainedInput;

  EEPROM.update(addr, val);

  addr = addr + 1;

  if (addr == EEPROM.length()) {

    addr = 0;

  }

  Serial.println("Data Saved!");

  digitalWrite(ledPin, HIGH);



200
  delay(100);

  digitalWrite(ledPin, LOW);

  delay(60000);

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

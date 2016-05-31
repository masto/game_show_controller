#include <SPI.h>
#include <Wire.h>

// const int buzzerChipSelect = 8;
const int latchPin = 4;

byte digits[11] = { 0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07, 0x7f, 0x67, 0x00 };

void displayDigit(byte digit) {
  // Shift the data out
  SPI.beginTransaction(SPISettings(30000000, MSBFIRST, SPI_MODE0));
  SPI.transfer(0xff-digits[digit]);
  SPI.endTransaction();
  
  // Toggle latch
  digitalWrite(latchPin, HIGH);
  digitalWrite(latchPin, LOW); 
}

void displayOff() {
  displayDigit(10);
}

void receiveEvent(int howMany) {
  while (Wire.available()) {
    byte d = Wire.read();
    displayDigit(d);
  }  
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  SPI.begin();

  pinMode(latchPin, OUTPUT);
  digitalWrite(latchPin, LOW);

  Wire.begin(8);
  Wire.onReceive(receiveEvent);

  // Blink to show we started up
  displayDigit(8);
  delay(250);
  displayOff();
  delay(250);
  displayDigit(8);
  delay(250);
  displayOff();

  Serial.println("Ready.");
}

void loop() {
  // put your main code here, to run repeatedly:
  delay(100);
}

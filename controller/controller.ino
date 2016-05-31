#include <SPI.h>
#include <Wire.h>

const int buzzerChipSelect = 8;
const int buzzerLoad = 4;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  SPI.begin();

  pinMode(buzzerChipSelect, OUTPUT);
  pinMode(buzzerLoad, OUTPUT);

  digitalWrite(buzzerChipSelect, HIGH);

  Serial.println("Ready.");
  displayOff();
}

byte bitToPosition(byte bits) {
  byte count = 0;

  while (bits > 0) {
    bits >>= 1;
    count++;
  }

  return count;
}

void displayDigit(byte digit) {
  Wire.begin();
  Wire.beginTransmission(8);
  Wire.write(digit);
  Wire.endTransmission();
}

void displayOff() {
  displayDigit(10);
}

void loop() {
  // put your main code here, to run repeatedly:

  byte buzzerStates;

  // Toggle the load pin
  digitalWrite(buzzerLoad, LOW);
  digitalWrite(buzzerLoad, HIGH);

  // Shift the data in
  SPI.beginTransaction(SPISettings(30000000, MSBFIRST, SPI_MODE0));
  digitalWrite(buzzerChipSelect, LOW);
  buzzerStates = SPI.transfer(0);
  digitalWrite(buzzerChipSelect, HIGH);
  SPI.endTransaction();

  if (buzzerStates != 0) {
    Serial.print("got ");
    Serial.println(bitToPosition(buzzerStates));
    displayDigit(bitToPosition(buzzerStates));
    delay(1000);
    Serial.println("Ready.");
    displayOff();
  }
}

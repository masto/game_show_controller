#include <SPI.h>

const int buzzerChipSelect = 2;
const int buzzerLoad = 4;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  SPI.begin();

  pinMode(buzzerChipSelect, OUTPUT);
  pinMode(buzzerLoad, OUTPUT);

  digitalWrite(buzzerChipSelect, HIGH);
}

void loop() {
  // put your main code here, to run repeatedly:

  byte buzzerStates;

  // Toggle the load pin
  digitalWrite(buzzerLoad, LOW);
  delay(5);
  digitalWrite(buzzerLoad, HIGH);

  // Shift the data in
  SPI.beginTransaction(SPISettings(14000000, MSBFIRST, SPI_MODE0));
  digitalWrite(buzzerChipSelect, LOW);
  buzzerStates = SPI.transfer(0);
  digitalWrite(buzzerChipSelect, HIGH);
  SPI.endTransaction();

  if (buzzerStates != 0) {
    Serial.print("got ");
    Serial.println(buzzerStates);
    while (1) {
      delay(1000);
    }
  }
}

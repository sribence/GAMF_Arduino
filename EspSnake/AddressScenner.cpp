#include <Wire.h>

void setup() {
  Wire.begin();
  Serial.begin(9600);
  while (!Serial);
  Serial.println("I2C szkenner");
}

void loop() {
  byte error, address;
  int nDevices = 0;

  Serial.println("Szkenneles...");
  for (address = 1; address < 128; address++) {
    Wire.beginTransmission(address);
    error = Wire.endTransmission();
    if (error == 0) {
      Serial.print("I2C eszkoz talalva: 0x");
      Serial.println(address, HEX);
      nDevices++;
    }
  }

  if (nDevices == 0)
    Serial.println("Nem talalhato eszkoz.\n");
  else
    Serial.println("Szkenneles befejezve.\n");

  delay(5000);
}

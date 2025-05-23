#include <Wire.h>
#include <Adafruit_GFX.h>         // Telepíteni kell
#include <Adafruit_LEDBackpack.h> // Telepíteni kell

Adafruit_8x8matrix matrix0 = Adafruit_8x8matrix();
Adafruit_8x8matrix matrix1 = Adafruit_8x8matrix();
Adafruit_8x8matrix matrix2 = Adafruit_8x8matrix();
Adafruit_8x8matrix matrix3 = Adafruit_8x8matrix();
Adafruit_8x8matrix matrix4 = Adafruit_8x8matrix();
Adafruit_8x8matrix matrix5 = Adafruit_8x8matrix();
Adafruit_8x8matrix matrix6 = Adafruit_8x8matrix();
Adafruit_8x8matrix matrix7 = Adafruit_8x8matrix();

// Karakterek 
static const uint8_t num0[] = {B00000000,
                              B00110000,
                              B01001000,
                              B01001000,
                              B01001000,
                              B01001000,
                              B00110000,
                              B00000000};
static const uint8_t num1[] = {B00000000,
                               B00010000,
                               B00110000,
                               B00010000,
                               B00010000,
                               B00010000,
                               B00111000,
                               B00000000};
static const uint8_t num2[] = {B00000000,
B00110000,
B01001000,
B00010000,
B00100000,
B01000000,
B01111000,
B00000000};
static const uint8_t num3[] = {B00000000,
B00110000,
B01001000,
B00010000,
B00010000,
B01001000,
B00110000,
B00000000};
static const uint8_t num4[] = {B00000000,
B01000000,
B01000000,
B01010000,
B01110000,
B00010000,
B00010000,
B00000000};
static const uint8_t num5[] = {B00000000,
B01110000,
B01000000,
B01100000,
B00010000,
B00010000,
B01100000,
B00000000};
static const uint8_t num6[] = {B00000000,
B00110000,
B01001000,
B01000000,
B01110000,
B01001000,
B00110000,
B00000000};
static const uint8_t num7[] = {B00000000,
B01111000,
B00001000,
B00010000,
B00111000,
B00010000,
B00010000,
B00000000};

void setup() 
{
    Serial.begin(9600);
    // Cserélgetsd a címeket addig amíg a megfelelő szám a megfelelő helyen nem lesz
    matrix0.begin(0x70);
    matrix1.begin(0x71);
    matrix2.begin(0x72);
    matrix3.begin(0x73);
    matrix4.begin(0x74);
    matrix5.begin(0x75);
    matrix6.begin(0x76);
    matrix7.begin(0x77);

    // Módosítsd az orientációt hogy megfelelő legyen
    matrix0.setRotation(0);
    matrix1.setRotation(0);
    matrix2.setRotation(0);
    matrix3.setRotation(0);
    matrix4.setRotation(0);
    matrix5.setRotation(0);
    matrix6.setRotation(0);
    matrix7.setRotation(0);

    clearScreen();
}

void loop() 
{
    clearScreen();

    szamKiir(matrix0, 0);
    delay(500);
    szamKiir(matrix1, 1);
    delay(500);
    szamKiir(matrix2, 2);
    delay(500);
    szamKiir(matrix3, 3);
    delay(500);
    szamKiir(matrix4, 4);
    delay(500);
    szamKiir(matrix5, 5);
    delay(500);
    szamKiir(matrix6, 6);
    delay(500);
    szamKiir(matrix7, 7);
    delay(500);
}
void szamKiir(Adafruit_8x8matrix matrix, int num)
{
  const uint8_t* pattern;

  // Select the correct digit pattern
  switch (num)
  {
    case 0: pattern = num0; break;
    case 1: pattern = num1; break;
    case 2: pattern = num2; break;
    case 3: pattern = num3; break;
    case 4: pattern = num4; break;
    case 5: pattern = num5; break;
    case 6: pattern = num6; break;
    case 7: pattern = num7; break;
    default: return; // Ignore invalid numbers
  }

  matrix.clear();

  for (uint8_t y = 0; y < 8; y++)
  {
    uint8_t row = pattern[y];
    for (uint8_t x = 0; x < 8; x++)
    {
      if (row & (1 << x))
      {
        matrix.drawPixel(7 - x, y, LED_ON);  // 7 - x to reverse bits
      }
    }
  }

  matrix.writeDisplay();
}

char reverseBits(char b) {
   b = (b & 0xF0) >> 4 | (b & 0x0F) << 4;
   b = (b & 0xCC) >> 2 | (b & 0x33) << 2;
   b = (b & 0xAA) >> 1 | (b & 0x55) << 1;
   return b;
}

void clearScreen()
{
  // Összes kijelző "letakarítása"
    matrix0.clear();
    matrix1.clear();
    matrix2.clear();
    matrix3.clear();
    matrix4.clear();
    matrix5.clear();
    matrix6.clear();
    matrix7.clear();
    matrix0.writeDisplay();
    matrix1.writeDisplay();
    matrix2.writeDisplay();
    matrix3.writeDisplay();
    matrix4.writeDisplay();
    matrix5.writeDisplay();
    matrix6.writeDisplay();
    matrix7.writeDisplay();
}

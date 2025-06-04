# 1. feladat - A lift mozgatása és alap vezérlése

```cpp
// A motor csatlakozói
const int DIR_PIN = 10;
const int STEP_PIN = 9;
const int EN_PIN = 8;

// Minél nagyobb annál lassabb, de ne vedd túl lassúra mert akkor nem fog menni
const int Sebesseg = 200;

void setup() 
{
    // Soros port indítása
    Serial.begin(9600);

    // Csatlakozások beállítása kimenetire
    pinMode(DIR_PIN, OUTPUT);
    pinMode(STEP_PIN, OUTPUT);
    pinMode(EN_PIN, OUTPUT);

    // Kikapcsoljuk a motor működését
    digitalWrite(EN_PIN, HIGH);

    Serial.println("\n\nHello vilag");
    delay(1000); // Várjunk 1 másodpercet
}

void loop() 
{
    // 10000 lépés felfelé
    Serial.println("Mozgas fel . . .");
    digitalWrite(DIR_PIN, LOW);
    digitalWrite(EN_PIN, LOW);
    for (int i = 0; i < 10000; i++)
    {
        digitalWrite(STEP_PIN, HIGH);
        delayMicroseconds(Sebesseg);
        digitalWrite(STEP_PIN, LOW);
        delayMicroseconds(Sebesseg);
    }
    
    // 10000 lépés lefelé
    Serial.println("Mozgas le . . .");
    digitalWrite(DIR_PIN, HIGH);
    digitalWrite(EN_PIN, LOW);
    for (int i = 0; i < 10000; i++)
    {
        digitalWrite(STEP_PIN, HIGH);
        delayMicroseconds(Sebesseg);
        digitalWrite(STEP_PIN, LOW);
        delayMicroseconds(Sebesseg);
    }
}
```

# 2. feladat - Egyéb eszközök csatlakozásának tesztelése

```cpp
#include <Servo.h>
#include <Adafruit_GFX.h>
#include <Adafruit_LEDBackpack.h>

// A motor csatlakozói
const int DIR_PIN = 10;
const int STEP_PIN = 9;
const int EN_PIN = 8;

const int BTN1 = 7;
const int BTN2 = 6;
const int BTN3 = 5;

const int BUZZER_PIN = 12;
const int SERVO_PIN = 11;
const int COLLISON_PIN = 2;

Servo ajto;

Adafruit_8x8matrix matrix = Adafruit_8x8matrix();

// Minél nagyobb annál lassabb, de ne vedd túl lassúra mert akkor nem fog menni
const int Sebesseg = 200;

void setup() 
{
    // Soros port indítása
    Serial.begin(9600);

    // Csatlakozások beállítása
    pinMode(DIR_PIN, OUTPUT);
    pinMode(STEP_PIN, OUTPUT);
    pinMode(EN_PIN, OUTPUT);
    pinMode(BTN1, INPUT);
    pinMode(BTN2, INPUT);
    pinMode(BTN3, INPUT);
    pinMode(COLLISON_PIN, INPUT);

    ajto.attach(SERVO_PIN);

    matrix.begin(0x70);  // Alapértelmezett I2C cím: 0x70

    // Kikapcsoljuk a motor működését
    digitalWrite(EN_PIN, HIGH);

    Serial.println("\n\nSetup sikeres\n------");
    delay(1000); // Várjunk 1 másodpercet

    // Tesztelések amiket csak egyszer akaruk/kell
    ajto.write(0);
    delay(1000);
    ajto.write(90);
    delay(1000);

    tone(BUZZER_PIN, 200, 500);

    matrix.clear();

    matrix.setRotation(3);
    matrix.setBrightness(4);

    uint8_t smiley[8] = {
        B00111100,
        B01000010,
        B10100101,
        B10000001,
        B10100101,
        B10011001,
        B01000010,
        B00111100
    };

    // Beállítjuk a pixeleket
    for (uint8_t y = 0; y < 8; y++) {
        for (uint8_t x = 0; x < 8; x++) {
            if (smiley[y] & (1 << (7 - x))) {
                matrix.drawPixel(x, y, LED_ON);
            }
        }
    }

    matrix.writeDisplay(); // Frissítjük a kijelzőt
}

void loop() 
{

    Serial.println("Collison: " + String(digitalRead(COLLISON_PIN) == LOW));
    Serial.println("BTN1: " + String(digitalRead(BTN1) == LOW) + "\tBTN2: " + String(digitalRead(BTN2) == LOW) + "\tBTN3: " + String(digitalRead(BTN3) == LOW));
    Serial.println("------");
    delay(500);
}
```

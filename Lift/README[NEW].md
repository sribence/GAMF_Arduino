# 🛗 Lift működtetés 🚀
---

**🛗 Feladat:** Építs egy háromszintes liftet, amely egy léptetőmotor segítségével mozgatja a kabint az emeletek között! 🏢🚡 A vezérlés három nyomógombbal történik, amelyekkel kiválasztható a cél-állomás. A kabin pontos mozgatását a pozíció alapján kell vezérelni – a rendszer lineáris sín mentén dolgozik. 🔁⚙️ Minden emelet elérésekor fény- és hangjelzést kell adnia, valamint a 8x8-as LED mátrixon jelenjen meg az aktuális emeletszám és a mozgás iránya is. 💡🔊 A motor működését finomítani is lehet – például gyorsítás/lassítás hozzáadásával, hogy még valósághűbb legyen. 🐢🚀

**🛠️ Fontos:** 🧭 Minden alkatrészt pontosan a kapcsolási rajz alapján köss be! Ha máshogy nevezel el egy változót, az rendben van, de figyelj arra, hogy átlátható és jól érthető legyen a kódod. 📋✅

📌 A teljes projekt több lépésből áll, de egyetlen rendszert építünk, nem kell semmit törölni vagy átállítani, ha új funkciót adsz hozzá. 🔗 Ha valamelyik modul még nincs használva, de már be van kötve, az nem gond – hagyd nyugodtan bent! 🧠

🤓 Ha gyorsan haladsz, és szeretnél továbbgondolni a feladatot, nézd meg az extra kihívást a végén – ajtóidőzítéssel és visszaszámlálásos kijelzéssel!

---

**Tartalomjegyzék**
-   [Eszközök](#️-eszközök-amikre-szükséged-lesz)
-   [1. Feladat](#1-feladat---a-lift-mozgatása-és-alap-vezérlése)
-   [2. Feladat](#2-feladat---egyéb-eszközök-csatlakozásának-tesztelése) 
-   [3. Feladat](#3-feladat---a-lift-irányítása-gombokkal-fel-le-álj)
-   [4. Feladat](#4-feladat---a-lift-funkcióinak-alapvető-megvalósítása)
-   [5. Feladat](#5-feladat---a-lift-végleleges-működése)
-   [Teljes rendszer](#teljes-rendszer)
-   [Extra Feladat](#-extra-feladat)

---

# 🛠️ Eszközök, amikre szükséged lesz:
- Arduino UNO 🖥️⚡
- Léptetőmotor ⚙️🔄
- Motorvezérlő modul 🎛️🔌
- Lineáris sín és kabinmodell 🚠📏
- 3 db nyomógomb 🔘🔢
- 8x8 LED mátrix 🔲💡
- Végálláskapcsolók 🚫📍
- Buzzer és LED 🔊💡

---

# 1. feladat - A lift mozgatása és alap vezérlése

<img src="./ElevatorCode1.png" width="100%" />

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

<img src="./ElevatorCode2.png" width="100%" />

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

# 3. feladat - A lift irányítása gombokkal (fel, le, álj)

<img src="./ElevatorCode3.png" width="100%" />

```cpp
#include <Adafruit_GFX.h>
#include <Adafruit_LEDBackpack.h>

// A motor csatlakozói
const int DIR_PIN = 10;
const int STEP_PIN = 9;
const int EN_PIN = 8;

// Gombok
const int BTN1 = 7;
const int BTN2 = 6;
const int BTN3 = 5;

// Buzzer
const int BUZZER_PIN = 12;

// Kijelző
Adafruit_8x8matrix matrix = Adafruit_8x8matrix();

// Minél nagyobb annál lassabb, de ne vedd túl lassúra mert akkor nem fog menni
const int Sebesseg = 200;

void IranyBeallitas(String);

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

    matrix.begin(0x70);
    matrix.clear();
    matrix.setRotation(3);
    matrix.setBrightness(4);

    Serial.println("\n\nHello vilag");
    delay(1000); // Várjunk 1 másodpercet
}

void loop() 
{
    if (digitalRead(BTN1) == LOW) IranyBeallitas("fel");
    else if (digitalRead(BTN2) == LOW) IranyBeallitas("le");
    else if (digitalRead(BTN3) == LOW) IranyBeallitas("kikapcs");

    digitalWrite(STEP_PIN, HIGH);
    delayMicroseconds(Sebesseg);
    digitalWrite(STEP_PIN, LOW);
    delayMicroseconds(Sebesseg);    
}

void IranyBeallitas(String irany = "fel")
{
    tone(BUZZER_PIN, 200, 200);
    matrix.clear();

    if (irany == "fel")
    {
        uint8_t smiley[8] = {
            B00000000,
            B00010000,
            B00111000,
            B01111100,
            B00010000,
            B00010000,
            B00010000,
            B00000000
        };

        // Beállítjuk a pixeleket
        for (uint8_t y = 0; y < 8; y++) {
            for (uint8_t x = 0; x < 8; x++) {
                if (smiley[y] & (1 << (7 - x))) {
                    matrix.drawPixel(x, y, LED_ON);
                }
            }
        }

        
        digitalWrite(DIR_PIN, LOW);
        digitalWrite(EN_PIN, LOW);
    }
    else if (irany == "le")
    {
        uint8_t smiley[8] = {
            B00000000,
            B00010000,
            B00010000,
            B00010000,
            B01111100,
            B00111000,
            B00010000,
            B00000000
        };

        // Beállítjuk a pixeleket
        for (uint8_t y = 0; y < 8; y++) {
            for (uint8_t x = 0; x < 8; x++) {
                if (smiley[y] & (1 << (7 - x))) {
                    matrix.drawPixel(x, y, LED_ON);
                }
            }
        }

        digitalWrite(DIR_PIN, HIGH);
        digitalWrite(EN_PIN, LOW);
    }
    else
    {
        uint8_t smiley[8] = {
            B00000000,
            B00000000,
            B00000000,
            B01111110,
            B01111110,
            B00000000,
            B00000000,
            B00000000
        };

        // Beállítjuk a pixeleket
        for (uint8_t y = 0; y < 8; y++) {
            for (uint8_t x = 0; x < 8; x++) {
                if (smiley[y] & (1 << (7 - x))) {
                    matrix.drawPixel(x, y, LED_ON);
                }
            }
        }
    
        digitalWrite(EN_PIN, HIGH);
    }

    matrix.writeDisplay(); // Frissítjük a kijelzőt
}
```

# 4. feladat - A lift funkcióinak alapvető megvalósítása

<img src="./ElevatorCode4.png" width="100%" />

```cpp
#include <Adafruit_GFX.h>
#include <Adafruit_LEDBackpack.h>

// A motor csatlakozói
const int DIR_PIN = 10;
const int STEP_PIN = 9;
const int EN_PIN = 8;

// Gombok
const int BTN1 = 7;
const int BTN2 = 6;
const int BTN3 = 5;

// Buzzer és ütközés érzékelés
const int BUZZER_PIN = 12;
const int COLLISON_PIN = 2;

// Kijelző
Adafruit_8x8matrix matrix = Adafruit_8x8matrix();

// Minél nagyobb annál lassabb, de ne vedd túl lassúra mert akkor nem fog menni
const int Sebesseg = 200;

// A lift pozíciója
long Magassag;

// Az emeletek magassága
const long Emeletek[3] = { 0, 30000, 60000 };

// Függvény és eljárás deklarációk
void IranyBeallitas(String);
void MozgasEmelethez(int);

void setup() 
{
    // Soros port indítása
    Serial.begin(9600);

    // Csatlakozások beállítása kimenetire
    pinMode(DIR_PIN, OUTPUT);
    pinMode(STEP_PIN, OUTPUT);
    pinMode(EN_PIN, OUTPUT);
    pinMode(COLLISON_PIN, INPUT);

    // Kikapcsoljuk a motor működését
    digitalWrite(EN_PIN, HIGH);

    matrix.begin(0x70);
    matrix.clear();
    matrix.setRotation(3);
    matrix.setBrightness(4);

    Serial.println("\n\nHello vilag");
    delay(1000); // Várjunk 1 másodpercet

    // Home-olás (visszamegyünk a kezdő pozícióba és a mozgást ahhoz viszonyítjuk utánna)
    IranyBeallitas("le");
    while (digitalRead(COLLISON_PIN) == HIGH)
    {
        Leptetes();
    }
    IranyBeallitas("kikapcs");

    IranyBeallitas("fel");
    for (int i = 0; i < 2000; i++)
    {
        Leptetes();
    }
    IranyBeallitas("kikapcs");
    Magassag = 0;

    matrix.clear();

    uint8_t smiley[8] = {
        B00000000,
        B00111100,
        B01000010,
        B01000000,
        B01001110,
        B01000010,
        B00111100,
        B00000000
    };

    // Beállítjuk a pixeleket
    for (uint8_t y = 0; y < 8; y++) {
        for (uint8_t x = 0; x < 8; x++) {
            if (smiley[y] & (1 << (7 - x))) {
                matrix.drawPixel(x, y, LED_ON);
            }
        }
    }

    matrix.writeDisplay();
}

void loop() 
{
    if (digitalRead(BTN1) == LOW) MozgasEmelethez(0);
    else if (digitalRead(BTN2) == LOW) MozgasEmelethez(1);
    else if (digitalRead(BTN3) == LOW) MozgasEmelethez(2);
}

// Egy lépés a léptető motorral
void Leptetes()
{
    digitalWrite(STEP_PIN, HIGH);
    delayMicroseconds(Sebesseg);
    digitalWrite(STEP_PIN, LOW);
    delayMicroseconds(Sebesseg);
}

// Eldüntjük hogyan mozogjon az eszköz a célemelethez és a jelenlegi pozicíóhoz képest
// 0 -> földszint
// 1 -> 1. emelet
// 2 -> 2. emelet
void MozgasEmelethez(int emelet = 0)
{
    // Ha nem jó emelet lett megadva, ne csináljon semmit
    if (emelet < 0 || emelet > 2) return;

    // Motor mozgásának száma
    long Lepesszam = 0;
    if (Magassag == 0)
    {
        Lepesszam = abs(Magassag - Emeletek[emelet]);
    }
    else
    {
        Lepesszam = abs(Emeletek[emelet] - Magassag);
    }


    // Ha a liftnek nem kell mozogni, ne csináljon semmit
    if (Lepesszam == 0) return;

    // Irány meghatározása
    Serial.println(String(Magassag) + " - " + String(Emeletek[emelet]));
    if (Magassag < Emeletek[emelet]) IranyBeallitas("fel");
    else IranyBeallitas("le");

    // Lépések megtétele
    for (long i = 0; i < Lepesszam; i++) Leptetes();

    // Az új magasság frissítése
    Magassag = Emeletek[emelet];

    IranyBeallitas("kikapcs");

    // Emelet számának kiírása
    matrix.clear();
    if (Magassag == Emeletek[0])
    {
        uint8_t smiley[8] = {
            B00000000,
            B00111100,
            B01000010,
            B01000000,
            B01001110,
            B01000010,
            B00111100,
            B00000000
        };

        // Beállítjuk a pixeleket
        for (uint8_t y = 0; y < 8; y++) {
            for (uint8_t x = 0; x < 8; x++) {
                if (smiley[y] & (1 << (7 - x))) {
                    matrix.drawPixel(x, y, LED_ON);
                }
            }
        }
    }
    else if (Magassag == Emeletek[1])
    {
        uint8_t smiley[8] = {
            B00000000,
            B00001000,
            B00011000,
            B00001000,
            B00001000,
            B00001000,
            B00011100,
            B00000000
        };

        // Beállítjuk a pixeleket
        for (uint8_t y = 0; y < 8; y++) {
            for (uint8_t x = 0; x < 8; x++) {
                if (smiley[y] & (1 << (7 - x))) {
                    matrix.drawPixel(x, y, LED_ON);
                }
            }
        }
    }
    else if (Magassag == Emeletek[2])
    {
        uint8_t smiley[8] = {
            B00000000,
            B00011000,
            B00100100,
            B00001000,
            B00010000,
            B00100000,
            B00111100,
            B00000000
        };

        // Beállítjuk a pixeleket
        for (uint8_t y = 0; y < 8; y++) {
            for (uint8_t x = 0; x < 8; x++) {
                if (smiley[y] & (1 << (7 - x))) {
                    matrix.drawPixel(x, y, LED_ON);
                }
            }
        }
    }

    matrix.writeDisplay(); // Frissítjük a kijelzőt
}

void IranyBeallitas(String irany = "fel")
{
    tone(BUZZER_PIN, 200, 200);
    matrix.clear();

    if (irany == "fel")
    {
        uint8_t smiley[8] = {
            B00000000,
            B00010000,
            B00111000,
            B01111100,
            B00010000,
            B00010000,
            B00010000,
            B00000000
        };

        // Beállítjuk a pixeleket
        for (uint8_t y = 0; y < 8; y++) {
            for (uint8_t x = 0; x < 8; x++) {
                if (smiley[y] & (1 << (7 - x))) {
                    matrix.drawPixel(x, y, LED_ON);
                }
            }
        }

        
        digitalWrite(DIR_PIN, LOW);
        digitalWrite(EN_PIN, LOW);
    }
    else if (irany == "le")
    {
        uint8_t smiley[8] = {
            B00000000,
            B00010000,
            B00010000,
            B00010000,
            B01111100,
            B00111000,
            B00010000,
            B00000000
        };

        // Beállítjuk a pixeleket
        for (uint8_t y = 0; y < 8; y++) {
            for (uint8_t x = 0; x < 8; x++) {
                if (smiley[y] & (1 << (7 - x))) {
                    matrix.drawPixel(x, y, LED_ON);
                }
            }
        }

        digitalWrite(DIR_PIN, HIGH);
        digitalWrite(EN_PIN, LOW);
    }
    else
    {
        uint8_t smiley[8] = {
            B00000000,
            B00000000,
            B00000000,
            B01111110,
            B01111110,
            B00000000,
            B00000000,
            B00000000
        };

        // Beállítjuk a pixeleket
        for (uint8_t y = 0; y < 8; y++) {
            for (uint8_t x = 0; x < 8; x++) {
                if (smiley[y] & (1 << (7 - x))) {
                    matrix.drawPixel(x, y, LED_ON);
                }
            }
        }
    
        digitalWrite(EN_PIN, HIGH);
    }

    matrix.writeDisplay(); // Frissítjük a kijelzőt
}
```

# 5. feladat - A lift végleleges működése

<img src="./ElevatorCode5.png" width="100%" />

```cpp
#include <Arduino.h>
#include <Wire.h>
#include <Servo.h>
#include <Adafruit_LEDBackpack.h>
#include <Adafruit_GFX.h>

#define CS_PIN 2

#define DIR_PIN 10
#define STEP_PIN 9
#define EN_PIN 8

#define SERVO_PIN 11

#define BUZZER_PIN 12

const byte gomb[3] = {5, 6, 7};

Adafruit_8x8matrix matrix = Adafruit_8x8matrix();
Servo ajto;
byte ajto_poz = 0;
int motor_var = 0;
const int var_gyors = 200;
const int var_lassu = 400;
long poz = 0;
long cel_poz = 0;
long frissit = 0;
const long emelet_tavolsag = 30000;
const long atmenet = 3000;
byte emelet = 0;
byte cel_emelet = 0;
enum Irany {
    LE,
    FEL,
    NINCS,
};
Irany irany;
enum Allapot {
    STOP,
    VARAKOZAS,
    START,
    AJTONYITAS,
    AJTO_NYITVA,
    AJTOZARAS,
    INDULAS,
    MOZGASBAN,
    ERKEZES,
};
volatile Allapot allapot;

byte reverse(byte b) {
   b = (b & 0xF0) >> 4 | (b & 0x0F) << 4;
   b = (b & 0xCC) >> 2 | (b & 0x33) << 2;
   b = (b & 0xAA) >> 1 | (b & 0x55) << 1;
   return b;
}

byte rotr(byte val) {
    return (val >> 1) | (val << 7);
}

const uint16_t szam[4][5] = {
    {
        0b00000111,
        0b00000100,
        0b00000111,
        0b00000100,
        0b00000100,
    },
    {
        0b00000010,
        0b00000110,
        0b00000010,
        0b00000010,
        0b00000010,
    },
    {
        0b00000110,
        0b00000001,
        0b00000010,
        0b00000100,
        0b00000111,
    },
    {
        0b00000000,
        0b00000000,
        0b00000111,
        0b00000000,
        0b00000000,
    },
};

const uint16_t nyil[3][5] = {
    {
        0b00000010,
        0b00000010,
        0b00000010,
        0b00000111,
        0b00000010,
    },
    {
        0b00000010,
        0b00000111,
        0b00000010,
        0b00000010,
        0b00000010,
    },
    {
        0b00000000,
        0b00000000,
        0b00000000,
        0b00000000,
        0b00000000,
    },
};

void matrix_kiir() {
    for (byte i = 0; i < 5; ++i) {
        matrix.displaybuffer[i + 1] = rotr((reverse(nyil[irany][i]) >> 5) | (reverse(szam[emelet][i]) >> 1));
    }
    matrix.writeDisplay();
}

void serial_kiir() {
    Serial.print("a: ");
    Serial.print(allapot);
    Serial.print(", e: ");
    Serial.print(emelet);
    Serial.print(", ce: ");
    Serial.print(cel_emelet);
    Serial.print(", p: ");
    Serial.print(poz);
    Serial.print(", cp: ");
    Serial.print(cel_poz);
    Serial.println();
}

void leptet() {
    digitalWrite(STEP_PIN, HIGH);
    delayMicroseconds(motor_var);
    digitalWrite(STEP_PIN, LOW);
    delayMicroseconds(motor_var);
}

void allapotot_frissit(Allapot uj) {
    if (allapot == STOP) {
        return;
    }
    allapot = uj;
}

void iranyt_frissit(Irany uj) {
    irany = uj;
    switch (irany) {
        case FEL:
            digitalWrite(DIR_PIN, LOW);
            digitalWrite(EN_PIN, LOW);
            break;
        case LE:
            digitalWrite(DIR_PIN, HIGH);
            digitalWrite(EN_PIN, LOW);
            break;
        default:
            digitalWrite(EN_PIN, HIGH);
            break;
    }
}

void stop() {
    if (allapot == START) {
        return;
    }
    allapot = STOP;
}

void poziciot_frissit() {
    switch (irany) {
        case FEL:
            ++poz;
            break;
        case LE:
            --poz;
            break;
        default:
            break;
    }
}

void emeletet_frissit_indulaskor() {
    frissit = poz;
    switch (irany) {
        case FEL:
            frissit += emelet_tavolsag / 2;
            break;
        case LE:
            frissit -= emelet_tavolsag / 2;
            break;
        default:
            break;
    }
}

void emeletet_frissit() {
    if (poz != frissit) {
        return;
    }
    switch (irany) {
        case FEL:
            ++emelet;
            frissit += emelet_tavolsag;
            break;
        case LE:
            --emelet;
            frissit -= emelet_tavolsag;
            break;
        default:
            break;
    }
    matrix_kiir();
}

void ajtot_mozgat(int poz) {
    ajto.attach(SERVO_PIN);
    while (ajto_poz != poz) {
        ajto_poz < poz ? ++ajto_poz : --ajto_poz;
        ajto.write(ajto_poz);
        delay(10);
    }
    delay(500);
    ajto.detach();
}

void hang() {
    tone(BUZZER_PIN, 200);
    delay(500);
    noTone(BUZZER_PIN);
}

void setup() {
    Serial.begin(9600);
    Serial.println();
    Serial.println("Setup started");
    attachInterrupt(digitalPinToInterrupt(CS_PIN), stop, FALLING);
    matrix.begin(0x70);
    pinMode(DIR_PIN, OUTPUT);
    pinMode(STEP_PIN, OUTPUT);
    pinMode(EN_PIN, OUTPUT);
    digitalWrite(EN_PIN, HIGH);
    pinMode(BUZZER_PIN, OUTPUT);
    allapot = STOP;
    Serial.println("Setup completed");
}

void loop() {
    switch (allapot) {
        case STOP:
            emelet = 3;
            iranyt_frissit(NINCS);
            matrix_kiir();
            serial_kiir();
            Serial.println("Stop");
            delay(1000);
            allapot = VARAKOZAS;
            break;
        case VARAKOZAS:
        {
            unsigned long start = millis();
            while (!digitalRead(gomb[0])) {
                if (millis() - start > 2000) {
                    allapotot_frissit(START);
                    return;
                }
            }
            break;
        }
        case START:
            emelet = 3;
            iranyt_frissit(LE);
            matrix_kiir();
            ajtot_mozgat(10);
            delay(4000);
            motor_var = 300;
            while (digitalRead(CS_PIN)) {
                leptet();
            }
            iranyt_frissit(FEL);
            matrix_kiir();
            for (long i = 0; i < 10000; ++i) {
                leptet();
            }
            poz = 0;
            emelet = 0;
            iranyt_frissit(NINCS);
            allapotot_frissit(AJTONYITAS);
            matrix_kiir();
            serial_kiir();
            break;
        case AJTONYITAS:
            delay(2000);
            ajtot_mozgat(170);
            delay(2000);
            allapotot_frissit(AJTO_NYITVA);
            break;
        case AJTO_NYITVA:
            for (byte i = 0; i < 3; ++i) {
                if (i != emelet && !digitalRead(gomb[i])) {
                    cel_emelet = i;
                    cel_poz = cel_emelet * emelet_tavolsag;
                    iranyt_frissit(cel_emelet > emelet ? FEL : LE);
                    emeletet_frissit_indulaskor();
                    allapotot_frissit(AJTOZARAS);
                    matrix_kiir();
                    serial_kiir();
                    break;
                }
            }
            break;
        case AJTOZARAS:
            delay(2000);
            ajtot_mozgat(10);
            delay(2000);
            allapotot_frissit(INDULAS);
            break;
        case INDULAS:
            for (long i = 0; i < atmenet; ++i) {
                motor_var = var_gyors + (1 - ((float)i / atmenet)) * (var_lassu - var_gyors);
                leptet();
                poziciot_frissit();
                if (allapot == STOP) {
                    return;
                }
            }
            allapotot_frissit(MOZGASBAN);
            break;
        case MOZGASBAN:
            motor_var = var_gyors;
            while (abs(cel_poz - poz) > atmenet) {
                leptet();
                poziciot_frissit();
                emeletet_frissit();
                if (allapot == STOP) {
                    return;
                }
            }
            allapotot_frissit(ERKEZES);
            break;
        case ERKEZES:
            for (long i = 0; i < atmenet; ++i) {
                motor_var = var_gyors + ((float)i / atmenet) * (var_lassu - var_gyors);
                leptet();
                poziciot_frissit();
                if (allapot == STOP) {
                    return;
                }
            }
            iranyt_frissit(NINCS);
            allapotot_frissit(AJTONYITAS);
            matrix_kiir();
            serial_kiir();
            hang();
            break;
    }
}
```

# Teljes rendszer
**A teljes liftvezérlő rendszer vezérlése**🚀

📌 Feladatleírás: A projekt célja egy liftmodell létrehozása, amely három emelet között mozgat egy kabint léptetőmotor segítségével. 🚀

🛗 Rendszer elemei:
- Léptetőmotor ( NEMA 17 ) ⚙️🔄
- Motorvezérlő modul ( A4988 vagy ULN2003 ) 🎛️🔌
- Lineáris sín és kabinmodell 🚠📏
- 3 db nyomógomb (  emeletválasztáshoz) 🔘🔢
- 8x8 LED mátrix ( emeletszám kijelzéshez ) 🔲💡
- Végálláskapcsolók ( referenciapont érzékeléshez ) 🚫📍
- Buzzer és LED ( jelzésekhez ) 🔊💡

🚀 Program működése:
- Emeletválasztás: A felhasználó három nyomógombbal választhatja ki a kívánt emeletet 🏠🔘🏠 
- Pozícióvezérlés: A rendszer léptetőmotor segítségével mozgatja a kabint a lineáris sínen ⚙️📏 
- LED Mátrix kijelzés: Az aktuális emeletszám és mozgásirány a 8x8 LED mátrixon jelenik meg 📟💡 
- Ajtó működése: A kabin ajtaja egy szervomotorral nyílik és záródik 🚪🔄 
- Hang- és fényjelzés: Minden emelet elérésekor buzzer és LED figyelmezteti a felhasználót 🔊✨ 
- Motorvezérlés finomhangolása: A gyorsítás/lassítás fokozatosan történik 🚀🐢

---

# **🏆 Extra feladat:**  
**🛠️ Extra feladat:** Ha elkészült az alap projekt, és van kedved feltúrbózni, itt egy gondolkodós kihívás! 🤔

**📌 Időzített ajtónyitás és automatikus visszazárás:** A lift ajtaja ne csak manuálisan nyíljon és záródjon, hanem időzített módon működjön, és figyelje, hogy egy bizonyos idő elteltével automatikusan bezáródjon.

**🏆 Extra kihívás:** 👀 Jelenítsd meg a visszaszámlálást a LED kijelzőn – a hátralévő másodperceket mutassa! 

✅ Sok sikert! 😊

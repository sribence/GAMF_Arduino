# 🟩 8x8 LED Mátrix – Snake Játék Arduino Projekttel

Ez a projekt egy **kis kijelzős videojátékot** valósít meg egy 8x8 LED mátrix kijelzőn – egy olyan táblán, ahol 64 kis pont világít vagy nem világít. Ezeket úgy irányítjuk, hogy **rajzolni vagy mozgatni tudjunk** dolgokat rajta, például karaktereket, képeket vagy akár egy **kígyót, ami a játékban mozog**.

A játék, amit megépítünk, a klasszikus Snake: a képernyőn egy vonalként mozgó kígyó növekszik, ha **"ételt"** vesz fel, és a cél, hogy ne ütközzön neki semminek – se a falnak, se saját magának.

A projekt **lépésenként halad**, és minden új lépés egy kicsivel érdekesebbé és ügyesebbé teszi az egész játékot!


---

## 📦 Tartalom

- [Alkatrészek](#alkatrészek)
- [Kapcsolás](#kapcsolás)
- [Funkciók lépésenként](#funkciók-lépésenként)
- [Kódok és magyarázatok](#kódok-és-magyarázatok)
- [Képek](#képek)
- [Extra ötletek](#extra-ötletek)

---

## 🧰 Alkatrészek

| Eszköz              | Darabszám |
|---------------------|-----------|
| Arduino UNO         | 1         |
| 8x8 LED mátrix  | 1         |
| Nyomógomb           | 4         |
| Ellenállás (10kΩ)   | 4         |
| Breadboard + Jumperek | -       |
| Tápellátás USB-n keresztül | 1   |

---

## 🧠 Kapcsolás

📷 ÁBRÁK
![8x8 matrix connecting diagram](/2.%20feladat/2-1.png)
> _Figure 1: 8x8 mátrix bekötése


### De hogy működik a 8x8 LED mátrix? 
![image](https://github.com/user-attachments/assets/8b52e76f-8c48-42cd-801e-8d9089ad0fbf)

Egy 8x8-as LED mátrix belsőleg sorokba (R1–R8) és oszlopokba (C1–C8) rendezett LED-ekből áll, ahol minden LED egy sor- és egy oszlopvezeték találkozásánál helyezkedik el. A LED-ek vezérléséhez multiplexelést használnak: egyszerre csak egy sort aktiválnak, és az adott sor oszlopaiban vezérlik a világítandó LED-eket, majd gyorsan váltanak a sorok között, így a kijelző folyamatosan világítónak tűnik.

---

## 🧭 Funkciók lépésenként

### ✅ Alap kijelzés
- LED mátrix inicializálása
- Egyszerű karakter vagy szám megjelenítése

### ✅ Snake játék alapverzió
- Kígyó mozgatása a kijelzőn
- Növekedés étel felvétele után
- Irányváltás 4 gombbal

### ✅ Extra mód
- Akadályokat helyezünk a pályára
- Ütközésvizsgálat

---

## 💻 Kódok és magyarázatok

### ✅ 1. LED mátrix inicializálása (Adafruit HT16K33)
A LED mátrix eleinte csak egy-egy pontot vagy egyszerű ábrát mutat. Ez segít abban, hogy megértsük, hogyan lehet egy képernyőt programból vezérelni. Ilyen lehet például egy mosolygós arc vagy számok.


```cpp
#include <Wire.h>
#include <Adafruit_GFX.h>         // Telepíteni kell
#include <Adafruit_LEDBackpack.h> // Telepíteni kell

Adafruit_8x8matrix matrix = Adafruit_8x8matrix();

void setup() 
{
    matrix.begin(0x70);     // I2C cím
    matrix.setRotation(0);  // Orientáció, el lehet forgatni a "képet" a mátrixon
    matrix.clear();
    matrix.writeDisplay();
}

void loop() 
{
    matrix.clear();
    matrix.drawPixel(3, 3, LED_ON); // 0-tól kezdjük a számozást
    matrix.writeDisplay();
    delay(500);
}
```
> [!NOTE]
> Az Adafruit_LEDBackpack könyvtár egyszerű vezérlést tesz lehetővé HT16K33 mátrixhoz. A drawPixel(x,y,LED_ON) függvényekkel kirajzolhatunk pontokat.
---

### 🔢 Saját karakter vagy szám kijelzése

  ```cpp
#include <Wire.h>
#include <Adafruit_GFX.h>         // Telepíteni kell
#include <Adafruit_LEDBackpack.h> // Telepíteni kell

Adafruit_8x8matrix matrix = Adafruit_8x8matrix();

// Az első oszlop-ot a legelső helyre kell írni majd a második oszloptól hadava normál sorrendben kell haladni
static const uint8_t smiley[] = {
    B00011110,
    B00100001,
    B11010010,
    B11000000,
    B11010010,
    B11001100,
    B00100001,
    B00011110
};

void setup() 
{
    matrix.begin(0x70);     // I2C cím
    matrix.setRotation(0);  // Orientáció, el lehet forgatni a "képet" a mátrixon
    matrix.clear();
    matrix.writeDisplay();
}

void loop() 
{
    matrix.clear();
    for (int i = 0; i < 8; i++) 
    {
        matrix.displaybuffer[i] = smiley[i];  // Végigmegyünk a sorokon és elmentjük a kirajzolandók listájába
    }
    matrix.writeDisplay();
    delay(1000);
}
```

> [!NOTE]
> A displaybuffer tömböt közvetlenül is módosíthatjuk saját bitmintával. Itt egy smiley arc jelenik meg.

---
###  2. 🐍 Snake játék alap
Elkészítünk egy működő kígyó játékot, ami egy adott irányba mozog, és minden lépés után új pozíciót vesz fel a kijelzőn. A kígyó egyre hosszabb lesz, ha sikerül "ennie" (ezt később adjuk hozzá). Ha falba ütközik, újrakezdődik.

Ez már egy valódi, mini videojáték, amit mi programozunk meg és irányítunk!


```cpp
#include <Wire.h>
#include <Adafruit_LEDBackpack.h> // Telepíteni kell

Adafruit_8x8matrix matrix = Adafruit_8x8matrix();

int snakeX[64];
int snakeY[64];
int length = 3; // Kígyó hossza
int dir = 0;    // 0: jobbra, 1: le, 2: balra, 3: fel

void setup() 
{
    matrix.begin(0x70);
    snakeX[0] = 3; snakeY[0] = 3;
    snakeX[1] = 2; snakeY[1] = 3;
    snakeX[2] = 1; snakeY[2] = 3;
}

void loop() 
{
    delay(300);
    moveSnake();
    drawSnake();
}

void moveSnake() 
{
    for (int i = length - 1; i > 0; i--) 
    {
        snakeX[i] = snakeX[i - 1];
        snakeY[i] = snakeY[i - 1];
    }

    if (dir == 0) snakeX[0]++;
    if (dir == 1) snakeY[0]++;
    if (dir == 2) snakeX[0]--;
    if (dir == 3) snakeY[0]--;

    // egyszerű ütközés
    if (snakeX[0] < 0 || snakeX[0] > 7 || snakeY[0] < 0 || snakeY[0] > 7) 
    {
        length = 3;
        snakeX[0] = 3; snakeY[0] = 3;
        snakeX[1] = 2; snakeY[1] = 3;
        snakeX[2] = 1; snakeY[2] = 3;
    }
}

void drawSnake() {
    matrix.clear();
    for (int i = 0; i < length; i++) 
    {
        matrix.drawPixel(snakeX[i], snakeY[i], LED_ON);
    }
    matrix.writeDisplay();
}
```
> [!NOTE]
> Ez az alap Snake algoritmus megvalósítja a kígyó növekedését és mozgását, egyszerű határfigyeléssel. Irányváltás még nincs benne, de azt gombokkal bővítjük.
---

###  3. 🎮 Gombok bekötése és irányítás
Ezután 4 nyomógomb segítségével lehet balra, jobbra, felfelé vagy lefelé mozgatni a kígyót. Ezzel azt tanuljuk meg, hogyan lehet felhasználói bemenetekre reagálni: ha a játékos nyom egy gombot, a program máshogy viselkedik.
![8x8 matrix connecting diagram](/2.%20feladat/2-2-2.png)
> _Figure 2: 8x8 mátrix és gombok bekötése_


```cpp
#include <Wire.h>
#include <Adafruit_LEDBackpack.h> // Telepíteni kell

Adafruit_8x8matrix matrix = Adafruit_8x8matrix();

int snakeX[64];
int snakeY[64];
int length = 3; // Kígyó hossza
int dir = 0;    // 0: jobbra, 1: le, 2: balra, 3: fel

const int JOYSTICK_X = A0;
const int JOYSTICK_Y = A1;

const int JOYSTICK_DEADZONE_RADIUS = 150;
int LimitT = 512 + JOYSTICK_DEADZONE_RADIUS;
int LimitB = 512 - JOYSTICK_DEADZONE_RADIUS;
int x, y;
bool IsJoyStickMoved = false;

unsigned int Ido;

void setup() 
{
    matrix.begin(0x70);
    snakeX[0] = 3; snakeY[0] = 3;
    snakeX[1] = 2; snakeY[1] = 3;
    snakeX[2] = 1; snakeY[2] = 3;

    Ido = millis();
}

void loop() 
{
    JoystickBemenet();
    JoystickIrany();
    if (millis() - Ido >= 300)
    {
        moveSnake();
        drawSnake();
        Ido = millis();
    }
}

void moveSnake() 
{
    for (int i = length - 1; i > 0; i--) 
    {
        snakeX[i] = snakeX[i - 1];
        snakeY[i] = snakeY[i - 1];
    }

    if (dir == 0) snakeX[0]++;
    if (dir == 1) snakeY[0]++;
    if (dir == 2) snakeX[0]--;
    if (dir == 3) snakeY[0]--;

    // egyszerű ütközés
    if (snakeX[0] < 0 || snakeX[0] > 7 || snakeY[0] < 0 || snakeY[0] > 7) 
    {
        length = 3;
        snakeX[0] = 3; snakeY[0] = 3;
        snakeX[1] = 2; snakeY[1] = 3;
        snakeX[2] = 1; snakeY[2] = 3;
    }
}

void drawSnake() {
    matrix.clear();
    for (int i = 0; i < length; i++) 
    {
        matrix.drawPixel(snakeX[i], snakeY[i], LED_ON);
    }
    matrix.writeDisplay();
}

void JoystickBemenet()
{
    x = analogRead(JOYSTICK_X);
    y = analogRead(JOYSTICK_Y);
}

void JoystickIrany()
{
    // Save the move
    String JoyStickMove = "";

    // If joystick moved up and isn't checked before then register the movement
    if (IsJoyUp() && !IsJoyStickMoved)
    {
        JoyStickMove = "up";
        IsJoyStickMoved = true;
        dir = 3; // Menjünk felfelé
    }

    // If joystick moved down and isn't checked before then register the movement
    else if (IsJoyDown() && !IsJoyStickMoved)
    {
        JoyStickMove = "down";
        IsJoyStickMoved = true;
        dir = 1; // Menjünk lefelé
    }

    // If joystick moved left and isn't checked before then register the movement
    else if (IsJoyLeft() && !IsJoyStickMoved)
    {
        JoyStickMove = "left";
        IsJoyStickMoved = true;
        dir = 2; // Menjünk balra
    }

    // If joystick moved right and isn't checked before then register the movement
    else if (IsJoyRight() && !IsJoyStickMoved)
    {
        JoyStickMove = "right";
        IsJoyStickMoved = true;
        dir = 0; // Menjünk jobbra
    }

    // If joystick is in the deadzone then let registering possible again
    else if (IsJoyInDeadzone() && IsJoyStickMoved)
    {
        IsJoyStickMoved = false;
    }
}

// Checks if the joystick is moved up
bool IsJoyUp()
{
    bool ConditionX = x < LimitT && x > LimitB;     // Is in deadzone of x
    bool ConditionY = y > LimitT;                   // Is over the top limit of y

    if (ConditionX && ConditionY) return true;
    return false;
}

// Checks if the joystick is moved down
bool IsJoyDown()
{
    bool ConditionX = x < LimitT && x > LimitB;     // Is in deadzone of x
    bool ConditionY = y < LimitB;                   // Is under the bottom limit of y

    if (ConditionX && ConditionY) return true;
    return false;
}

// Checks if the joystick is moved left
bool IsJoyLeft()
{
    bool ConditionX = x < LimitB;                   // Is under the bottom limit of x
    bool ConditionY = y < LimitT && y > LimitB;     // Is in deadzone of y

    if (ConditionX && ConditionY) return true;
    return false;
}

// Checks if the joystick is moved right
bool IsJoyRight()
{
    bool ConditionX = x > LimitT;                   // Is over the top limit of x
    bool ConditionY = y < LimitT && y > LimitB;     // Is in deadzone of y

    if (ConditionX && ConditionY) return true;
    return false;
}

// Checks if the joystick is in the deadzone
bool IsJoyInDeadzone()
{
    bool ConditionX = x < LimitT && x > LimitB;     // Is in deadzone of x
    bool ConditionY = y < LimitT && y > LimitB;     // Is in deadzone of y

    if (ConditionX && ConditionY) return true;
    return false;
}
```
---
🎓 Mit tanulunk ebből?
- Hogyan működik egy LED mátrix kijelző: pontokat hogyan világítunk fel.
- Mit jelent az, hogy egy karaktert vagy képet bitmintával tárolunk.
- Hogyan rajzoljunk mozgó dolgokat a kijelzőre (kígyó mozgás).
- Hogyan lehet irányt váltani gombnyomásra – ez az egyik alapja az interaktív programozásnak.
- Hogyan működik az ütközésvizsgálat, és miként kezeljük a játék végét.
- Mit jelent egy egyszerű játéklogika – ha A történik, akkor B következik.
- Hogyan lehet a játékot fokozatosan bővíteni új ötletekkel (akadály, csipogó, étel, saját testbe ütközés).
- Hogyan lehet egy egyszerű eszközből valódi játékélményt kihozni saját kézzel.
---

🔁 Extra ötletek
 🧱 Pálya akadályokkal: rajzold ki fix blokkokat, ahol a kígyó nem haladhat át

 🍎 Véletlenszerű "kaja" a kijelzőn – ha megeszi, nő a kígyó

 💥 Ütközés saját testtel (haladó szint)

 🎵 Hangjelzés gombnyomásra vagy játék végén (csipogóval)
---

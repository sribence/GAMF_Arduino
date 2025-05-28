# EspSnake vezérlése 🐍

Ebben a projektben két ESP32 mikrokontroller együttműködésével valósul meg egy kétszemélyes Snake játék. A kijelzőfelületet 8 db 8x8 LED mátrix alkotja, amelyek 2 sorba, 4-4-es elrendezésben vannak sorba kötve. Az egyik ESP32 fogadja a saját játékos joystick bemenetét, míg a másik ESP32-től ESP-NOW protokollon keresztül megkapja a másik játékos irányítását. A két irányítási adatot összevetve egyetlen játékképernyőt rajzol ki a mátrixokra, így lehetővé válik a Snake PvP üzemmód. A projekt során a résztvevők megismerik az ESP-NOW kommunikáció alapjait, mátrixkezelést, játékszabály-implementációt, és többkijelzős grafikus megjelenítést.

**🛠️ Fontos:** 📝 mindent a rajz alapján csináljatok, mert így biztosított a tökéletes működés. A progranban az elnevezések relatívak, nem muszáj azt használni. Ha mást használtok, akkor figyeljetek arra, hogy könnyen lehessen azonosítani az egyes vátozó neveket. 🔍

🤓 Aki foglalkozott már hasonlóval és szertne egy kicsit bonyolultabb feladaton gondolkodni annak van egy **exta feladat** a füzet végén. 📖💡

🔗 Minden feladatrész ugyanahoz a feladathoz tartozik. A feladatok között nem kell semmit átállítani, vagy megváltoztani. Ha egy feladatban egy elemet nem használsz és be van kötve attól nem lesz rossz, nem kell kivenni az alapból. 🔄✅

---
**Tartalomjegyzék:**
-   [Eszközök](#️-eszközök-amikre-szükséged-lesz)
-   [0. Feladat](#0-feladat)
-   [1. Feladat](#1-feladat)
-   [2. Feladat](#2-feladat) 
-   [3. Feladat](#3-feladat)
-   [4. Feladat](#4-feladat)
-   [Teljes rendszer](#a-teljes-rendszer-működtetése)
-   [Extra Feladat](#extra-feladat)

---

# 🛠️ Eszközök, amikre szükséged lesz:
- 🧠 2 db ESP32 mikrokontroller
- 🟦 8 db 8×8 LED mátrix
- 🎮 2 db joystick modul
- 📡 ESP-NOW protokoll
- 🎯 Kettős vezérlés, közös játéktér frissítéssel

---

# 0. Feladat:
⚙️ Kapcsolási rajz: (Először ez alapján csináljátok meg a kezdő állapotot.) 
![kapcsolási rajz](bekotes.png)

---

# 8x8 LED Mátrix Tutorial - Haladó útmutató

Üdv! Ha középiskolás vagy és érdeklődsz az ESP32 mikrokontrollerek iránt, ez a tutorial segít megérteni a 8x8 LED mátrixok használatát egy gyakorlati projektben. Elmagyarázom a kulcskoncepciókat, mint az I2C címzés, pixelkezelés és animáció, lépésről lépésre, de már egy kicsit mélyebben, hogy lásd, hogyan épül fel egy ilyen rendszer. Használd ki a példákat kódoláshoz!

## 1. Lépés: Inicializálás (Ébreszd fel a mátrixot)
Az I2C protokollon keresztül kommunikálunk a mátrixokkal, ami azt jelenti, hogy mindegyiknek egyedi címet adunk (pl. 0x70). Ez biztosítja, hogy az ESP32 külön-külön irányíthassa őket. Példa:
```cpp
matrix0.begin(0x70);  // Inicializálja az első mátrixot az I2C címen
// Miért fontos? Ha nem adsz címet, az ESP32 nem tudja, melyik mátrixnak küldje az adatokat.
```

## 2. Lépés: Kijelző törlése (Clear screen)
Mielőtt rajzolsz, töröld a mátrixot, hogy tiszta felületen dolgozhass. Ez a mátrix memóriájának nullázását jelenti:
```cpp
matrix0.clear();  // Törli a mátrix tartalmát
matrix0.writeDisplay();  // Frissíti a kijelzőt
// Technikailag ez a mátrix bufferét üríti, ami gyorsabbá teszi a frissítéseket.
```

## 3. Lépés: Egyetlen pixel kirajzolása
A mátrix 64 pixelből (8x8) áll, és pixelenként vezérelheted őket. Ez alapvető a grafikus megjelenítéshez:
```cpp
matrix0.drawPixel(3, 4, LED_ON);  // Bekapcsol egy pixelt a 3. oszlopban, 4. sorban
matrix0.writeDisplay();  // Láthatod a változást
// Példa bővítése: Kipróbálhatod, hogyan rajzolsz egy vonalat több pixelből: for ciklusokkal sorban bekapcsolhatsz pixeleket.
```

## 4. Lépés: Alakzat kirajzolása (Pl. számok vagy formák)
Használhatsz tömböket, hogy komplexebb mintákat rajzolj, mint egy számot. Ez már a bitek manipulációjára épül:
```cpp
const uint8_t num1[] = {B00000000, B00010000, B00110000, B00010000, B00010000, B00010000, B00111000, B00000000};
for (uint8_t y = 0; y < 8; y++) {
    for (uint8_t x = 0; x < 8; x++) {
        if (num1[y] & (1 << x)) {
            matrix0.drawPixel(7 - x, y, LED_ON);  // Bitek alapján rajzol
        }
    }
}
matrix0.writeDisplay();  // Megjeleníti a számot
// Miért bitsor? Ez hatékony, mert kis memóriával dolgozunk az ESP32-n.
```

## 5. Lépés: Animáció és több mátrix kezelése
Hozd mozgásba a mátrixot! Például villogasd a pixelt, vagy szinkronizáld több mátrixot:
```cpp
void loop() {
    matrix0.clear();
    matrix0.drawPixel(3, 4, LED_ON);  // Első pixel bekapcsolása
    matrix0.writeDisplay();
    delay(500);  // 0.5 másodperc várakozás
    matrix0.clear();
    matrix0.writeDisplay();  // Kikapcsolás
    delay(500);

    // Több mátrix: Pl. szinkronizált rajz
    matrix1.drawPixel(0, 0, LED_ON);  // Másik mátrixon rajzolás
    matrix1.writeDisplay();
}
// Ez demonstrálja a loop használatát animációkhoz, ami a játékokban kulcsfontosságú.
```

## 6. Lépés: Teljes példa integráció
Próbáld ki egy egyszerű játékfragmentumot, ahol több elemet kombinálsz:
```cpp
// Példa: Egy egyszerű villogó minta több mátrixon
matrix0.begin(0x70);
matrix1.begin(0x71);
while(true) {
    matrix0.drawPixel(0, 0, LED_ON);
    matrix1.drawPixel(7, 7, LED_ON);
    matrix0.writeDisplay();
    matrix1.writeDisplay();
    delay(200);
    matrix0.clear();
    matrix1.clear();
    matrix0.writeDisplay();
    matrix1.writeDisplay();
    delay(200);
}
// Ez mutatja, hogyan kezelhetsz több eszközt egyszerre.
```

Végül, íme a teljes mintakód az OrderConfigurator.cpp fájlból, hogy lásd a kontextust és kipróbálhasd:
```cpp
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_LEDBackpack.h>

Adafruit_8x8matrix matrix0 = Adafruit_8x8matrix();
// ... (a teljes kód folytatása) ...
// [Teljes kód itt:]
static const uint8_t num0[] = {B00000000, B00110000, B01001000, B01001000, B01001000, B01001000, B00110000, B00000000};
// ... (további num tömbök) ...

void setup() {
    Serial.begin(9600);
    matrix0.begin(0x70);
    // ... (további inicializálások) ...
    clearScreen();
}

void loop() {
    clearScreen();
    szamKiir(matrix0, 0);
    delay(500);
    // ... (további loop tartalom) ...
}

void szamKiir(Adafruit_8x8matrix matrix, int num) {
    // ... (funkció teljes tartalma) ...
}

char reverseBits(char b) {
    // ... (funkció) ...
}

void clearScreen() {
    // ... (funkció) ...
}
// A teljes kód itt fejeződik be.
```

Ez a tutorial most már részletesebb, hogy középiskolásként mélyebben megérthesd a rendszert. Próbáld ki a példákat, és építsd be a saját projektedbe!

---

# 1. Feladat:


![1. Feladat](1.png)

---

# 2. Feladat:


![2. Feladat](2.png)

---

# 3. Feladat:


![3. Feladat](3.png)

---

# 4. Feladat:


![4. Feladat](4.png)

---

# Teljes rendszer
**A teljes esp vezérlése** 

🛠️ Eszközök:
- 🧠 2 db ESP32 mikrokontroller
- 🟦 8 db 8×8 LED mátrix ( MAX7219-es vagy sorba köthető típus )
- 🎮 2 db joystick modul
- 📡 ESP-NOW protokoll ( ESP32 közötti vezeték nélküli kommunikációhoz )
- 🎯 Kettős vezérlés, közös játéktér frissítéssel

### **🏆 Extra feladat:**  
**🛠️ Extra feladat:** Ha elkészült az alap projekt, és van kedved feltúrbózni, itt egy gondolkodós kihívás! 🤔


✅ Sok sikert! 😊
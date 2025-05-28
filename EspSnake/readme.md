# EspSnake vezérlése 🐍

**📘 Projektleírás:** Ebben a projektben két ESP32 mikrokontroller 🧠 működik együtt, hogy megvalósítsanak egy kétszemélyes Snake játékot 🐍👾. A játék egy nagy LED mátrix kijelzőn 🟩 jelenik meg, amelyen mindkét játékos irányíthatja saját kígyóját, és egymással versenyezhetnek!

**🧱 Hardverfelépítés**
- 📟 8 db 8x8-as LED mátrix, összesen 64x16 pixel felbontással
- Elrendezés: 2 sor, 4-4 mátrix = 128 oszlop LED
- 🕹️ Két külön joystick: egyik játékos az egyik ESP32-vel, másik a másikkal irányít
- 📡 ESP-NOW kommunikáció: gyors, Wi-Fi alapú, peer-to-peer adatküldés

**🕹️ Játékmechanika:**
- Mindkét ESP32 fogadja a saját joystick adatát
- Az egyik ESP32 (fő vezérlő) összegyűjti az irányítási adatokat
- Ez a vezérlő kirajzolja a játékot a LED mátrixra:

**🐍🐍Két kígyó**
- Ütközésérzékelés (játék vége, ha falnak vagy egymásnak mennek)
- Pontszerzés, hosszabbodás, gyümölcsök 🎯


**🛠️ Fontos:** 📝 mindent a rajz alapján csináljatok, mert így biztosított a tökéletes működés. A progranban az elnevezések relatívak, nem muszáj azt használni. Ha mást használtok, akkor figyeljetek arra, hogy könnyen lehessen azonosítani az egyes vátozó neveket. 🔍

🤓 Aki foglalkozott már hasonlóval és szertne egy kicsit bonyolultabb feladaton gondolkodni annak van egy **exta feladat** a füzet végén. 📖💡

🔗 Minden feladatrész ugyanahoz a feladathoz tartozik. A feladatok között nem kell semmit átállítani, vagy megváltoztani. Ha egy feladatban egy elemet nem használsz és be van kötve attól nem lesz rossz, nem kell kivenni az alapból. 🔄✅

---
**Tartalomjegyzék:**
-   [Eszközök](#️-eszközök-amikre-szükséged-lesz)
-   [0. Feladat](#0-feladat)
-   [1. Feladat](#1-lépés-inicializálás-ébreszd-fel-a-mátrixot)
-   [2. Feladat](#2-lépés-kijelző-törlése-clear-screen) 
-   [3. Feladat](#3-lépés-egyetlen-pixel-kirajzolása)
-   [4. Feladat](#4-lépés-alakzat-kirajzolása-pl-számok-vagy-formák)
-   [5. Feladat](#5-lépés-animáció-és-több-mátrix-kezelése)
-   [6. Feladat](#6-lépés-teljes-példa-integráció)
-   [Összefoglaló](#összefoglalva)
-   [Fontos változók, függvények](#szószedet--fontosabb-változók-és-függvények)
-   [Extra Feladat](#extra-ötletek-bővítési-lehetőségek)

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

Ez a tutorial segít megérteni a 8x8 LED mátrixok használatát egy gyakorlati projektben. Elmagyarázom a kulcskoncepciókat, mint az I2C címzés, pixelkezelés és animáció, lépésről lépésre, de már egy kicsit mélyebben, hogy lásd, hogyan épül fel egy ilyen rendszer. Használd ki a példákat kódoláshoz!

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

---

# ESP-NOW Kommunikáció: Bevezetés és Példák

## Bevezető az ESP-NOW-hoz
ESP-NOW egy hatékony, vezeték nélküli kommunikációs protokoll, amelyet az Espressif (az ESP32 gyártója) fejlesztett ki. Ez lehetővé teszi az adatok gyors és alacsony késleltetésű cseréjét ESP32 eszközök között anélkül, hogy teljes WiFi hálózatot vagy internetkapcsolatot kellene használnod. Lényegében egy "közvetlen üzenetküldő rendszer", ami ideális valós idejű alkalmazásokhoz, mint például játékok vagy érzékelőhálózatok. Működése során az eszközök közvetlenül kommunikálnak egymással, ami gyorsabbá teszi, mint a hagyományos WiFi vagy Bluetooth. A protokoll használatához inicializálni kell az ESP32-t, majd regisztrálni a peer eszközöket (a másik ESP32-t), és ezután küldhetsz vagy fogadhatsz adatokat.

## Hogyan működik az ESP-NOW? Részletes magyarázat
1. **Inicializálás**: Először engedélyezned kell az ESP-NOW-t az ESP32-n. Ezután regisztrálod a célkészüléket (peer), hogy tudjon kommunikálni vele. Ehhez MAC-címeket használsz, amelyek minden ESP32-nek egyedi azonosítói.
2. **Adatküldés**: A feladó eszköz (sender) csomagolja az adatokat (pl. joystick irányok) és elküldi őket a regisztrált peer-nek. Az ESP-NOW nem igényel kézfogást, így nagyon gyors.
3. **Adatfogadás**: A fogadó eszköz (receiver) figyel az üzenetekre, és amikor érkezik, feldolgozza őket. Ha több eszköz van, szűrheted az üzeneteket a feladó MAC-címe alapján.
4. **Előnyök és korlátok**: Gyorsaság mellett energiatakarékos, de a távolság korlátozott (tipikusan 10-100 méter), és nem titkosított, szóval érzékeny adatokhoz nem ajánlott.

## Példakódok
Íme egy egyszerű példa, ahol egy feladó elküld egy üzenetet (pl. egy számot), és a fogadó fogadja azt. Ezeket a kódokat külön ESP32 eszközökön futtathatod.

### Feladó (Sender) Példakód:
```cpp
#include <esp_now.h>
#include <WiFi.h>

uint8_t peerAddress[] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};  // Cseréld ki a fogadó ESP32 MAC-címére!

void setup() {
    Serial.begin(115200);
    WiFi.mode(WIFI_STA);  // Állítsd be STA módra
    if (esp_now_init() != ESP_OK) {
        Serial.println("Hiba: ESP-NOW inicializálása sikertelen!");
        return;
    }
    esp_now_register_send_cb(onDataSent);  // Regisztráld a küldés eseményt
    esp_now_peer_info_t peerInfo = {};
    memcpy(peerInfo.peer_addr, peerAddress, 6);
    peerInfo.channel = 0;  // Használd az alapértelmezett csatornát
    peerInfo.encrypt = false;  // Nincs titkosítás
    if (esp_now_add_peer(&peerInfo) != ESP_OK) {
        Serial.println("Hiba: Peer regisztrálása sikertelen!");
        return;
    }
}

void loop() {
    String message = "Hello, ESP-NOW!";  // Üzenet, amit küldünk
    esp_err_t result = esp_now_send(peerAddress, (uint8_t *) message.c_str(), message.length());
    if (result == ESP_OK) {
        Serial.println("Üzenet elküldve!");
    } else {
        Serial.println("Küldés sikertelen!");
    }
    delay(2000);  // Két másodpercenként küldj
}

void onDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
    Serial.print("Küldés státusz: ");
    Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Sikeres" : "Sikertelen");
}
```

### Fogadó (Receiver) Példakód:
```cpp
#include <esp_now.h>
#include <WiFi.h>

void setup() {
    Serial.begin(115200);
    WiFi.mode(WIFI_STA);
    if (esp_now_init() != ESP_OK) {
        Serial.println("Hiba: ESP-NOW inicializálása sikertelen!");
        return;
    }
    esp_now_register_recv_cb(onDataRecv);  // Regisztráld a fogadás eseményt
}

void loop() {
    // A loop-ban nem kell tenni, az eseménykezelő fogja kezelni
}

void onDataRecv(const uint8_t *mac, const uint8_t *incomingData, int len) {
    String message = String((char*)incomingData);
    Serial.print("Fogadott üzenet: ");
    Serial.println(message);
    // Itt feldolgozhatod az adatokat, pl. frissítheted a kijelzőt
}
```

Próbáld ki: Futtasd a feladó kódot az egyik ESP32-n, a fogadót a másikon. Ellenőrizd a soros monitoron az üzeneteket, és lásd, hogyan érkeznek az adatok valós időben!

---

# Snake Játék 8x8-as Kijelzőkön: PVP Módban Két Joystickkel

## Bevezető és Elvek
A Snake játékot 8 darab 8x8-as LED mátrixon megvalósítani egy klasszikus grid-alapú játékot jelent, ahol két játékos versenyez egymással (PVP). A játék lényege, hogy két kígyót irányítasz joystickokkal, és célod, hogy az ellenfelet blokkold anélkül, hogy te ütköznél falba vagy a saját testedbe. Mivel az ESP-NOW nem szükséges ezekben a feladatokban, a fókusz a helyi vezérlésre, a kijelzőkezelésre és a játéklogikára esik. Itt vannak a fő elvek:

1. **Grid-alapú Térkép**: A 8 mátrix összesen egy 32x16-os virtuális gridet képez (mivel 8 mátrix vízszintesen 32 oszlopot és 16 sort ad ki). Minden mátrix egy 8x8-as részt kezel, így a kígyók mozgása ezen a kombinált griden történik.
2. **Bemenetfeldolgozás**: Két joystick kezeli a két kígyó irányítását. A bemenetet (pl. fel, le, balra, jobbra) olvasod be, és frissíted a kígyók irányát, de megakadályozod a fordított mozgást (pl. ha jobbra mész, nem fordulhatsz azonnal balra).
3. **Kígyómozgás és Ütközés**: A kígyók ciklikusan mozognak a griden. Ellenőrzöd az ütközéseket: ha a kígyó a grid széléhez, a másik kígyóhoz vagy saját magához ér, a játék véget ér. A mozgás egy tömbben tárolt koordinátákkal valósul meg.
4. **Játékciklus (Game Loop)**: Folyamatos ciklusban olvasod a bemenetet, frissíted a játékállapotot (mozgás), és kirajzolod a kijelzőkre. Ez biztosítja a valós idejű frissítést.
5. **Kirajzolás**: A mátrixokat frissíted a játékállapot alapján, pl. bekapcsolod a LED-eket a kígyó pozícióinál.
6. **PVP Logika**: A két kígyó párhuzamosan mozog, és az első, aki hibázik, veszít. Döntetlen, ha egyszerre ütköznek.

Idézet a SnakeMain.cpp fájlból: A játékciklus (`loop()`), a kígyómozgás (`moveSnake()`) és a bemenetkezelés (`JoystickBemenet()` és `DetermineDirection()`) mutatja ezeket az elveket. Például:

```cpp
void loop() {
    JoystickBemenet();
    DetermineDirection();
    if (GameState == "game") {
        if (millis() - Ido >= 100) {
            moveSnake();
            updateScreen();
            Ido = millis();
        }
    }
    // ... (további logika)
}

void moveSnake() {
    for (int i = length - 1; i > 0; i--) {
        snakeX1[i] = snakeX1[i - 1];
        snakeY1[i] = snakeY1[i - 1];
        snakeX2[i] = snakeX2[i - 1];
        snakeY2[i] = snakeY2[i - 1];
    }
    if (dir1 == 0) snakeX1[0]++;  // Jobbra mozgás
    if (dir1 == 1) snakeY1[0]++;  // Lefelé
    if (dir1 == 2) snakeX1[0]--;  // Balra
    if (dir1 == 3) snakeY1[0]--;  // Fel
    // Hasonlóan a második kígyóhoz
    // Ütközésellenőrzés: Ha kimegy a gridről vagy összeütközik
    if (snakeX1[0] < 0 || snakeX1[0] > 31 || snakeY1[0] < 0 || snakeY1[0] > 15) {
        GameState = "p2_w";
        ResetGame();
        return;
    }
    // ...
}
```
Ez a rész mutatja a griden való mozgást és ütközést, ami a PVP alapja.

---

# Snake Játék További Részletei: PVP Implementáció

A 3. feladatban építünk a 2.-re, és részletezzük, hogyan valósul meg a teljes PVP játék. Az elvek hasonlóak, de most hangsúlyozzuk a játékállapot-kezelést és a kijelzőfrissítést:

1. **Két Játékos Bemenete**: Külön-külön joystickok kezelik a két kígyót, de a játék egyetlen griden fut. A bemenetet a `JoystickBemenet()` funkció olvassa, és a `DetermineDirection()` állítja be az irányt.
2. **Játékállapotok**: Állapotgépet használsz (pl. "standby", "game", "p1_w"), hogy kezelhesd a játék fázisait, pl. várakozás indulásra vagy győzelem.
3. **Frissítés és Kirajzolás**: A `updateScreen()` frissíti a mátrixokat a `playField` tömb alapján, ami a grid állapotát tárolja.
4. **Egyszerű Játéklogika**: Nincs pontszám vagy étel, csak ütközés-alapú végkifejlet, de bővíthető.

Idézet a SnakeMain.cpp-ből: A kijelzőfrissítés és játéklogika kulcsfontosságú:

```cpp
void updateScreen() {
    for (int i = 0; i < 32; i++) {
        for (int j = 0; j < 16; j++) {
            int matrixIndex = (int)(i / 8) + 4 * (int)(j / 8);
            matrix[matrixIndex].drawPixel(i % 8, j % 8, playField[i][j] ? LED_ON : LED_OFF);
        }
    }
    for (int i = 0; i < 8; i++) matrix[i].writeDisplay();
}
// És a bemenet: 
void JoystickBemenet() {
    x = analogRead(JOYSTICK_X) - (JOYSTICK_RANGE_MAX / 2);
    y = analogRead(JOYSTICK_Y) - (JOYSTICK_RANGE_MAX / 2);
    // ... (további feldolgozás)
}
```
Ez illusztrálja, hogyan frissül a grid és hogyan olvassák a joystickok.

---

# Vezeték Nélküli PVP Snake: A Teljes Rendszer Működése

A 4. feladatban a Snake játék végső, vezeték nélküli (wireless) PVP változatát valósítjuk meg két ESP32 mikrokontroller között. Itt már nem csak helyben, hanem két külön eszközön, vezeték nélkül játszhattok egymás ellen! Az előző feladatokban már megismerted a grid-kezelést, a két joystickos irányítást és a játéklogikát – most azt mutatjuk be, hogyan lesz ebből igazi multiplayer élmény.

## Újdonságok és Fő Elvek

1. **Két ESP32, egy közös játékmező**: Mindkét ESP32 saját joystickot és kijelzősort kezel, de a játékmező (a két kígyó mozgása) szinkronban van. Az egyik eszköz a "fő vezérlő" (host), a másik a "vendég" (client).
2. **Vezeték nélküli kommunikáció ESP-NOW-val**: Az ESP-NOW protokoll segítségével az eszközök gyorsan, WiFi-hálózat nélkül, közvetlenül küldenek egymásnak üzeneteket. Ez teszi lehetővé, hogy a másik játékos joystickjának mozgását is lásd a saját kijelződön.
3. **Irányítási adatok átvitele**: Amikor a vendég játékos mozgatja a joystickot, az eszköze elküldi az irányt (pl. "up", "down", "left", "right") a fő vezérlőnek. A fő vezérlő fogadja ezt, és a saját játéklogikájába beépíti, így mindkét kígyó mozgása szinkronban van.
4. **Játékállapot szinkronizáció**: A játék indítása, győzelem, döntetlen vagy újrakezdés is szinkronizált. Például, ha az egyik játékos lenyomja a gombot, az üzenetként átmegy a másik eszközre, és mindkét kijelzőn egyszerre indul a játék.
5. **Callback funkciók és peer regisztráció**: Az ESP-NOW kommunikációhoz callback függvényeket használsz, amelyek automatikusan lefutnak, ha üzenet érkezik. A peer regisztrációval mondod meg, melyik eszközzel akarsz kommunikálni (MAC-cím alapján).

## Kódrészletek a SnakeMain.cpp-ből

**Peer regisztráció és callback beállítás:**
```cpp
WiFi.mode(WIFI_STA);
if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
}
esp_now_register_recv_cb(OnDataRecv); // Fogadó callback regisztrálása
```

**Adat fogadása és irányítás szinkronizáció:**
```cpp
void OnDataRecv(const esp_now_recv_info_t *recv_info, const uint8_t *data, int len)
{
    memcpy(&myData, data, sizeof(myData));
    if (strcmp(myData.a, "up") == 0) {
        if (dir2 != 1) dir2 = 3; // Menjünk felfelé
    } else if (strcmp(myData.a, "down") == 0) {
        if (dir2 != 3) dir2 = 1; // Menjünk lefelé
    } // ...
    else if (strcmp(myData.a, "button") == 0) {
        if (GameState != "standby") return;
        tone(BUZZER, 1000, 300);
        IsP2Ready = !IsP2Ready;
    }
}
```

**Játékállapot szinkronizáció:**
- Ha mindkét játékos készen áll, a játék egyszerre indul:
```cpp
if (tempP1Ready && tempP2Ready)
{
    IsP1Ready = false;
    IsP2Ready = false;
    GameState = "game";
    dir1 = 0;
    dir2 = 2;
    delay(1500);
}
```

## Mit jelent ez a játékosoknak?
- Mindkét játékos a saját joystickjával irányítja a saját kígyóját, de a mozgás és a játékállapot mindig szinkronban van.
- A vezeték nélküli kapcsolat miatt akár két külön asztalnál is játszhattok, nincs szükség összekötött kábelekre.
- A játékélmény teljesen valós idejű, hiszen az ESP-NOW gyors és megbízható.

## Összefoglalva
A 4. feladatban a Snake játék igazi, vezeték nélküli PVP élménnyé válik. Az ESP-NOW kommunikációval a két ESP32 közös játékmezőt alkot, a joystickok mozgása és a játékállapotok szinkronban vannak, így egy izgalmas multiplayer játékot hozhattok létre saját hardveren!

---

# Hardveres összefoglaló és bekötési tippek

## Mátrixok I2C címei és bekötése
- 8 db 8x8 LED mátrix, mindegyiknek saját I2C címe van (pl. 0x70, 0x71, 0x72, 0x73, 0x74, 0x75, 0x76, 0x77).
- A címeket a kódban a `matrix.begin(0x70);` sorokkal állítod be.
- A mátrixok SDA és SCL lábait az ESP32 megfelelő lábaira kell kötni (pl. SDA: 21, SCL: 22, de ez boardtól függ!).
- Minden mátrix tápját (VCC, GND) is kösd be, és legyen közös GND minden eszköz között!

## Joystick és buzzer bekötése
- Joystick X: pl. GPIO 33
- Joystick Y: pl. GPIO 35
- Joystick gomb: pl. GPIO 32
- Buzzer: pl. GPIO 26
- Ezeket a pin-eket a kódban is átírhatod, ha máshova kötöd!

## Tápellátás
- Figyelj, hogy az összes mátrix és az ESP32 is stabil 5V/3.3V tápot kapjon.
- A GND legyen mindenhol közös!

---

# Szükséges könyvtárak és telepítés

A projekt futtatásához az alábbi könyvtárak szükségesek:
- Adafruit GFX Library
- Adafruit LED Backpack Library
- esp_now (ESP32-hez)
- WiFi (ESP32-hez)

**Telepítés Arduino IDE-ben:**
1. Nyisd meg a Library Manager-t (Eszközök > Könyvtárak kezelése)
2. Keresd meg és telepítsd: "Adafruit GFX", "Adafruit LED Backpack"
3. Az "esp_now" és "WiFi" az ESP32 board telepítésével automatikusan elérhető lesz.

**PlatformIO esetén:**
- A `platformio.ini`-be írd be:
```
librarys =
    adafruit/Adafruit GFX Library
    adafruit/Adafruit LED Backpack Library
```

---

# Fájlok és kódok szerepe

- **SnakeMain.cpp**: A teljes játéklogika, joystick kezelés, mátrixok vezérlése, ESP-NOW kommunikáció.
- **OrderConfigurator.cpp**: Mátrixok tesztelése, címek és orientációk beállítása, egyszerű kijelzőpróba.
- **readme.md**: Ez a leírás, minden fontos információval.

**Melyik kódot töltsd fel?**
- A végső játékhoz a `SnakeMain.cpp`-t töltsd fel mindkét ESP32-re (ha szükséges, a peer MAC-címeket módosítsd a saját eszközeidhez).
- Az `OrderConfigurator.cpp`-t csak a mátrixok teszteléséhez használd.

---

# Hibakeresési tippek és gyakori hibák

- **Nem világít a mátrix:**
  - Ellenőrizd az I2C címeket (helyes sorrend, ütközés nincs-e)
  - Ellenőrizd a tápot, GND-t, SDA/SCL bekötést
  - Próbáld ki az `OrderConfigurator.cpp`-t, hogy minden mátrix működik-e
- **ESP-NOW nem kommunikál:**
  - Ellenőrizd, hogy mindkét ESP32 WiFi STA módban van-e
  - MAC-címeket pontosan add meg (nagybetű/kisbetű, kettőspontok)
  - Túl messze vannak az eszközök? (10-20 méter a biztos)
- **Joystick nem működik:**
  - Ellenőrizd a pin bekötést, GND-t
  - Soros monitorral nézd meg az olvasott értékeket
- **A játék nem indul:**
  - Mindkét játékosnak készen kell állnia (gombnyomás)
  - Ellenőrizd a GameState változót a soros monitoron

**Soros monitor használata:**
- Állítsd 9600 vagy 115200 baudra, és nézd a hibákat, visszajelzéseket!

---

# Játék indításának menete

1. Kapcsold be mindkét ESP32-t, ellenőrizd, hogy minden mátrix világít-e.
2. Mindkét játékos nyomja meg a joystick gombját, hogy készen álljon.
3. Ha mindketten készen állnak, a játék automatikusan indul.
4. A joystickkal irányítsd a saját kígyódat (fel/le/balra/jobbra).
5. Ha valaki ütközik, a játék véget ér, és visszakerül standby állapotba.
6. Új játékhoz ismét gombnyomás mindkét oldalon.

---

# Szószedet – fontosabb változók és függvények

- **matrix[]**: A 8 db 8x8-as mátrixot tartalmazó tömb
- **playField[32][16]**: A teljes játékmező (32x16) állapotát tárolja (hol van kígyó, hol nincs)
- **snakeX1[], snakeY1[]**: Az első játékos kígyójának koordinátái
- **snakeX2[], snakeY2[]**: A második játékos kígyójának koordinátái
- **dir1, dir2**: A két kígyó aktuális iránya (0: jobbra, 1: le, 2: balra, 3: fel)
- **GameState**: A játék aktuális állapota ("standby", "game", "p1_w", "p2_w", "draw")
- **JoystickBemenet()**: Joystick olvasása
- **DetermineDirection()**: Irány meghatározása joystick alapján
- **moveSnake()**: Kígyók mozgatása
- **updateScreen()**: Kijelzők frissítése
- **OnDataRecv()**: ESP-NOW üzenet fogadása
- **ResetGame()**: Játék újraindítása

---

# Extra ötletek, bővítési lehetőségek

- **Pontszám hozzáadása**: Minden túlélésért vagy ütközésért pont járhat.
- **"Étel" a pályán**: Véletlenszerűen jelenjen meg, a kígyó nőhet, ha megeszi.
- **AI ellenfél**: Egyik kígyót a gép irányítja.
- **Több mátrix, nagyobb pálya**: Akár 16 vagy több mátrix is összeköthető.
- **Különböző pályák, akadályok**: A playField tömbben előre beállított akadályok.
- **Hangjelzések, fény effektek**: Buzzerrel vagy LED-ekkel visszajelzés.
- **Bluetooth vagy WiFi alapú multiplayer**: Más kommunikációs módok kipróbálása.

---

Ha elakadsz, nézd át ezt a leírást, vagy kérdezz bátran! Jó játékot és jó tanulást! :)

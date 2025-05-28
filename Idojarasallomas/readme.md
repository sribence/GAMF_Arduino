# Időjárásállomás 🌡️🌁

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
-   [Teljes rendszer](#teljes-rendszer)
-   [Extra Feladat](#-extra-feladat)

---

# 🛠️ Eszközök, amikre szükséged lesz:
- 📶 Arduino MKR WiFi
- ☀️ Napelem + feszültségosztó
- 🌗 Beépített fényérzékelő 
- 🎤 Beépített mikrofon 
- 🌡️ DHT11 vagy beépített szenzor – hőmérséklet & páratartalom
- ⚙️ Szervómotor 
- 📊 Webes adatmegjelenítés grafikonokkal WiFi-n keresztül

---

# 0. Feladat:
⚙️ Kapcsolási rajz: (Először ez alapján csináljátok meg a kezdő állapotot.) 
![kapcsolási rajz](bekotes.png)

---

# 1. Feladat:
Az első lépésben csak a hőmérséklet és páratartalom mérését valósítjuk meg a DHT11 szenzorral. A mért értékeket a soros porton jelenítjük meg.

```cpp
#include <DHT.h>

// PIN definíciók
const int DHT_SENSOR = 2;    // DHT11 szenzor PIN-je

// Globális változók
DHT dht(DHT_SENSOR, DHT11);  // DHT szenzor inicializálása
float homerseklet;           // Hőmérséklet érték tárolása
float paratartalom;          // Páratartalom érték tárolása
unsigned long idozito;       // Időzítő a mérésekhez

void setup() {
    Serial.begin(9600);      // Soros port inicializálása
    dht.begin();             // DHT szenzor inicializálása
    idozito = millis();      // Időzítő kezdőértéke
}

void loop() {
    // Minden 2 másodpercben mérünk (a szenzor lassú)
    if (millis() - idozito < 2000) return;
    
    // Értékek kiolvasása
    float h = dht.readHumidity();        // Páratartalom mérése
    float t = dht.readTemperature();     // Hőmérséklet mérése (°C)
    
    // Hibaellenőrzés
    if (isnan(h) || isnan(t)) {
        Serial.println("Hiba a DHT szenzor olvasásakor!");
        return;
    }
    
    // Értékek kiírása
    Serial.print("Hőmérséklet: ");
    Serial.print(t);
    Serial.print("°C, Páratartalom: ");
    Serial.print(h);
    Serial.println("%");
    
    idozito = millis();  // Időzítő újraindítása
}
```

> 💡 **Fontos:** A DHT11 szenzor nem túl pontos, de olcsó és könnyen használható. A mérések között 2 másodperc szünetet kell tartani, mert a szenzor lassan válaszol.

---

# 2. Feladat:
A második lépésben hozzáadjuk a fényérzékelőt és a napelem követő rendszert. A szervómotor a fény irányába forgatja a napelemet.

```cpp
#include <DHT.h>
#include <Servo.h>

// PIN definíciók
const int DHT_SENSOR = 2;        // DHT11 szenzor PIN-je
const int SZERVO_PIN = 5;        // Szervó motor PIN-je
const int FENY_SZENZOR1 = A2;    // Első fényérzékelő PIN-je
const int FENY_SZENZOR2 = A1;    // Második fényérzékelő PIN-je

// Globális változók
DHT dht(DHT_SENSOR, DHT11);
Servo szervo;                    // Szervó motor objektum
int szervoSzog = 90;            // Szervó aktuális szöge
unsigned long idozito;
unsigned long szervoIdozito;

// Szervó korlátok
const int MIN_SZOG = 30;         // Minimális szög
const int MAX_SZOG = 150;        // Maximális szög
const int TOLERANCIA = 100;      // Fényérzékelő tolerancia

void setup() {
    Serial.begin(9600);
    dht.begin();
    szervo.attach(SZERVO_PIN);   // Szervó inicializálása
    szervo.write(szervoSzog);    // Szervó kezdőpozíció
    
    idozito = millis();
    szervoIdozito = millis();
}

void loop() {
    // Hőmérséklet és páratartalom mérése
    if (millis() - idozito >= 2000) {
        float h = dht.readHumidity();
        float t = dht.readTemperature();
        
        if (!isnan(h) && !isnan(t)) {
            Serial.print("Hőmérséklet: ");
            Serial.print(t);
            Serial.print("°C, Páratartalom: ");
            Serial.print(h);
            Serial.println("%");
        }
        idozito = millis();
    }
    
    // Napelem követés
    if (millis() - szervoIdozito >= 150) {
        int feny1 = analogRead(FENY_SZENZOR1);
        int feny2 = analogRead(FENY_SZENZOR2);
        
        // Csak akkor mozgatjuk a szervót, ha jelentős a különbség
        if (abs(feny1 - feny2) > TOLERANCIA) {
            if (feny1 > feny2) {
                szervoSzog = max(szervoSzog - 5, MIN_SZOG);
            } else {
                szervoSzog = min(szervoSzog + 5, MAX_SZOG);
            }
            szervo.write(szervoSzog);
        }
        szervoIdozito = millis();
    }
}
```

> ⚠️ **Megjegyzés:** A szervó motor fokozatosan mozog, hogy elkerüljük a hirtelen mozdulatokat. A fényérzékelők különbségét csak akkor használjuk, ha az meghaladja a tolerancia értéket.

---

# 3. Feladat:
A harmadik lépésben hozzáadjuk a WiFi kapcsolatot és egy egyszerű webes felületet az adatok megjelenítéséhez.

```cpp
#include <DHT.h>
#include <Servo.h>
#include <WiFiNINA.h>

// PIN definíciók
const int DHT_SENSOR = 2;
const int SZERVO_PIN = 5;
const int FENY_SZENZOR1 = A2;
const int FENY_SZENZOR2 = A1;

// WiFi beállítások
const char SSID[] = "IdojarasAllomas";
const char JELSZO[] = "12345678";

// Globális változók
DHT dht(DHT_SENSOR, DHT11);
Servo szervo;
int szervoSzog = 90;
unsigned long idozito;
unsigned long szervoIdozito;
WiFiServer szerver(80);  // Web szerver a 80-as porton

// HTML sablon a weboldalhoz
const char HTML_FEJLEC[] = R"(
<!DOCTYPE html>
<html>
<head>
    <title>Időjárásállomás</title>
    <meta charset='UTF-8'>
    <meta http-equiv='refresh' content='5'>
    <style>
        body { font-family: Arial; margin: 20px; }
        .adat { margin: 10px; padding: 10px; border: 1px solid #ccc; }
    </style>
</head>
<body>
    <h1>Időjárásállomás adatok</h1>
)";

void setup() {
    Serial.begin(9600);
    dht.begin();
    szervo.attach(SZERVO_PIN);
    szervo.write(szervoSzog);
    
    // WiFi hozzáférési pont indítása
    Serial.println("WiFi hozzáférési pont indítása...");
    if (WiFi.beginAP(SSID, JELSZO) != WL_AP_LISTENING) {
        Serial.println("WiFi indítási hiba!");
        while (true);
    }
    
    szerver.begin();
    Serial.print("IP cím: ");
    Serial.println(WiFi.localIP());
    
    idozito = millis();
    szervoIdozito = millis();
}

void loop() {
    // Hőmérséklet és páratartalom mérése
    if (millis() - idozito >= 2000) {
        float h = dht.readHumidity();
        float t = dht.readTemperature();
        
        if (!isnan(h) && !isnan(t)) {
            Serial.print("Hőmérséklet: ");
            Serial.print(t);
            Serial.print("°C, Páratartalom: ");
            Serial.print(h);
            Serial.println("%");
        }
        idozito = millis();
    }
    
    // Napelem követés
    if (millis() - szervoIdozito >= 150) {
        int feny1 = analogRead(FENY_SZENZOR1);
        int feny2 = analogRead(FENY_SZENZOR2);
        
        if (abs(feny1 - feny2) > TOLERANCIA) {
            if (feny1 > feny2) {
                szervoSzog = max(szervoSzog - 5, MIN_SZOG);
            } else {
                szervoSzog = min(szervoSzog + 5, MAX_SZOG);
            }
            szervo.write(szervoSzog);
        }
        szervoIdozito = millis();
    }
    
    // Web kliens kezelése
    WiFiClient kliens = szerver.available();
    if (kliens) {
        Serial.println("Új kliens csatlakozott");
        
        // HTTP kérés feldolgozása
        while (kliens.connected()) {
            if (kliens.available()) {
                // HTML oldal küldése
                kliens.println("HTTP/1.1 200 OK");
                kliens.println("Content-type:text/html");
                kliens.println();
                
                kliens.println(HTML_FEJLEC);
                kliens.println("<div class='adat'>");
                kliens.print("Hőmérséklet: ");
                kliens.print(dht.readTemperature());
                kliens.println("°C</div>");
                
                kliens.println("<div class='adat'>");
                kliens.print("Páratartalom: ");
                kliens.print(dht.readHumidity());
                kliens.println("%</div>");
                
                kliens.println("</body></html>");
                break;
            }
        }
        kliens.stop();
        Serial.println("Kliens kapcsolat bontva");
    }
}
```

> 🔍 **Tipp:** A webes felület automatikusan frissül 5 másodpercenként. A WiFi hozzáférési pont neve és jelszava a kódban van beállítva, ezeket módosíthatod a saját igényeidnek megfelelően.

---

# Teljes rendszer
**A teljes 🌦️ Mini időjárásállomás vezérlése** 

**🧪 Feladatleírás:** Valósíts meg egy környezeti szenzorokon alapuló mini időjárásállomást az Arduino Nano 33 IoT (vagy Nano 33 Sense) segítségével. A rendszer képes a következő környezeti értékek mérésére és kijelzésére:

**🛠️ Eszközök:**
- 📶 Arduino MKR WiFi
- ☀️ Napelem + feszültségosztó ( 🔋 töltöttség méréshez )
- 🌗 Beépített fényérzékelő ( ALS )
- 🎤 Beépített mikrofon ( 📈 hangszint érzékeléshez )
- 🌡️ DHT11 vagy beépített szenzor – hőmérséklet & páratartalom
- ⚙️ Szervómotor ( 🌞 napkövető funkció – opcionális )
- 📊 Webes adatmegjelenítés grafikonokkal WiFi-n keresztül

**🌡️ Hőmérséklet:**
- 💧 Páratartalom
- ☀️ Napfény erőssége
- 🔊 Hangszennyezettség (pl. zajszint)
- 🔋 Napelem feszültségszintje

Az adatokat a Nano beépített Wi-Fi kapcsolatán keresztül elérhető weboldalon jelenítsd meg grafikonos formában, lehetőség szerint valós időben frissülő nézettel (akár JavaScriptes grafikon segítségével, pl. Chart.js).

**🌞 Napelemes tápellátás figyelése:** Mivel a rendszer napelemes táplálásra van tervezve, fontos a töltöttségi szint (azaz a napelem aktuális feszültségének) megjelenítése is, például:
- 🔋 Napelem feszültség: 3.7V
Ez segít nyomon követni, mikor van szükség energiatakarékos működésre.

**🛠️ Extra funkció (opcionális) – Napkövető szervómotor:** Ha szeretnéd, egy szervómotorral megvalósítható egy napkövető rendszer, amely a beépített fényérzékelő adatai alapján:
- 👉 a napfény irányába fordítja a napelemet
Ez növelheti a töltési hatékonyságot.
- 📈 Webes megjelenítés
A Nano 33 IoT egy beépített webszervert futtat, amely a szenzoradatokat egy weboldalon jeleníti meg:
- 🕸️ Helyi IP-címről elérhető
- 📊 Az adatok grafikonként is látszanak (használható: Chart.js, Google Charts, stb.)
- 🔁 Automatikus frissítés 2–5 másodpercenként

---

# 🏆 Extra feladat:
**🛠️ Extra feladat:** Ha elkészült az alap projekt, és van kedved feltúrbózni, itt egy gondolkodós kihívás! 🤔

**🔁 1. Vízgőz és hőmérséklet összefüggés (Steam alert logic)**

**Cél:** Ha a hőmérséklet 30°C felett van ÉS a steam szenzor is magas értéket mutat, akkor a rendszer „Magas páratartalom és hő!” figyelmeztetést írjon ki a soros monitorra.

**Kihívás:** Kombinált feltételek, több változó figyelése egyszerre.ű

**🔁 2. Napkövetés időkorlát (Solar tracking cooldown)**
**Cél:** Limitáljuk a szervó mozgását úgy, hogy csak óránként maximum 10-szer állítódhat át, függetlenül attól, hogy a fotocellák milyen értéket adnak.

**Kihívás:** Egy mozgásszámláló és idő alapú reset implementálása.

**🔁 3. Éjszakai mód aktiválása (Night mode)**
**Cél:** Ha a fényérzékelő értéke alacsonyabb egy adott küszöbnél (pl. 150), akkor a weboldalon jelenjen meg egy új adatkártya: „Night Mode: ON”.

**Kihívás:** Webes HTML tartalom feltételes bővítése, logikai vezérlés a kijelzésben.

✅ Sok sikert! 😊

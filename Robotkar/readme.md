# Robotkar 🤖💪

**🔧 Projektleírás:** 
Ebben a projektben egy több szervómotorral vezérelt, asztali méretű robotkart építünk meg Arduino segítségével. A cél, hogy a diákok játékosan, mégis mélyrehatóan ismerkedjenek meg az aktuátorvezérlés, a mozgásprogramozás, valamint az ismételhető műveletsorok megvalósításával.

**🕹️ Egyéni vezérlés potméterekkel:**
Először a robotkar minden egyes tengelyét külön vezérelheted potméterek segítségével. Ez lehetővé teszi, hogy megtanuld, hogyan mozog egy szervó, és hogyan kapcsolódnak egymáshoz a kar részei.

**🤲 Szinkronizált mozgás – több szervó egy időben:**
Miután az alapmozgások mennek, egyszerre fogod vezérelni az összes szervót. Ezáltal képes leszel komplex, természetes mozgásokat létrehozni (pl. „fogd meg – emeld fel – tedd le”).

**💾 Pozíciók mentése és visszajátszása:**
A program lehetőséget biztosít arra, hogy kulcspozíciókat elments, majd ezeket sorrendben visszajátszd. Így a robotkar képes lesz egy adott feladatot automatikusan elvégezni, például egy tárgy áthelyezését egyik helyről a másikra.

**🔁 Feladat automatizálása:**
A robotkarod már nem csak egy eszköz, hanem egy programozható gép, amely képes újra és újra elvégezni ugyanazt a feladatot – emberi beavatkozás nélkül!


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
-   [Extra Feladat](#extra-ötlet)

---

# 🛠️ Eszközök, amikre szükséged lesz:
- 🧠 Arduino Mega
- ⚙️ 6 db szervómotor
- 🧩 Servo Shield 
- 🎛️ 4 db potméter
- 🔋 5V/6V tápegység a szervómotorok tápellátásához

---

# 0. Feladat:
⚙️ Kapcsolási rajz: (Először ez alapján csináljátok meg a kezdő állapotot.) 
![kapcsolási rajz](bekotes.png)

### Az alábbi rajzon látható a robotkar és tengelyei. 

> important
> vigyázzatok!

![kapcsolási rajz](robotkar.png)

---

# 1. Feladat:

## Szervómotorok vezérlése potméterrel – Lépésről lépésre

Ebben a feladatban megtanulod, hogyan lehet egy szervómotort (vagy többet) vezérelni egy potméter segítségével. Ez a robotkar alapja, hiszen minden ízületet (tengelyt) egy szervómotor mozgat, a potméter pedig olyan, mint egy "kézi vezérlő".

### 1. Mi az a szervómotor?
A szervómotor egy olyan motor, amelyet pontosan be tudsz állítani egy adott szögbe. Ezért tökéletes robotkarokhoz, ahol minden tengelynek pontosan kell mozognia.

### 2. Mi az a potméter?
A potméter egy tekerhető ellenállás, amivel egy analóg jelet (0-1023) tudsz beállítani. Olyan, mint egy hangerőszabályzó, csak itt a szervó szögét állítod vele.

### 3. Hogyan működik együtt?
- A potmétert az Arduino analóg bemenetére kötöd (pl. A0).
- A szervót egy PWM (pl. D9) kimenetre kötöd.
- Az Arduino beolvassa a potméter értékét, és átszámolja egy szögre (pl. 70-140 fok).
- A szervó ezt a szöget beállítja.

### 4. Lépésről lépésre példa

**Bekötés:**
- Potméter középső lába: A0
- Potméter két szélső lába: 5V és GND
- Szervó narancs: D9, piros: 5V, barna: GND

**Kód részlet:**
```cpp
#include <Servo.h>
Servo szervo1;
void setup() {
  szervo1.attach(9); // Szervó a D9-re
}
void loop() {
  int pot = analogRead(A0); // Potméter olvasása
  int szog = map(pot, 0, 1023, 70, 140); // Átszámolás szögre
  szervo1.write(szog); // Szervó beállítása
  delay(15); // Stabil működés
}
```

### 5. Miért fontos ez?
A robotkar minden ízületét így tudod kézzel mozgatni, "tanítani". Ha ezt érted, már tudsz egy teljes kart is vezérelni több potméterrel és szervóval.

### 6. Extra ötletek, magyarázatok
- Próbáld ki, hogy több szervót és potmétert kötsz be! (pl. szervo2.attach(10), pot2 = analogRead(A1), stb.)
- Írd ki a soros monitorra a potméter és szervó értékeket, hogy lásd, mi történik!
- Gondold végig: ha minden szervó egy-egy ízület, hány szabadságfoka van a robotkarnak?

---

# 2. Feladat:

## Szervómotorok pontosabb vezérlése – PWM és finomhangolás

Most tovább lépünk: nem csak szöget állítunk, hanem közvetlenül a szervó vezérlőjelét (PWM – impulzusszélesség) szabályozzuk. Ez még pontosabb mozgást tesz lehetővé, és közelebb visz a profi robotikához!

### 1. Mi az a PWM?
A PWM (Pulse Width Modulation) egy olyan jel, amivel a szervó "megmondja", milyen szögbe álljon. A jel hossza (pl. 500-2500 mikrosec) határozza meg a szöget.

### 2. Miért jó közvetlenül PWM-et vezérelni?
- Finomabb, pontosabb mozgás
- Egyes szervók csak bizonyos PWM tartományban működnek jól
- Profi robotikában gyakran közvetlenül PWM-mel dolgozunk

### 3. Lépésről lépésre példa

**Bekötés:**
- Ugyanaz, mint az előző feladatban

**Kód részlet:**
```cpp
#include <Servo.h>
Servo szervo1;
const int MIN_PWM = 500;   // Minimum impulzus (0 fok)
const int MAX_PWM = 2500;  // Maximum impulzus (180 fok)
void setup() {
  szervo1.attach(9);
}
void loop() {
  int pot = analogRead(A0);
  int pwm = map(pot, 0, 1023, MIN_PWM, MAX_PWM);
  szervo1.writeMicroseconds(pwm); // Közvetlen PWM vezérlés
  delay(15);
}
```

### 4. Fokozatos mozgatás – miért jó?
Ha a szervót nem "ugrasztod" azonnal a célpozícióba, hanem kis lépésekben mozgatod, a mozgás simább, a robotkar nem rángatózik.

**Példa:**
```cpp
for (int szog = 70; szog <= 140; szog++) {
  szervo1.write(szog);
  delay(10);
}
```

### 5. Miért fontos ez?
A robotkar precíz, ismételhető mozgásához elengedhetetlen a pontos vezérlés. Ha később programból szeretnél mozdulatsorokat tanítani, a PWM-es vezérlés lesz az alap.

### 6. Extra ötletek, magyarázatok
- Próbáld ki, hogy a szervót lassan mozgatod egyik pozícióból a másikba!
- Mérd meg, hogy a különböző szervók milyen PWM tartományban működnek jól!
- Gondold végig: hogyan lehetne több szervót egyszerre, szinkronban mozgatni?

```cpp
#include <Servo.h>

// A szervó motorok (ábra szerint vannak betűvel ellátva)
const int ServoPinA = 4;
const int ServoPinB = 10;
const int ServoPinC = 9;
const int ServoPinD = 11;
const int ServoPinE = 5;
const int ServoPinF = 6;

Servo szervoA;
// Servo szervoB;
// Servo szervoC;
// Servo szervoD;

const int MIN_PWM = 500;   // Minimum impulzus (0 fok)
const int MAX_PWM = 2500;  // Maximum impulzus (180 fok)

void setup() {
  szervoA.attach(ServoPinA);        // Szervó 1 a D9-re
  // szervoB.attach(ServoPinB);    // Szervó 2 a D10-re
  // szervoC.attach(ServoPinC);    // Szervó 3 a D11-re
  // szervoD.attach(ServoPinD);     // Szervó 4 a D6-ra
}

void loop() 
{
  int pot1 = analogRead(A0); // Potméter 1
  int pwm1 = map(pot1, 0, 1023, MIN_PWM, MAX_PWM);
  szervoA.writeMicroseconds(pwm1); // Szervó A vezérlése

  // int pot2 = analogRead(A1); // Potméter 2
  // int pwm2 = map(pot2, 0, 1023, MIN_PWM, MAX_PWM);
  // szervoB.writeMicroseconds(pwm2); // Szervó B vezérlése

  // int pot3 = analogRead(A2); // Potméter 3
  // int pwm3 = map(pot3, 0, 1023, MIN_PWM, MAX_PWM);
  // szervoC.writeMicroseconds(pwm3); // Szervó C vezérlése

  // int pot4 = analogRead(A3); // Potméter 4
  // int pwm4 = map(pot4, 0, 1023, MIN_PWM, MAX_PWM);
  // szervoD.writeMicroseconds(pwm4); // Szervó D vezérlése

  delay(15); // Frissítési idő
}
```

---

# 3. Feladat:


## Szervómotorok kézi vezérlése – Élő szögkiolvasás soros porton


Ebben a feladatban három potméterrel vezérlünk három szervót, valós időben, és a szervók aktuális szögeit folyamatosan kiírjuk a soros monitorra. Így a diákok kézzel be tudják állítani a kívánt pozíciókat, majd a szögeket másolhatják a saját robotvezérlésükbe.

### 1. Mire jó ez?
Segít pozíciók kézi tanításában

Azonnali vizuális visszajelzést ad a potméter beállításairól

Egyszerű és hasznos alap robotkar programozásához

### 2. Mit ír ki a program?
A soros monitoron folyamatosan frissülő formában láthatjuk például:
`S1: 85 | S2: 102 | S3: 77`

```cpp
#include <Servo.h>

// A szervó motorok (ábra szerint vannak betűvel ellátva)
const int ServoPinA = 4;
const int ServoPinB = 10;
const int ServoPinC = 9;
const int ServoPinD = 11;
const int ServoPinE = 5;
const int ServoPinF = 6;

const int SZERVO_PIN[3] = {ServoPinD, ServoPinE, ServoPinF};
const int POT_PIN[3] = {A0, A1, A2};

Servo szervok[3];

void setup() {
  Serial.begin(9600);
  for (int i = 0; i < 3; i++) {
    szervok[i].attach(SZERVO_PIN[i]);
  }
  Serial.println("Szervó szögek (S1 | S2 | S3):");
}

void loop() {
  int szogek[3];

  for (int i = 0; i < 3; i++) {
    szogek[i] = map(analogRead(POT_PIN[i]), 0, 1023, 0, 100);
    szervok[i].write(szogek[i]);
  }

  // Soros kiírás
  Serial.print("S1: ");
  Serial.print(szogek[0]);
  Serial.print(" | S2: ");
  Serial.print(szogek[1]);
  Serial.print(" | S3: ");
  Serial.println(szogek[2]);

  delay(50); // 0.05 másodperc frissítés
}
```


## 🤖 Robotkar vezérlése – Soros porton beírt pózok alapján

Ebben a részben egy átfogó, lépésenkénti útmutatót adunk arról, hogyan valósul meg az összehangolt szervomotor mozgatás a robotkarban. Gondolj erre, mint egy tananyagra, ami segít megérteni a technológiát kezdőktől haladókig. Használjuk a coordinatedMove függvény logikáját, hogy mutassuk be, hogyan kerül sor kontrollált, szinkronizált mozgásra több szervónál egyszerre.

Ez a projekt lehetővé teszi, hogy egy Arduino-alapú 3 tengelyes robotkar **koordináltan bemozogjon** a soros porton keresztül beírt szervóállásokba. A mozgás **egyenletes és egyszerre történik**, így szép, folyamatos átmenetet kapunk.

---

### 🧠 Alapötlet

Ez három szervó szögét jelenti (fokban):  
- Szervó 1 → 90°  
- Szervó 2 → 45°  
- Szervó 3 → 120°

Az Arduino ezeket az értékeket beolvassa, és **lépésekben odamozgatja** a szervókat.

## 💻 Használat

1. Nyisd meg a **Serial Monitor**-t (9600 baud).
2. Írd be a kívánt szögeket vesszővel elválasztva, pl.:  `90,45,120`
3. A robotkar szépen **bemozog a megadott pózba**.
4. Adj meg új pózt, és ismét bemozog.

```cpp
#include <Servo.h>

const int SZERVO_DB = 3;// Szervók száma
const int SZERVO_LABAK[SZERVO_DB] = {9, 10, 11};// Szervók kimeneti lábai
Servo szervok[SZERVO_DB];// Szervó objektumok tömbje
float aktualis_szog[SZERVO_DB] = {90, 90, 90};// Aktuális szögértékek fokban
float cel_szog[SZERVO_DB] = {90, 90, 90};// Cél szögértékek fokban
String soros_puffer = "";// Beolvasott soros adatpuffer

void setup() {
  Serial.begin(9600);

  // Szervók inicializálása és kezdő pozíció beállítása
  for (int i = 0; i < SZERVO_DB; i++) {
    szervok[i].attach(SZERVO_LABAK[i]);             // Csatlakoztatjuk a szervót a megfelelő lábra
    szervok[i].write(aktualis_szog[i]);             // Elküldjük az alap szög értékét
  }

  Serial.println("Adj meg egy pózt így: 90,45,120");
}

void loop() {
  // Soros portról érkező karakterek beolvasása
  while (Serial.available()) {
    char beolvasott_karakter = Serial.read();

    if (beolvasott_karakter == '\n') {
      feldolgozBemenet(soros_puffer);  // Ha sortörés, feldolgozzuk a puffer tartalmát
      soros_puffer = "";               // Puffer kiürítése
    } else {
      soros_puffer += beolvasott_karakter; // Hozzáadjuk a karaktert a pufferhez
    }
  }
}

// A beolvasott bemenet feldolgozása: vesszővel tagolt számok → cél szögek
void feldolgozBemenet(String bemenet) {
  bemenet.trim();  // Szóközök eltávolítása

  if (bemenet.length() == 0) return;  // Üres bemenet esetén kilép

  // Bemenet darabolása és értékek mentése
  for (int i = 0; i < SZERVO_DB; i++) {
    int vesszo_poz = bemenet.indexOf(',');  // Megkeressük a következő vessző helyét
    String ertek;

    if (vesszo_poz != -1 && i < SZERVO_DB - 1) {
      ertek = bemenet.substring(0, vesszo_poz);  // Első érték
      bemenet = bemenet.substring(vesszo_poz + 1);  // A többit megtartjuk a következő körre
    } else {
      ertek = bemenet;  // Utolsó érték (vagy csak egy volt)
    }

    // Átalakítjuk float típusra, és korlátozzuk 0–180 fok közé
    cel_szog[i] = constrain(ertek.toFloat(), 0, 180);
  }

  mozgasKoordinaltan();  // Elindítjuk a mozgást a cél szögek felé
}

// Koordinált, lépésenkénti mozgás minden szervóval egyszerre
void mozgasKoordinaltan(int kesleltetes_ms = 15) {
  int lepesek_szama = 50;
  float szog_lepes[SZERVO_DB];

  // Minden szervóhoz kiszámítjuk, mennyit kell mozdulnia egy lépésben
  for (int i = 0; i < SZERVO_DB; i++) {
    szog_lepes[i] = (cel_szog[i] - aktualis_szog[i]) / lepesek_szama;
  }

  // Lépésről lépésre közelítjük meg a cél pozíciót
  for (int lepes = 0; lepes < lepesek_szama; lepes++) {
    for (int i = 0; i < SZERVO_DB; i++) {
      aktualis_szog[i] += szog_lepes[i];          // Következő szög kiszámítása
      szervok[i].write(aktualis_szog[i]);         // Szervó vezérlése az új szöggel
    }
    delay(kesleltetes_ms);                        // Várakozás két lépés között
  }

  // A végpozíció pontos beállítása (elkerülve az apró csúszásokat)
  for (int i = 0; i < SZERVO_DB; i++) {
    aktualis_szog[i] = cel_szog[i];
    szervok[i].write(aktualis_szog[i]);
  }

  // Visszajelzés a felhasználónak
  Serial.print("Elért szögek: ");
  for (int i = 0; i < SZERVO_DB; i++) {
    Serial.print(aktualis_szog[i]);
    if (i < SZERVO_DB - 1) Serial.print(", ");
  }
  Serial.println();
}
```

Ez a kód futtatható az Arduino-ban, és mutatja, hogyan mozognak a 3 szervó összehangoltan a megadott cél szögök felé. Teszteléskor állítsd be a tényleges pin-eket!

---

# 4. Feladat:

## Saját mozdulatsor programozása és visszajátszása

A robotkar képes több pozíciót is elmenteni, majd ezeket egymás után végrehajtani. Így például megtaníthatod a kart, hogy felemeljen egy tárgyat, áthelyezze, majd visszatérjen a kiinduló helyzetbe.

```cpp
#include <Servo.h>

const int SZERVO_PIN[4] = {3, 5, 6, 9};
const int POT_PIN[4] = {A0, A1, A2, A3};
const int MAX_POZICIOK = 10;

Servo szervok[4];
int pozicioTarolo[MAX_POZICIOK][4]; // Tárolja a szervópozíciókat
int pozicioSzamlalo = 0;            // Aktuális mentett pozíciók száma

String parancs = "";

void setup() {
  Serial.begin(9600);
  for (int i = 0; i < 4; i++) {
    szervok[i].attach(SZERVO_PIN[i]);
  }
  Serial.println("Parancsok: MOVE, SAVE, LOAD");
}

void loop() {
  // Soros parancs beolvasása
  if (Serial.available()) {
    parancs = Serial.readStringUntil('\n');
    parancs.trim(); // Térköz, újsor eltávolítása

    if (parancs == "MOVE") {
      movePotmeterAlapjan();
    }
    else if (parancs == "SAVE") {
      if (pozicioSzamlalo < MAX_POZICIOK) {
        for (int i = 0; i < 4; i++) {
          int szog = map(analogRead(POT_PIN[i]), 0, 1023, 70, 140);
          pozicioTarolo[pozicioSzamlalo][i] = szog;
        }
        pozicioSzamlalo++;
        Serial.println("Pozíció elmentve.");
      } else {
        Serial.println("Tár megtelt!");
      }
    }
    else if (parancs == "LOAD") {
      Serial.println("Pozíciók lejátszása:");
      for (int p = 0; p < pozicioSzamlalo; p++) {
        for (int i = 0; i < 4; i++) {
          szervok[i].write(pozicioTarolo[p][i]);
        }
        delay(1000); // 1 másodperc várakozás két pozíció között
      }
    }
    else {
      Serial.println("Ismeretlen parancs!");
    }
  }

  // Folyamatos MOVE támogatás, ha ez a legutóbbi parancs
  if (parancs == "MOVE") {
    movePotmeterAlapjan();
  }
}

void movePotmeterAlapjan() {
  for (int i = 0; i < 4; i++) {
    int szog = map(analogRead(POT_PIN[i]), 0, 1023, 70, 140);
    szervok[i].write(szog);
  }
  delay(15);
}
```
# 🎮 4 Szervós Robotkar vezérlés potméterrel és soros parancsokkal

Ez a projekt lehetővé teszi egy **4 tengelyes szervóvezérelt robotkar** vezérlését potméterekkel, valamint pozíciók elmentését és visszajátszását a **soros porton keresztül adott parancsokkal**.

## 🛠️ Hardverkövetelmények

- 1 db Arduino UNO / Nano / Mega
- 4 db szervómotor (pl. SG90 vagy MG90S)
- 4 db potméter (10k ideális)
- Breadboard, vezetékek
- USB kábel Arduino programozásához

### 🔌 Bekötés

| Szervó index | Szervó pin | Potméter pin |
|--------------|------------|--------------|
| 0            | D3         | A0           |
| 1            | D5         | A1           |
| 2            | D6         | A2           |
| 3            | D9         | A3           |

> Az egyes szervók és potméterek párban dolgoznak: a potméter határozza meg a szervó szögét.

---

## 📦 Funkciók

- **MOVE**: A potméterek aktuális állása alapján vezérli a szervókat
- **SAVE**: Elmenti az aktuális 4 szervó pozícióját egy tömbbe
- **LOAD**: Sorban visszajátssza az összes mentett pozíciót

---

## 🧪 Használat lépései

1. **Töltsd fel a kódot az Arduino-ra** az Arduino IDE segítségével.
2. **Nyisd meg a Soros monitort** (baud rate: `9600`).
3. Írd be a következő parancsokat:

### Parancsok listája

| Parancs | Leírás |
|--------|--------|
| `MOVE` | A potméterek élő vezérlést biztosítanak a szervóknak. |
| `SAVE` | Elmenti az aktuális pozíciót egy tömbbe (max. 10 pozíció). |
| `LOAD` | Lejátsza az összes elmentett pozíciót, kb. 1 mp szünettel. |


---


# 5. feladat

## Előre beprogramozott pozíciók között váltás "simítva"

Ebben a feladatban az a cél hogy előre megadott állásokba kell vezérelni a robotot de úgy, hogy mindegyik egy időpontban érkezzen a kívánt pozícióba.

Mindemellett még implementáljuk az alapértelmezett működést amivel össze tudjuk majd hasonlítani a mi megoldásunkat.

```cpp
#include <Servo.h>

// Mivel a kód kettő fajta mozgatást velósít meg 
// így ezzel a váltózóval eldöntheted melyiket használod majd
// true  -> simított mozgás
// false -> alap mozgás
const bool SimaMozgas = true;

// A szervó motorok (ábra szerint vannak betűvel ellátva)
const int ServoPinA = 4;
const int ServoPinB = 10;
const int ServoPinC = 9;
const int ServoPinD = 11;
const int ServoPinE = 5;
const int ServoPinF = 6;

// Az F motor limitje
const int LimitF = 110; 

// Potméterek
const int Poti1 = A0;
const int Poti2 = A1;
const int Poti3 = A2;
const int Poti4 = A3;

// Szervó példányok
Servo ServoA;
Servo ServoB;
Servo ServoC;
Servo ServoD;
Servo ServoE;
Servo ServoF;

// Mentett pozíciók
// Egy sor jelenti az adott pozíciót (több motor állása)
// és az oszlopokban pedig az adott szervók beállított szöge
// FONTOS: egy sorban csak 6 érték lehet (mert ennyi motor van)
//         de annyi sor amennyit szeretnénk (csak a memória szab határt)
const int Poziciok[][6] = {
    {10, 30, 20, 40, 50, 0},
    {15, 20, 60, 20, 70, 100},
    {30, 30, 70, 30, 20, 0},
    {60, 20, 60, 10, 30, 100}
};

// A pozcízókat tároló tömb hosszának eltárolása
int length = 0;

// Eltároljuk az alap állapotot is, amit kiindulásnak és végpontnak használunk
const int AlapPoziciok[6] = {100, 78, 63, 15, 110, 0};
int AktualisPoziciok[6] = {0};

void setup()
{
    // Soros port elindítása
    Serial.begin(9600);

    // A szervó példányok csatolása a csatlakozásokhoz
    ServoA.attach(ServoPinA);
    ServoB.attach(ServoPinB);
    ServoC.attach(ServoPinC);
    ServoD.attach(ServoPinD);
    ServoE.attach(ServoPinE);
    ServoF.attach(ServoPinF);

    // A pozíciókat tároló tömb hosszának kiszámítása dinamikusan
    length = sizeof(Poziciok) / (sizeof(int) * 6);

    // Beállás alap állapotba
    Mozgatas(AlapPoziciok);

    // Megvárjuk a mozgást
    delay(1000);
}

void loop()
{
    // Végigmegyünk az elmentett pozíciókon és kiírjuk a motorokra
    // valamint egy értesítő üzenetet is a soros portra
    for (int i = 0; i < length; i++)
    {
        Serial.println(String(i + 1) + ". allapotba mozgas . . .");

        if (SimaMozgas)
        {
            SimaMozgatas(Poziciok[i]);
        }
        else
        {
            Mozgatas(Poziciok[i]);
        }

        delay(500);
    }

    // Szeparáló üzenet
    Serial.println("--------------------------");

    // Beállás alap állapotba
    if (SimaMozgas)
    {
        SimaMozgatas(AlapPoziciok);
    }
    else
    {
        Mozgatas(AlapPoziciok);
    }

    // Megvárjuk, hogy a motorok befejezzék a mozgást mielött új parancsot adnánk
    delay(1000);
}

void Mozgatas(int poz[6])
{
    // Az F motor limitjének vizsgálata
    if (poz[5] > LimitF) poz[5] = LimitF;

    // Csak szimplán kiírjuk az adatokat a motorokra és azok
    // maguktól beállnak a helyükre
    ServoA.write(poz[0]);
    ServoB.write(poz[1]);
    ServoC.write(poz[2]);
    ServoD.write(poz[3]);
    ServoE.write(poz[4]);
    ServoF.write(poz[5]);

    // Eltároljuk az új pozíciót jelenlegiként
    for (int i = 0; i < 6; i++)
        AktualisPoziciok[i] = poz[i];

    // Megvárjuk, hogy a motorok befejezzék a mozgást mielött új parancsot adnánk
    delay(1000);
}

void SimaMozgatas(int poz[6])
{
    // Az F motor limitjének vizsgálata
    if (poz[5] > LimitF) poz[5] = LimitF;

    // Lokálisan eltároljuk az aktuális pozíciót, a globálisat a végén fissítjük
    // A lebegőpontos ábrázolás könnyíti majd a dolgunkat (float)
    float LocalisAktualisPoziciok[6] = {};
    for (int i = 0; i < 6; i++)
        LocalisAktualisPoziciok[i] = AktualisPoziciok[i];

    // Kiszámoljuk, hogy egy mozdulattal mennyit kell mozdulnia minden egyes motornak
    // mindezt a legnagyobb mozdulathoz viszonyítva (a legnagyobb esetben 1 mozdulat 1 fokot jelent [1:1])
    float MozdulatRata[6] = {};
    int MaxElmozdulas = abs(poz[MaxErtekIndex(poz)] - LocalisAktualisPoziciok[MaxErtekIndex(poz)]);
    for (int i = 0; i < 6; i++)
    {
        int Elmozdulas = abs(poz[i] - LocalisAktualisPoziciok[i]);
        MozdulatRata[i] = 1.0 * Elmozdulas / MaxElmozdulas;
    }

    // Elmozdulás sok apró lépésben
    for (int i = 0; i < MaxElmozdulas; i++)
    {
        // Hozzáadjuk az 1 lépés alatt megtett fokokat a pozícióhoz
        for (int j = 0; j < 6; j++)
        {
            int szorzo = 1;
            if (LocalisAktualisPoziciok[j] - poz[j] >= 0) szorzo  = -1; 
            LocalisAktualisPoziciok[j] += MozdulatRata[j] * szorzo;

        }

        // Kiírjuk a pozíciót a motorokra
        ServoA.write((int)LocalisAktualisPoziciok[0]);
        ServoB.write((int)LocalisAktualisPoziciok[1]);
        ServoC.write((int)LocalisAktualisPoziciok[2]);
        ServoD.write((int)LocalisAktualisPoziciok[3]);
        ServoE.write((int)LocalisAktualisPoziciok[4]);
        ServoF.write((int)LocalisAktualisPoziciok[5]);

        // Megvárjuk, hogy a motorok befejezzék a mozgást mielött új parancsot adnánk
        // sok kicsi mozgás -> kisebb várakozás idő mozgásonként
        delay(50);
    }

    // Eltároljuk az új pozíciót jelenlegiként
    for (int i = 0; i < 6; i++)
        AktualisPoziciok[i] = poz[i];
}

// Egyszerű maximum függvény (visszaadja a legnagyobb érték indexét)
int MaxErtekIndex(const int poz[6])
{
    int max = 0;

    for (int i = 0; i < sizeof(poz) / sizeof(int); i++)
        if (poz[max] < poz[i]) 
            max = i;

    return max;
}
```

---
# Összefoglalás

A valós robotkar.cpp kód sokkal többet tud, mint az alap potméteres vezérlés:
- 6 szervó, szinkronizált mozgás, pozíciók mentése, visszajátszása, LED visszajelzés, soros parancsvezérlés.
A 3. és 4. feladatban a diákok megtanulják a robotkar programozott vezérlését, a mozdulatsorok tanítását és visszajátszását, így valóban kipróbálhatják a robotot, és kreatívan használhatják a rendszert.

Ha elakadsz, nézd át ezt a leírást, vagy kérdezz bátran! Jó kísérletezést és jó tanulást! :)


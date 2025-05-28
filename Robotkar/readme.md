# Robotkar 🤖💪

A projekt egy több szervómotorral vezérelt, asztali méretű robotkar megépítését célozza. A diákok először külön-külön vezérlik a kar egyes tengelyeit potméterek segítségével, majd egyszerre történő mozgatással komplexebb mozdulatsorokat hajtanak végre. A felhasználó képes pozíciókat elmenteni, és később sorrendben visszajátszani a mozdulatokat, így a robotkar ismételhető, előre programozott feladatokat képes végrehajtani (pl. tárgy mozgatása egyik pontról a másikra). A projekt célja a szervóvezérlés, mozgás szinkronizálás és pozíció-mentés gyakorlása.

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
- 🧠 Arduino Mega
- ⚙️ 6 db szervómotor
- 🧩 Servo Shield 
- 🎛️ 4 db potméter
- 🔋 5V/6V tápegység a szervómotorok tápellátásához

---

# 0. Feladat:
⚙️ Kapcsolási rajz: (Először ez alapján csináljátok meg a kezdő állapotot.) 
![kapcsolási rajz](bekotes.png)

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

---

# 3. Feladat:

## Parancsvezérelt robotkar – pozíciók mentése, visszajátszása

A robotkar valós kódja nem csak egyszerű potméter-szervó vezérlés, hanem egy **parancsvezérelt rendszer**. Ez azt jelenti, hogy a robotkart a soros porton keresztül utasításokkal (parancsokkal) lehet irányítani, például:
- **Mozgás egy adott pozícióba**
- **Pozíciók elmentése**
- **Elmentett pozíciók visszatöltése és végrehajtása**
- **Információ lekérdezése a szervókról**

### Fő elvek:
- **Objektum-orientált szervókezelés:** Minden szervó egy MyServo objektum, amely tudja a saját határait, aktuális pozícióját, PWM értékét.
- **Szinkronizált mozgás:** A Servos osztály gondoskodik arról, hogy minden szervó egyszerre, fokozatosan érje el a kívánt pozíciót.
- **Pozíciók mentése/töltése:** Több pozíciót is elmenthetsz, majd ezeket visszajátszhatod, így a robotkar ismételhető mozdulatsorokat hajt végre.
- **LED visszajelzés:** Mozgás közben piros, végén sárga fény.

### Példák a parancsokra:

- **Mozgás egy adott pozícióba:**
  ```
  mov 0 45
  mov 1 -30
  mov 2 60
  mov 3 0
  mov 4 90
  mov 5 -45
  go
  ```
  Ez a sorozat beállítja a 6 szervó kívánt szögét, majd a `go` parancsra a kar egyszerre, szinkronizáltan elmozdul ezekbe a pozíciókba.

- **Pozíció mentése:**
  ```
  save_cur 0
  ```
  Elmenti a jelenlegi szervóállásokat a 0. pozícióba.

- **Pozíció betöltése és végrehajtása:**
  ```
  load 0
  go
  ```

- **Információ lekérdezése:**
  ```
  info
  ```
  Kiírja a szervók aktuális szögét, határait, lépésközét.

### Kódrészletek magyarázattal:

- **Szervók tömbje, paraméterezés:**
  ```cpp
  MyServo servo_array[] = {
      MyServo(11, 650, 1950, -90, 90, 1, 0.5),
      MyServo(10, 500, 1800, -90, 90, 1, 0.5),
      MyServo( 9, 750, 1750,   0, 90, 1, 0),
      MyServo( 6, 700, 1700,   0, 90, 1, 0),
      MyServo( 5, 500, 1700,   0, 90, 1, 1),
      MyServo( 4, 544, 2400, -90, 90, 1, 0.5),
  };
  ```
  Itt minden szervóhoz megadod: pin, min/max PWM, min/max szög, sebesség, kezdőpozíció.

- **Szervók szinkronizált mozgatása:**
  ```cpp
  void move(int del = 10) {
      strip.fill(red);
      strip.show();
      // ... minden szervó egyszerre, fokozatosan mozog a célpozícióba
      strip.fill(yellow);
      strip.show();
  }
  ```

- **Pozíciók mentése/töltése:**
  ```cpp
  void save(byte idx) { ... }
  void load(byte idx) { ... }
  ```

- **Soros parancsok feldolgozása:**
  ```cpp
  void process_command() {
      // pl. "mov 0 45", "go", "save_cur 0", "load 0", "info"
  }
  ```

---

# 4. Feladat:

## Saját mozdulatsor programozása és visszajátszása

A robotkar képes több pozíciót is elmenteni, majd ezeket egymás után végrehajtani. Így például megtaníthatod a kart, hogy felemeljen egy tárgyat, áthelyezze, majd visszatérjen a kiinduló helyzetbe.

### Lépések:

1. **Állítsd be a kart a kívánt pozícióba** (pl. potméterekkel vagy soros parancsokkal: `mov 0 0`, `mov 1 45`, stb.)
2. **Mentsd el a pozíciót:**
   ```
   save_cur 0
   ```
3. **Állítsd be a következő pozíciót** (pl. másik tárgy fölé, más szögekkel), majd mentsd el:
   ```
   save_cur 1
   ```
4. **Tetszőleges számú pozíciót elmenthetsz (pl. 0-9-ig).**
5. **A mozdulatsor visszajátszása:**
   ```
   load 0
   go
   load 1
   go
   load 0
   go
   ```
   Ezzel a kar végrehajtja a tanított mozdulatsort.

### Automatizált visszajátszás (bővítés):

Írhatsz egy egyszerű ciklust a soros monitoron keresztül, vagy akár a kódot is bővítheted, hogy egy gombnyomásra végigmenjen az összes elmentett pozíción:

```cpp
for (int i = 0; i < 3; ++i) {
    servos.load(i);
    servos.move();
}
```

### Tippek, magyarázatok:
- **A mozgás mindig szinkronizált, minden szervó egyszerre mozog.**
- **A LED szalag pirosan világít mozgás közben, sárgán, ha végzett.**
- **A pozíciók elmentése után a robotkar képes ismételni a tanult mozdulatsort, akárhányszor.**
- **A parancsokat a soros monitoron keresztül adhatod ki, így könnyen kísérletezhetsz.**

### Extra ötlet:
- **Írj egy "macro" parancsot, ami egy előre elmentett mozdulatsort automatikusan végigjátszik!**
- **Próbáld ki, hogy a robotkar egy tárgyat felemel, áthelyez, majd visszatesz!**

---

# Összefoglalás

A valós robotkar.cpp kód sokkal többet tud, mint az alap potméteres vezérlés:
- 6 szervó, szinkronizált mozgás, pozíciók mentése, visszajátszása, LED visszajelzés, soros parancsvezérlés.
A 3. és 4. feladatban a diákok megtanulják a robotkar programozott vezérlését, a mozdulatsorok tanítását és visszajátszását, így valóban kipróbálhatják a robotot, és kreatívan használhatják a rendszert.

Ha elakadsz, nézd át ezt a leírást, vagy kérdezz bátran! Jó kísérletezést és jó tanulást! :)

---

# Teljes rendszer
**A teljes robotkar vezérlése** 

🛠️ Eszközök:   
- 🧠 Arduino Mega
- ⚙️ 6 db szervómotor ( pl. SG90 vagy MG996R típusok kombinációja )
- 🧩 Servo Shield ( PWM vezérléshez )
- 🎛️ 4 db potméter ( manuális tengelyirányítás )
- 🔋 5V/6V tápegység a szervómotorok tápellátásához


### **🏆 Extra feladat:**  
**🛠️ Extra feladat:** Ha elkészült az alap projekt, és van kedved feltúrbózni, itt egy gondolkodós kihívás! 🤔


✅ Sok sikert! 😊

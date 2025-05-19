
# 🚦 LED-ek, Csipogó és RGB vezérlés – Arduino Projekt

Ez a projekt egy **közlekedési lámpa szimulációt** valósít meg, ahol a piros-sárga-zöld LED-ek váltogatása mellett **csipogó** és **RGB LED** is részt vesz a folyamatban. A végén 3 potméterrel keverhető RGB színt jelenítünk meg, és opcionálisan kombinálhatjuk a hanggal is – "hangos lámpa" mód.

---

## ✅ Tartalomjegyzék

- [Alkatrészek](#alkatrészek)
- [Kapcsolási rajz](#kapcsolási-rajz)
- [Lépések](#lépések)
- [Kód és magyarázat](#kód-és-magyarázat)
- [Képek](#képek)
- [Fejlesztési ötletek](#fejlesztési-ötletek)

---

## 🧰 Alkatrészek

| Eszköz            | Darabszám |
|-------------------|-----------|
| Piros LED         | 1         |
| Sárga LED         | 1         |
| Zöld LED          | 1         |
| RGB LED           | 1         |
| 220 Ohm ellenállás| 3–4       |
| Csipogó (Buzzer)  | 1         |
| Potméter          | 3         |
| Arduino UNO       | 1         |
| Breadboard + Jumperek | -     |

---

## 🧠 Kapcsolási rajz

📷 *(Első ábránk)*  
![Kezdeti bekötés](/1%20project/1-1.png)
> _Figure 1: Kezdeti bekötés

---

## 🔧 Lépések

1. **Alap közlekedési lámpa villogtatás** (piros–sárga–zöld)
2. **Csipogó integrálása** (időzítés, visszaszámlálás hangjelzéssel)
3. **RGB LED alapszínek villogtatása**
4. **RGB LED színkeverés potméterekkel**
5. *(Extra)* Hangos lámpa mód: RGB + buzzer

---

## 💻 Kód és magyarázat

### 1. Alap LED szimuláció – közlekedési lámpa
Három LED (piros, sárga, zöld) egymás után felvillan, pont úgy, mint az igazi lámpánál. Így látod, hogyan vezérelhetünk időzítve LED-eket.


```cpp
// LED lábak
int piros = 2;
int sarga = 3;
int zold  = 4;

void setup() {
  pinMode(piros, OUTPUT);
  pinMode(sarga, OUTPUT);
  pinMode(zold, OUTPUT);
}

void loop() {
  digitalWrite(piros, HIGH);
  delay(3000);                    // piros 3 másodperc
  digitalWrite(sarga, HIGH);
  delay(1000);                    // sárga + piros együtt 1 másodperc
  digitalWrite(piros, LOW);
  digitalWrite(sarga, LOW);
  digitalWrite(zold, HIGH);
  delay(3000);                    // zöld 3 másodperc
  digitalWrite(zold, LOW);
  digitalWrite(sarga, HIGH);
  delay(1000);                    // sárga 1 másodperc
  digitalWrite(sarga, LOW);
}
````
> [!NOTE]
> A `delay()` funkcióval időzíthetjük az egyes színek váltását. A sárga LED jelzi az átmenetet.

---

### 2. Csipogó hozzáadása (pl. vészjelzés)
A lámpa működését hanggal is kiegészítjük, például egy csipogás indulhat, amikor vált a lámpa. Ezzel azt tanuljuk meg, hogyan lehet egyszerre hangot és fényt is vezérelni.


📷 *(Csipogó hozzáadása)*  
![Második bekötés](/1%20project/1-2.png)
> _Figure 1: Csipogóval kiegészített áramökr

```cpp
int buzzer = 5;

void loop() {
  tone(buzzer, 1000);   // 1000 Hz hang
  delay(200);  
  noTone(buzzer);
  delay(200);
}
```
> [!IMPORTANT]
> A `tone()` függvény generál hangot. A `noTone()` leállítja. Próbálj ki különböző frekvenciákat és ütemeket!

---

### 3. RGB LED alapvezérlés (piros-zöld-kék egymás után)
Megnézzük, hogyan tudunk egyetlen LED-del többféle színt mutatni: piros, zöld és kék. Ez a LED három szín fényerejét keveri, mint egy színeslámpa.


📷 *(RGB ledünk bekötése)*  
![RGB led hozzáadása](/1%20project/1-3.png)
> _Figure 1: RGB ledet hozzáadtuk a bekötési rajzhoz
> 
```cpp
int red = 6;
int green = 9;
int blue = 10;

void setup() {
  pinMode(red, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(blue, OUTPUT);
}

void loop() {
  // Piros
  analogWrite(red, 255);
  analogWrite(green, 0);
  analogWrite(blue, 0);
  delay(1000);
  
  // Zöld
  analogWrite(red, 0);
  analogWrite(green, 255);
  analogWrite(blue, 0);
  delay(1000);

  // Kék
  analogWrite(red, 0);
  analogWrite(green, 0);
  analogWrite(blue, 255);
  delay(1000);
}
```
> [!IMPORTANT]
> Az `analogWrite()` segítségével PWM kimenettel állíthatjuk a fényerőt 0–255 között.

---

### 4. Potméteres színkeverés
Itt már te kevered ki a színt, három tekerőgombbal (potméterrel). Ezzel megtanulod, hogyan olvassunk analóg jeleket, és azt hogyan fordítsuk át színekre.



📷 *(Utolsó bekötés)*  
![Kezdeti bekötés](/1%20project/1-4.png)
> _Figure 1: Előzők plusz potméter 3szor is!
> 
```cpp
int potR = A0;
int potG = A1;
int potB = A2;

void loop() {
  int r = map(analogRead(potR), 0, 1023, 0, 255);
  int g = map(analogRead(potG), 0, 1023, 0, 255);
  int b = map(analogRead(potB), 0, 1023, 0, 255);

  analogWrite(red, r);
  analogWrite(green, g);
  analogWrite(blue, b);
  delay(10);
}
```
> [!IMPORTANT]
> A `map()` függvénnyel az analóg bemenetet (0–1023) konvertáljuk 0–255 tartományra az RGB LED-hez.

---

### 5. 🔊 Hangos lámpa mód
Végül a lámpa véletlenszerű színeket mutat, és minden színhez tartozik egy hang is. Olyan lesz, mintha egy bulis lámpa vagy jelzőberendezés lenne!


```cpp
void loop() {
  // RGB random szín + hang kombináció
  int r = random(255);
  int g = random(255);
  int b = random(255);

  analogWrite(red, r);
  analogWrite(green, g);
  analogWrite(blue, b);
  
  tone(buzzer, 500 + r); // a piros érték befolyásolja a hangot
  delay(500);
  noTone(buzzer);
}
```

---

## 🎓 Mit tanulunk ebből?
- Hogyan kell LED-et, RGB LED-et vezérelni.

- Hogyan működik egy csipogó (buzzer).

- Mit jelent a digitális és az analóg jel.

- Hogyan olvassunk be értékeket potméterrel.

- Hogyan keverjük a színeket és a hangokat programból.



---

## 📎 Fejlesztési ötletek

* [ ] OLED kijelző integrálása (pl. színértékek megjelenítése)
* [ ] Nyomógombos váltás "kézi vezérlés" móddal
* [ ] RGB LED villogtatás ritmus alapján
* [ ] Időalapú működés (millis() alapú, nem delay)

---





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

📷 *(Helyezd ide az ábrát)*  
```

images/traffic\_lamp\_wiring.png

````

> _Figure 1: A LED-ek, buzzer és RGB bekötése_

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

## 📷 Képek

Helyezd el a következő fájlokat a `images/` mappába:

* `traffic_lamp_wiring.png`
* `rgb_control_diagram.png`
* `full_project_build.jpg`

Markdownban így hivatkozol rá:

```markdown
![Kapcsolási rajz](images/traffic_lamp_wiring.png)
```

---

## 📌 Fejlesztési ötletek

* [ ] OLED kijelző integrálása (pl. színértékek megjelenítése)
* [ ] Nyomógombos váltás "kézi vezérlés" móddal
* [ ] RGB LED villogtatás ritmus alapján
* [ ] Időalapú működés (millis() alapú, nem delay)

---

## 📎 Licenc

MIT License

---

## 📩 Kapcsolat

Ha kérdésed van vagy hibát találsz, nyiss egy `Issue`-t vagy küldj `Pull Request`-et. 😊

```

---

Ez a `README.md` így nézne ki egy GitHub projektben, teljes mértékben nyomtatható és könnyen PDF-be exportálható.  
Ha szeretnéd, átkonvertálom neked `.pdf` vagy `.html` formátumba is – csak szólj!
```

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
A szervómotorok alapvető vezérlése potméterekkel. A potméterek értékeit beolvassuk az A0-A3 analóg bemenetekről, és ezek alapján vezéreljük a szervómotorokat. A szervók csak 70-140 fok között mozoghatnak a biztonságos működés érdekében.

```cpp
#include <Servo.h>

// Szervó motorok létrehozása
Servo szervo1;
Servo szervo2;
Servo szervo3;
Servo szervo4;

void setup() {
  // Szervók csatlakoztatása PWM lábakhoz
  szervo1.attach(9);  // D9 PWM láb
  szervo2.attach(10); // D10 PWM láb
  szervo3.attach(11); // D11 PWM láb
  szervo4.attach(12); // D12 PWM láb
  
  Serial.begin(9600);
}

void loop() {
  // Potméterek értékeinek beolvasása (0-1023)
  int pot1 = analogRead(A0);
  int pot2 = analogRead(A1);
  int pot3 = analogRead(A2);
  int pot4 = analogRead(A3);
  
  // Értékek átkonvertálása 70-140 fok közé
  int szog1 = map(pot1, 0, 1023, 70, 140);
  int szog2 = map(pot2, 0, 1023, 70, 140);
  int szog3 = map(pot3, 0, 1023, 70, 140);
  int szog4 = map(pot4, 0, 1023, 70, 140);
  
  // Szervók mozgatása
  szervo1.write(szog1);
  szervo2.write(szog2);
  szervo3.write(szog3);
  szervo4.write(szog4);
  
  // Értékek kiírása soros portra
  Serial.print("Potméter értékek: ");
  Serial.print(pot1); Serial.print(" ");
  Serial.print(pot2); Serial.print(" ");
  Serial.print(pot3); Serial.print(" ");
  Serial.println(pot4);
  
  delay(15); // Kis késleltetés a stabil működéshez
}

---

# 2. Feladat:
A szervómotorok pontosabb vezérlése PWM jelszinttel. A potméterek értékeit most már közvetlenül PWM impulzusszélességre konvertáljuk (500-2500 mikroszekundum), ami pontosabb vezérlést tesz lehetővé. A motorok mozgatása fokozatos, a for ciklusok segítségével.

```cpp
#include <Servo.h>

Servo szervo1;
Servo szervo2;
Servo szervo3;
Servo szervo4;

// PWM értékek tartománya (mikroszekundum)
const int MIN_PWM = 500;   // 0 fok
const int MAX_PWM = 2500;  // 180 fok

void setup() {
  szervo1.attach(9);
  szervo2.attach(10);
  szervo3.attach(11);
  szervo4.attach(12);
  
  Serial.begin(9600);
}

void loop() {
  // Potméterek beolvasása
  int pot1 = analogRead(A0);
  int pot2 = analogRead(A1);
  int pot3 = analogRead(A2);
  int pot4 = analogRead(A3);
  
  // Értékek konvertálása PWM tartományra
  int pwm1 = map(pot1, 0, 1023, MIN_PWM, MAX_PWM);
  int pwm2 = map(pot2, 0, 1023, MIN_PWM, MAX_PWM);
  int pwm3 = map(pot3, 0, 1023, MIN_PWM, MAX_PWM);
  int pwm4 = map(pot4, 0, 1023, MIN_PWM, MAX_PWM);
  
  // Fokozatos mozgatás for ciklusokkal
  for(int i = 0; i < 180; i++) {
    // PWM jelek generálása
    digitalWrite(9, HIGH);
    delayMicroseconds(pwm1);
    digitalWrite(9, LOW);
    
    digitalWrite(10, HIGH);
    delayMicroseconds(pwm2);
    digitalWrite(10, LOW);
    
    digitalWrite(11, HIGH);
    delayMicroseconds(pwm3);
    digitalWrite(11, LOW);
    
    digitalWrite(12, HIGH);
    delayMicroseconds(pwm4);
    digitalWrite(12, LOW);
    
    delay(20); // Teljes ciklus időtartama
  }
  
  // PWM értékek kiírása
  Serial.print("PWM értékek (μs): ");
  Serial.print(pwm1); Serial.print(" ");
  Serial.print(pwm2); Serial.print(" ");
  Serial.print(pwm3); Serial.print(" ");
  Serial.println(pwm4);
}

---

# 3. Feladat:


![3. Feladat](3.png)

---

# 4. Feladat:


![4. Feladat](4.png)

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

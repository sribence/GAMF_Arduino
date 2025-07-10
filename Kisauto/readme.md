# Önvezető - vonalkövető - kisautó 🚗

**🛠️ Feladat:** Ez a projekt egy vonalkövető kisautó építéséről szól, amely képes egy előre meghatározott fekete vonalat követni a földön. A cél egy egyszerű, de jól működő robot megépítése és programozása. 🤖
**🛠️ Fő funkciók:** 
- ⚙️ A szenzorok (pl. infravörös érzékelők) segítségével a vonal érzékelése
- 🔄 A motorok vezérlése a vonal követéséhez
- 🧠 Az irányító logika (pl. Arduino kód) megírása
- 🔋 Energiaellátás biztosítása
- 🧪 Tesztelés különböző pályákon

**🎯 Cél:**
- Megbízható, folyamatos vonalkövetés
- Gyors reagálás kanyarokra és elágazásokra
- Egyszerű, áttekinthető programkód

---
**Tartalomjegyzék:**
- [Alkatrészek](#-alkatrészek)
- [Teszt](#-teszt)
- [Ultrahangos érzékelő](#)
- [Osoyoo senzor](#)
- [Teljese kisautó](#)
- [Plusz feladat](#)

---
# 🔧 Alkatrészek:

- 🚗 Félig összerakott kisautó – a váz és néhány alkatrész már a helyén van
- 📡 Ultrahangos távolságérzékelő egy 🤖 szervómotorra rögzítve – akadályok észlelésére
- 🔍 Oyoso vonalkövető szenzor – már be van kötve az 🔌 Arduino vezérlőbe

---
# 🧪 Teszt:

**🔌Kapcsolási rajz:** 
![kapcsolási rajz](kapcsolas.png)

> ⚠️ Figyelem: A képen látható fekete OSOYOO panel csak szemléltetés. A valóságban nem ugyanaz van beépítve.
📍 Az ultrahangos érzékelő GND és VCC lábait kell megfelelően bekötni:
- GND ➜ fekete sáv
- VCC ➜ piros sáv

🧰 Tesztkód
Készítettünk egy tesztkódot, amivel a kisautó különböző kerekeinek működését lehet kipróbálni. 🛞⚙️
A fájlokat fent le tudjátok tölteni. 📁⬇️

> 📌 A három fájlnak egy mappában kell lennie, erre figyeljetek!
▶️ Ha a .ino fájlt elindítjátok, és minden megfelelően be van kötve:
- 🔋 Kapcsoljátok be az akkumulátort a kisautón
- 🔘 A bekapcsoló gomb azon az oldalon található, ahol két kábel kilóg

---
# Ultrahangos érzékelő működése:
Ebben a készletben egy Keyes HC-SR04 ultrahangos szenzor található 🔧📏, amely képes érzékelni az előtte lévő akadályokat 🚧, valamint megállapítani a szenzor és az akadály közötti pontos távolságot 📐. A működési elve hasonló a denevérek repüléséhez 🦇.

A szenzor ultrahangos jeleket bocsát ki 🔊, amelyeket az emberek nem hallanak 🙉. Amikor ezek a jelek egy akadályba ütköznek és visszaverődnek ↩️, a szenzor érzékeli őket. A jelek kibocsátása és visszaérkezése közötti időből ⏱️ kiszámítható a távolság a szenzor és az akadály között 📏.

🔬 A kísérletben a szenzort arra használjuk, hogy megmérjük az akadály és a szenzor közötti távolságot, és az eredményt ki is íratjuk 🖥️.

Az ultrahangos érzékelő modul 2 cm–450 cm közötti érintés nélküli mérési távolságot biztosít 📏➖📏, a mérési pontossága pedig akár 3 mm is lehet 🎯, ami kiválóan megfelel a hétköznapi igényeknek ✅. A modul tartalmaz egy ultrahangos adót és vevőt, valamint a hozzájuk tartozó vezérlőáramkört ⚙️🔌.

Példakód:

````cpp
//**********************************************************************************

const int TrigPin = 31; // Trig megadása, melyik lábra van kötve
const int EchoPin = 30; // Echo megadása, melyik lábra van kötve
int duration = 0; // Állítsd be a 'duration' (időtartam) kezdeti értékét 0-ra
int distance = 0;// Állítsd be a 'distance' (távolság) kezdeti értékét 0-ra

void setup() 
{
  pinMode(TrigPin , OUTPUT); // kimeneti módba áll a TrigPin
  pinMode(EchoPin , INPUT); // bemeneti módba áll az EchoPin
  Serial.begin(9600);  // A soros monitort 9600 baud sebessége, hogy lásd a pingelés eredményét
}
void loop()
{
 // Állítsd a trigPin-t magas szintre 10 mikrosecundum (10 μs) ideig, hogy aktiváld a HC-SR04 szenzort.
  digitalWrite(TrigPin , HIGH);
  delayMicroseconds(10);
  digitalWrite(TrigPin , LOW);

  // Várd meg, amíg a HC-SR04 visszatér magas szintre, és mérd meg ezt a várakozási időt.
  duration = pulseIn(EchoPin , HIGH);

  // Számítsd ki a távolságot az idő alapján
  distance = (duration/2) / 28.5 ;
  Serial.print("Distance: ");
  Serial.print(distance); // Írasd ki a távolság értékét a soros portra.
  Serial.println("cm");
  delay(300); // Várj 100ms két pingelés között (kb 20 pings/sec).
}
//**********************************************************************************
````

---
# Osoyoo senzor működése:

---




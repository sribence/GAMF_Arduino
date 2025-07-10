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
- [Ultrahangos érzékelő](#ultrahangos-érzékelő-működése)
- [Osoyoo sensor](#osoyoo-sensor-működése)
- [Teljese kisautó](#a-teljes-rendszer-egyben)
- [Plusz feladat](#-extra-feladat)

---
# 🔧 Alkatrészek:

- 🚗 Félig összerakott kisautó – a váz és néhány alkatrész már a helyén van
- 📡 Ultrahangos távolságérzékelő egy 🤖 szervómotorra rögzítve – akadályok észlelésére
- 🔍 Oyoso vonalkövető sensor – már be van kötve az 🔌 Arduino vezérlőbe

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
# Osoyoo sensor működése:

---
# A teljes rendszer egyben:

---
# 🏆 Extra feladat:
Ha elkészült az alap projekt, és van kedved feltúrbózni, itt egy gondolkodós kihívás! 🤔

Vonalkövető kisautó építése és programozása IR kommunikációval
**📌 Feladatleírás:** A projekt célja egy önállóan működő, vonalkövető kisautó megtervezése, megépítése és programozása, amely képes követni egy fekete színű vonalat a világos felületen, és kommunikálni más eszközökkel vagy autókkal infravörös (IR) jeleken keresztül.

**🎯 A projekt célja:** Egy egyszerű, de megbízható robotautó megépítése, amely követi a földre ragasztott fekete csíkot. 
Az autó képes legyen érzékelni a vonalat, fordulni, ha letér róla, és visszatalálni. Beépíteni egy IR adó-vevőt (transmitter & receiver), amelyen keresztül az autó adatot képes küldeni vagy fogadni – például akadály észlelése, másik robot jelenléte, vagy start/stop jelzések.

**💡 Funkciók és elvárások:**
🖤 Vonalkövetés:
- A robot folyamatosan kövesse a fekete csíkot.
- Ha a robot letér a vonalról, próbáljon visszatérni.
- Érzékelők: legalább 3 szenzoros vonalkövető modul (bal–közép–jobb).

📡 IR kommunikáció:
- A robot tudjon IR jelet küldeni más eszközöknek (pl. ha akadályt észlel).
- A robot tudjon IR jelet fogadni (pl. indulás vagy megállás parancs).
- Egyszerű üzenetek továbbítása, például: START, STOP, OBSTACLE.

🧠 Programozás:
- A vezérlés Arduino környezetben történjen (C++ alapú kód).
- A program dokumentált, áttekinthető legyen.
- A soros monitoron (Serial Monitor) jelenjen meg a távolság vagy vonalkövetési állapot.

**✅ Teljesítési feltételek:**
- A robot elindul és stabilan követi a vonalat.
- Megfelelően reagál, ha letér a vonalról (korrekció).
- Az IR adó-vevő használható legalább egy alap jel küldésére/fogadására.
- A forráskód működőképes és érthető.
- Legalább egy bemutató tesztkör sikeres lefuttatása.

> Ehhez már nem adunk példakódot. Az elkészült kódot kell kiegészíteni.
> Egy kis segítség hozzá: https://docs.keyestudio.com/projects/KS5005/en/latest/docs/Arduino/Arduino.html#projects

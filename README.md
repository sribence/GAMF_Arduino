# 🛠️ Arduino Projektek Gyűjteménye

Ez a repository különböző oktatási célú Arduino projekteket tartalmaz, melyek egyszerű szenzorokat és vezérlőeszközöket integrálnak. A projektek célja, hogy **gyakorlatorientált módon tanítsák meg a mikrokontrollerek és az elektronika alapjait**.

> 🎓 Ajánlott középiskolai vagy egyetemi bevezető kurzusokhoz, illetve hobbi fejlesztőknek is.

---

## 📂 Projektfeladatok

| #  | Cím | Leírás |
|----|-----|--------|
| 1. | [LED-ek, csipogó és RGB vezérlés](1%20project/1.%20projekt.md) | Közlekedési lámpa, RGB keverés potméterrel |
| 2. | [8x8 LED mátrix és Snake játék](2.%20feladat/2_feladat_leiras.md) | Mátrix kijelzés, karakterek, játék |
| 3. | [Rotary Encoder és LCD kijelző](3.%20feladat/3.%20feladat.md) | Menürendszer encoderrel, saját karakterek |
| 4. | [Távolságmérés – IR vs Ultrahang](4.%20feladat/4.%20feladat.md) | Szenzorok összehasonlítása, mérés LCD-n |
| 5. | [IR kommunikáció két Arduino között](5.%20feladat/5.%20feladat.md) | Távirányítós vezérlés, üzenetküldés IR-rel |
| 6. | [Szervómotorok és gyorsulásmérő](6.%20feladat/6.%20feladat.md) | Szervó-vezérlés, egyensúlykövetés, joystick |

---

## ⚙️ Használat

1. Töltsd le vagy klónozd a repót:
   ```bash
   git clone https://github.com/felhasznalo/arduino-projektek.git
   ```
2. Nyisd meg az Arduino IDE-t és válaszd ki a *.ino fájlokat.
3. Ellenőrizd a bekötést az adott feladat README.md fájlja szerint.
4. Töltsd fel a kódot a megfelelő Arduino eszközre.
---

## 📦 Szükséges könyvtárak
A projektektől függően szükséged lehet az alábbi könyvtárakra:
- IRremote
- Servo
- Wire, MPU6050 (gyorsulásmérőhöz)
- LiquidCrystal vagy LiquidCrystal_I2C
> Telepítés: Arduino IDE → Eszközök → Könyvtárkezelő
---

## 🧰 Hardverek
>  **Ez a projektgyűjtemény a [Keyestudio 48 in 1 Starter Kit for Arduino](https://docs.keyestudio.com/projects/KS0522/en/latest/KS0522.html) komponenseit használja.**

![image](https://github.com/user-attachments/assets/46330884-6949-4c06-9a9b-7c06beb39442)

Ez a készlet ideális választás azok számára, akik szeretnék elsajátítani az **Arduino programozás és szenzorhasználat alapjait**.  
Tartalmaz LED-eket, kijelzőket, szenzorokat, motorokat és egyéb hasznos modulokat, amelyek segítségével változatos oktatási feladatok valósíthatók meg.

> [!NOTE]  
> A példaprojektek többsége közvetlenül kapcsolódik a készletben található alkatrészekhez – az egyes feladatoknál jelezzük, hogy mely modulokra lesz szükség.

---
## 🖼️ Példaképek
> [!NOTE]
> További képek minden feladat saját mappájában találhatók.

# 👤 Szerző
- Sári Bence – sari.bence@neonpc.hu
- Halász Izabella Mária
- Fülöp Andor Zoltán 

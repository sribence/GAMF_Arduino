# 🛗 Lift működtetés 🚀
---
## BENCE ÁLTAL: 
A projekt célja egy háromszintes lift működésének modellezése egy léptetőmotorral hajtott kabin segítségével. A felhasználó három nyomógombbal választhatja ki a kívánt emeletet (földszint, 1. emelet, 2. emelet), amelyhez a rendszer pozíció-vezérléssel mozgatja a liftkocsit a lineáris sínen. Minden szint elérését fény- és hangjelzés kíséri, valamint egy 8x8 LED mátrixon az aktuális emeletszám és nyíl jelzi a mozgás irányát. A motorvezérlés finomításához opcionálisan gyorsítás/lassítás is beépíthető. A projekt során a diákok megismerkednek a léptetőmotor működésével, végálláskapcsolók használatával és az alap könyvtárak kezelésével.

- Arduino UNO
- Léptetőmotor (pl. NEMA 17)
- Motorvezérlő modul (pl. A4988 vagy ULN2003)
- Lineáris sín és kabinmodell
- 3 db nyomógomb (emeletválasztáshoz)
- 8x8 LED mátrix (emeletszám kijelzéshez)
- Végálláskapcsolók (referenciapont érzékeléshez)
- Buzzer és LED (jelzésekhez)

---

**🛗 Feladat:** Készíts egy liftmodellt, amely három emelet között mozgat egy kabint léptetőmotor segítségével. 🚀⚙️ Készíts egy vezérlőprogramot, amely kezeli a gombok jelzéseit, a motor működését és az emeletszám kijelzését. 💻🔢 Implementáld a pozícióvezérelt kabinmozgást a léptetőmotor és lineáris sín segítségével. 🚡📏 Biztosíts vizuális és hangjelzéseket minden emelet elérésekor. 🔊💡

**🛠️ Fontos:** 📝 mindent a rajz alapján csináljatok, mert így biztosított a tökéletes működés. A progranban az elnevezések relatívak, nem muszáj azt használni. Ha mást használtok, akkor figyeljetek arra, hogy könnyen lehessen azonosítani az egyes vátozó neveket. 🔍

🤓 Aki foglalkozott már hasonlóval és szertne egy kicsit bonyolultabb feladaton gondolkodni annak van egy **exta feladat** a füzet végén. 📖💡

🔗 Minden feladatrész ugyanahoz a feladathoz tartozik. A feladatok között nem kell semmit átállítani, vagy megváltoztani. Ha egy feladatban egy elemet nem használsz és be van kötve attól nem lesz rossz, nem kell kivenni az alapból. 🔄✅

---

**Tartalomjegyzék**
-   [Eszközök](#️-eszközök-amikre-szükséged-lesz)
-   [0. Feladat](#0-feladat)
-   [1. Feladat](#1-feladat)
-   [2. Feladat](#2-feladat) 
-   [3. Feladat](#3-feladat)
-   [4. Feladat](#4-feladat)
-   [Teljes rendszer](#a-teljes-rendszer-működtetése)
-   [Extra Feladat](#-extra-feladat)

---

# 🛠️ Eszközök, amikre szükséged lesz:
- Arduino UNO 🖥️⚡
- Léptetőmotor ⚙️🔄
- Motorvezérlő modul 🎛️🔌
- Lineáris sín és kabinmodell 🚠📏
- 3 db nyomógomb 🔘🔢
- 8x8 LED mátrix 🔲💡
- Végálláskapcsolók 🚫📍
- Buzzer és LED 🔊💡

---

# 0. Feladat:
⚙️ Kapcsolási rajz: (Először ez alapján csináljátok meg a kezdő állapotot.) 
![kapcsolási rajz](bekotes.png)

---

# 1. Feladat:


![1. Feladat](l-1.png)

---

# 2. Feladat:


![2. Feladat](l-2.png)

---

# 3. Feladat:


![3. Feladat](l-3.png)

---

# 4. Feladat:


![4. Feladat](l-4.png)

---

# Teljes rendszer
**A teljes liftvezérlő rendszer vezérlése**🚀

📌 Feladatleírás: A projekt célja egy liftmodell létrehozása, amely három emelet között mozgat egy kabint léptetőmotor segítségével. 🚀

🛗 Rendszer elemei:
- Léptetőmotor ( NEMA 17 ) ⚙️🔄
- Motorvezérlő modul ( A4988 vagy ULN2003 ) 🎛️🔌
- Lineáris sín és kabinmodell 🚠📏
- 3 db nyomógomb (  emeletválasztáshoz) 🔘🔢
- 8x8 LED mátrix ( emeletszám kijelzéshez ) 🔲💡
- Végálláskapcsolók ( referenciapont érzékeléshez ) 🚫📍
- Buzzer és LED ( jelzésekhez ) 🔊💡

🚀 Program működése:
- Emeletválasztás: A felhasználó három nyomógombbal választhatja ki a kívánt emeletet 🏠🔘🏠 
- Pozícióvezérlés: A rendszer léptetőmotor segítségével mozgatja a kabint a lineáris sínen ⚙️📏 
- LED Mátrix kijelzés: Az aktuális emeletszám és mozgásirány a 8x8 LED mátrixon jelenik meg 📟💡 
- Ajtó működése: A kabin ajtaja egy szervomotorral nyílik és záródik 🚪🔄 
- Hang- és fényjelzés: Minden emelet elérésekor buzzer és LED figyelmezteti a felhasználót 🔊✨ 
- Motorvezérlés finomhangolása: A gyorsítás/lassítás fokozatosan történik 🚀🐢

---

### **🏆 Extra feladat:**  
**🛠 Extra feladat:** Ha elkészült az alap projekt, és van kedved feltúrbózni, itt egy gondolkodós kihívás! 🤔

**📌 Időzített ajtónyitás és automatikus visszazárás:** A lift ajtaja ne csak manuálisan nyíljon és záródjon, hanem időzített módon működjön, és figyelje, hogy egy bizonyos idő elteltével automatikusan bezáródjon.

**🏆 Extra kihívás:** 👀 Jelenítsd meg a visszaszámlálást a LED kijelzőn – a hátralévő másodperceket mutassa! 

✅ Sok sikert! 😊


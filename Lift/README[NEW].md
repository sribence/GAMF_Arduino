# 🛗 Lift működtetés 🚀
---

**🛗 Feladat:** Építs egy háromszintes liftet, amely egy léptetőmotor segítségével mozgatja a kabint az emeletek között! 🏢🚡 A vezérlés három nyomógombbal történik, amelyekkel kiválasztható a cél-állomás. A kabin pontos mozgatását a pozíció alapján kell vezérelni – a rendszer lineáris sín mentén dolgozik. 🔁⚙️ Minden emelet elérésekor fény- és hangjelzést kell adnia, valamint a 8x8-as LED mátrixon jelenjen meg az aktuális emeletszám és a mozgás iránya is. 💡🔊 A motor működését finomítani is lehet – például gyorsítás/lassítás hozzáadásával, hogy még valósághűbb legyen. 🐢🚀

**🛠️ Fontos:** 🧭 Minden alkatrészt pontosan a kapcsolási rajz alapján köss be! Ha máshogy nevezel el egy változót, az rendben van, de figyelj arra, hogy átlátható és jól érthető legyen a kódod. 📋✅

📌 A teljes projekt több lépésből áll, de egyetlen rendszert építünk, nem kell semmit törölni vagy átállítani, ha új funkciót adsz hozzá. 🔗 Ha valamelyik modul még nincs használva, de már be van kötve, az nem gond – hagyd nyugodtan bent! 🧠

🤓 Ha gyorsan haladsz, és szeretnél továbbgondolni a feladatot, nézd meg az extra kihívást a végén – ajtóidőzítéssel és visszaszámlálásos kijelzéssel!

---

**Tartalomjegyzék**
-   [Eszközök](#️-eszközök-amikre-szükséged-lesz)
-   [1. Feladat](#1-feladat---a-lift-mozgatása-és-alap-vezérlése)
-   [2. Feladat](#2-feladat---egyéb-eszközök-csatlakozásának-tesztelése) 
-   [3. Feladat](#3-feladat---a-lift-irányítása-gombokkal-fel-le-álj)
-   [4. Feladat](#4-feladat---a-lift-funkcióinak-alapvető-megvalósítása)
-   [5. Feladat](#5-feladat---a-lift-végleleges-működése)
-   [Teljes rendszer](#teljes-rendszer)
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

# 1. feladat - A lift mozgatása és alap vezérlése

<img src="./ElevatorCode1.png" width="100%" />

---

# 2. feladat - Egyéb eszközök csatlakozásának tesztelése

<img src="./ElevatorCode2.png" width="100%" />

---

# 3. feladat - A lift irányítása gombokkal (fel, le, álj)

<img src="./ElevatorCode3.png" width="100%" />

---

# 4. feladat - A lift funkcióinak alapvető megvalósítása

<img src="./ElevatorCode4.png" width="100%" />

---

# 5. feladat - A lift végleleges működése

<img src="./ElevatorCode5.png" width="100%" />

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

# **🏆 Extra feladat:**  
**🛠️ Extra feladat:** Ha elkészült az alap projekt, és van kedved feltúrbózni, itt egy gondolkodós kihívás! 🤔

**📌 Időzített ajtónyitás és automatikus visszazárás:** A lift ajtaja ne csak manuálisan nyíljon és záródjon, hanem időzített módon működjön, és figyelje, hogy egy bizonyos idő elteltével automatikusan bezáródjon.

**🏆 Extra kihívás:** 👀 Jelenítsd meg a visszaszámlálást a LED kijelzőn – a hátralévő másodperceket mutassa! 

✅ Sok sikert! 😊

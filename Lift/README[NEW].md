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

Ebben a feladatban megismerkedünk a léptetőmotor működésével 🌀⚙️.
A léptetőmotorok vezérléséhez nagyon gyorsan kell váltogatni a jelet az egyik vezérlőlábon ⏱️🔁 – mindössze néhány mikroszekundumos eltéréssel kell fel- és lekapcsolni a jelet.

Egy ilyen fel-le váltás egy lépésnek számít 🚶‍♂️.

Az alábbi program 10 000 lépést tesz meg előre, majd 10 000 lépést visszafelé 🔁⬆️⬇️ – így kipróbálhatjuk, hogyan működik a motor mozgása a gyakorlatban! 🧪✅

<img src="./ElevatorCode1.png" width="100%" />

---

# 2. feladat - Egyéb eszközök csatlakozásának tesztelése

Mivel egy lift működéséhez nem csak egy motor szükséges 🛗⚙️, most a többi kapcsolódó eszközt is leteszteljük 🧪🔌.

A program a következőket kezeli:

- 🔘 3 nyomógomb
- 🛑 1 ütközésérzékelő
- 🔊 1 buzzer (hangjelző)
- 🔁 1 szervómotor
- 💡 1 darab 8×8-as LED mátrix

Ezek segítségével már egy valósághű lift szimulációt tudunk készíteni 🎯🔄.
Az alábbi kód vagy vezérli ezeket az eszközöket, vagy kiírja az állapotukat a soros portra 🖥️📟 – attól függően, hogy milyen típusúak.

<img src="./ElevatorCode2.png" width="100%" />

---

# 3. feladat - A lift irányítása gombokkal (fel, le, álj)

Most, hogy már minden csatlakoztatott eszközt leteszteltünk ✅🔌, végre elkezdhetjük létrehozni a valósághoz hű működést – egyelőre egy egyszerű példával 🛠️🚀.

🔘 1. gomb: ha megnyomjuk, a lift felfelé megy ⬆️
🔘 2. gomb: ha megnyomjuk, lefelé megy ⬇️
🔘 3. gomb: ha megnyomjuk, a lift megáll ⏸️

A kijelzőn 📺 is látható lesz, hogy éppen mi történik:
➡️ nyilakkal jelezzük a mozgás irányát,
➖ és egy vízszintes vonal jelenik meg, ha a lift nem mozog.

Ez még nem egy teljesen valós lift működése 🏗️, de már gombokkal irányítjuk a léptetőmotort, és szépen haladunk a cél felé! 🎯💡

<img src="./ElevatorCode3.png" width="100%" />

---

# 4. feladat - A lift funkcióinak alapvető megvalósítása

Az előző példát továbbfejlesztve most egy valósághű liftvezérlés megvalósításán dolgozunk 🏢⬆️⬇️.

🎯 A cél:
A gombok már nem csak mozgási irányt jelentenek, hanem valós emeleteket képviselnek, ahová a liftet hívhatjuk vagy küldhetjük. Ehhez pontosan kell ismernünk a lift pozícióját.

🏠 HOME pozíció meghatározás:
A lift induláskor egy ütközésérzékelő segítségével meghatározza a kiinduló helyzetét, amit földszintnek (G) tekintünk. Ez a "nulladik" pont, innen számítjuk a további mozgásokat.

📐 Mivel léptetőmotorral dolgozunk, pontosan tudjuk, hogy egy-egy lépéssel mennyit mozdul a lift – így bármikor kiszámíthatjuk, hogy épp melyik emeleten vagyunk.

📺 Kijelzőn megjelenik:

- 🔼🔽 mozgás iránya (nyilakkal)
- 🅶 / 1️⃣ / 2️⃣ az aktuális emelet
- 🔊 Buzzer is jelez, amikor szintet váltunk vagy célhoz érünk

Ez már sokkal közelebb áll egy valódi lift működéséhez – pontos vezérlés, állapotkijelzés, hívógomb funkciók és hangjelzések. 🎉

<img src="./ElevatorCode4.png" width="100%" />

---

# 5. feladat - A lift végleleges működése

Az előző feladatban már szinte egy teljes értékű liftvezérlő rendszert hoztunk létre 🚀🏢, de most még tovább finomítjuk a működést, hogy még realisztikusabb és professzionálisabb legyen.

🎛️ Fejlesztések, amiket bevezetünk:

- 🚪 Ajtónyitás/zárás mozgás előtt és után
- ⚡ Gyorsulás és lassulás: a mozgás nem indul és áll meg azonnal, hanem fokozatosan gyorsítunk/lassítunk a valósághű élményért
- 🔄 Állapotgép (state machine) használata: minden működési szakasz (várakozás, indulás, mozgás, lassítás, ajtónyitás stb.) egy-egy külön állapotként van kezelve, így az egész működés átláthatóbb és bővíthetőbb lesz

⚙️ Az állapotgép lehetővé teszi, hogy:

- Egyszerűen kezeljük az eseményeket és átmeneteket
- Stabil, előre kiszámítható működést kapjunk
- Később könnyedén hozzáadhassunk új funkciókat (pl. időzítők, szenzorhibák kezelése, LCD kijelző)

Ez a megközelítés már tényleg ipari szintű vezérlések alapját képezi – nem csak oktatási célra hasznos, hanem valós projekteknél is alkalmazható.

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

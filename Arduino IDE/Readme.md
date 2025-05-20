# Getting Started with Arduino IDE 2

Az Arduino IDE 2 bevezető útmutatója.

A klasszikus Arduino IDE-t a kezdettől fogva használják hobbi készítők, diákok és szakemberek egyaránt. Az Arduino IDE 2 ennek továbbfejlesztett változata, jobb teljesítménnyel, modernizált felhasználói felülettel és sok új funkcióval, mint például:

- [Automatikus kódkiegészítés](https://docs.arduino.cc/software/ide-v2/tutorials/ide-v2-autocomplete-feature)
- [Beépített hibakereső](https://docs.arduino.cc/software/ide-v2/tutorials/ide-v2-debugger)
- [Sketch-ek szinkronizálása az Arduino Cloud-dal](https://docs.arduino.cc/software/ide-v2/tutorials/ide-v2-cloud-sketch-sync)

Ebben az útmutatóban az IDE 2 alapjait mutatjuk be, és további részletes forrásokat ajánlunk az egyes funkciók használatához.

**👉 Az IDE 2 letölthető az [Arduino Software oldalról](https://www.arduino.cc/en/software).**

**📘 A részletes telepítési útmutató pedig itt érhető el: [IDE 2 letöltése és telepítése](https://docs.arduino.cc/software/ide-v2/tutorials/getting-started/ide-v2-downloading-and-installing)**

## Követelmények

- Telepített [Arduino IDE 2](https://www.arduino.cc/en/software)

## Áttekintés

Az IDE 2 új oldalsávot tartalmaz, ahol a leggyakrabban használt eszközök gyorsan elérhetők.

![Arduino IDE 2](https://docs.arduino.cc/static/e534053def4bc0eb97a3b6ba9cf31853/a6d36/ide-2-overview.png)

- **Fordítás / Feltöltés** – A kód lefordítása és feltöltése az Arduino lapra.
- **Board & Port kiválasztása** – Automatikusan felismeri az Arduino lapokat és portokat.
- **Sketchbook** – Helyileg tárolt sketch-ek. Felhővel is szinkronizálható.
- **Boards Manager** – Lapokhoz szükséges csomagok letöltése (pl. Arduino SAMD).
- **Library Manager** – Több ezer közösségi és hivatalos könyvtár böngészése.
- **Debugger** – Valósidejű hibakeresés.
- **Keresés** – Kulcsszavak keresése a kódban.
- **Soros Monitor megnyitása** – A konzolban új fülön jelenik meg.

## Funkciók

Az Arduino IDE 2 egy sokoldalú szerkesztő, amely rengeteg beépített funkcióval rendelkezik. Telepíthetünk könyvtárakat, szinkronizálhatjuk a sketch-eket, hibakeresést végezhetünk, és még sok más is elérhető. Ebben a részben a legfontosabb funkciókat tekintjük át.

### Sketchbook

![Arduino Sketchbook](https://docs.arduino.cc/static/36ffc036e2c2e9fcdec541c603989a81/a6d36/local-sketchbook.png)

A Sketchbook az a hely, ahol a saját kódjainkat (sketch-eket) tároljuk. Az Arduino sketch-ek `.ino` kiterjesztésű fájlok, és nevüknek megfelelő nevű mappában kell lenniük.

Például a `my_sketch.ino` nevű sketch a `my_sketch` nevű mappában kell hogy legyen.

Alapértelmezetten a sketch-ek a `Documents/Arduino` mappában találhatók. A Sketchbook megnyitásához kattints a bal oldali oldalsávban a mappa ikonra.

### Boards Manager

![Boards Manager](https://docs.arduino.cc/static/3826a19d73de5886f0415e287f385de9/a6d36/board-manager.png)

A Boards Manager lehetővé teszi, hogy új lapcsomagokat töltsünk le. Egy lapcsomag tartalmazza az adott Arduino típushoz szükséges fordítási "utasításokat".

Többféle hivatalos Arduino lapcsomag is elérhető, például `avr`, `samd`, `megaavr`.

👉 [Új lapok telepítéséhez olvasd el a Boards Manager útmutatót](https://docs.arduino.cc/software/ide-v2/tutorials/ide-v2-board-manager)

### Library Manager

![Library Manager](https://docs.arduino.cc/static/6ba5c25722a5a434d64c19dc3855e164/a6d36/library-manager.png)

A Library Manager segítségével több ezer könyvtár között böngészhetsz és telepítheted is őket. A könyvtárak kiterjesztik az Arduino API-t, és lehetővé teszik például szervómotorok vezérlését, szenzorok olvasását vagy Wi-Fi modulok használatát.

👉 [Könyvtárak telepítése – részletes útmutató](https://docs.arduino.cc/software/ide-v2/tutorials/ide-v2-installing-a-library)

### Serial Monitor

![Serial Monitor](https://docs.arduino.cc/static/e787bbea82bbd7f55b1c41d1a4f1f323/a6d36/serial-monitor.png)

A Serial Monitor lehetővé teszi, hogy valós időben lássuk, milyen adatokat küld az Arduino lap, például a `Serial.print()` parancs segítségével.

Régen külön ablakban jelent meg, most viszont beépült az IDE felületébe, így akár több példány is futhat egyszerre.

👉 [Serial Monitor használata – útmutató](https://docs.arduino.cc/software/ide-v2/tutorials/ide-v2-serial-monitor)

### Serial Plotter

![Serial Plotter](https://docs.arduino.cc/f155cf7066d171d7b88b80f3c921e7b1/potentiometer-plotter.gif)

A Serial Plotter segítségével grafikonon jeleníthetők meg az értékek, például feszültségcsúcsok vizualizálása.

Több változó is figyelhető egyszerre, akár külön szűrési lehetőségekkel.

👉 [Serial Plotter – részletes útmutató](https://docs.arduino.cc/software/ide-v2/tutorials/ide-v2-serial-plotter)

### Példa Sketch-ek

![Example Sketches](https://docs.arduino.cc/static/b5e4710d2f4c9c76ebd6b649dcd13331/a6d36/examplesketches.png)

A dokumentáció fontos részei a könyvtárakkal együtt érkező példa sketch-ek. Ezek megmutatják, hogyan kell egy adott funkciót vagy eszközt helyesen használni.

Ezeket a `File > Examples` menüpontban találjuk meg, a megfelelő könyvtár alatt.

Például, ha UNO R4 WiFi lap van csatlakoztatva, akkor elérhető a `LED_Matrix > MatrixIntro` sketch is, ami a dobozból kivéve is megtalálható volt a lapon.


### Hibakeresés (Debugging)

![Debugger](https://docs.arduino.cc/3fb57be2d7a0519e5e06856322874177/playpause.gif)

A debugger eszköz segítségével lépésenként futtathatjuk a programot, és hibákat kereshetünk. Lehetővé teszi a kód végrehajtásának kontrollált elemzését.

👉 [Hibakeresés részletesen – útmutató](https://docs.arduino.cc/software/ide-v2/tutorials/ide-v2-debugger)

### Automatikus kódkiegészítés (Autocompletion)

![Autocompletion](https://docs.arduino.cc/static/2d60917d221bc34a369dbb79e18f4f69/a6d36/autocomplete.png)

Az automatikus kódkiegészítés megkönnyíti a kódírást, és segít az Arduino API jobb megértésében. 

> Fontos: a funkció csak akkor működik, ha előtte kiválasztottad az Arduino lapodat!

👉 [Automatikus kódkiegészítés használata – útmutató](https://docs.arduino.cc/software/ide-v2/tutorials/ide-v2-autocomplete-feature)

### Távoli Sketchbook (Remote Sketchbook)

![Remote Sketchbook](https://docs.arduino.cc/2fb698acbbf780714a05e443011617ff/remote-sketchbook.gif)

A Remote Sketchbook lehetővé teszi, hogy az Arduino Cloud-on tárolt sketch-eidet szinkronizáld a helyi számítógépedre. Ehhez be kell jelentkezned a Cloud fiókodba.

![Új Cloud sketch létrehozása](https://docs.arduino.cc/static/7a70268c1893041f869d280ae22f5da2/a6d36/new-cloud.png)

👉 [Sketch-ek szinkronizálása – útmutató](https://docs.arduino.cc/software/ide-v2/tutorials/ide-v2-cloud-sketch-sync)

### Firmware és Tanúsítvány Feltöltő (Firmware & Certificate Uploader)

![Firmware & Certificate Uploader](https://docs.arduino.cc/static/cb423d13d402efdffbe6dbf8bb4fcf75/a6d36/fw-cert-upload.png)

Ez az eszköz lehetővé teszi a Wi-Fi modulokat tartalmazó lapok firmware-ének frissítését vagy visszaállítását, valamint SSL tanúsítványok feltöltését közvetlenül az IDE-ben.

👉 [Firmware feltöltő – részletes útmutató](https://docs.arduino.cc/software/ide-v2/tutorials/ide-v2-fw-cert-uploader)

## Közreműködés (Contribute)

Az Arduino IDE 2 egy nyílt forráskódú projekt, amelyet bárki szabadon letölthet. Közreműködhetsz:

- [Adományozással](https://www.arduino.cc/en/donate/)
- [Hibajegyek beküldésével GitHub-on](https://github.com/arduino/arduino-ide)

## Összegzés

Ebben az útmutatóban bemutattuk az Arduino IDE 2 legfontosabb funkcióit és a hozzájuk tartozó részletes útmutatókat. Az IDE 2 új lehetőségeket nyit meg a fejlesztésben, és a dokumentáció segít, hogy minden funkcióból a legtöbbet hozhasd ki.

---

📝 **Forrás**: [docs.arduino.cc - Getting Started with Arduino IDE 2](https://docs.arduino.cc/software/ide-v2/tutorials/getting-started-ide-v2)  
📄 **Licenc**: Creative Commons Attribution-Share Alike 4.0  


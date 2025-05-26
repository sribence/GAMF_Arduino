Ebben a projektben két ESP32 mikrokontroller együttműködésével valósul meg egy kétszemélyes Snake játék. A kijelzőfelületet 8 db 8x8 LED mátrix alkotja, amelyek 2 sorba, 4-4-es elrendezésben vannak sorba kötve. Az egyik ESP32 fogadja a saját játékos joystick bemenetét, míg a másik ESP32-től ESP-NOW protokollon keresztül megkapja a másik játékos irányítását. A két irányítási adatot összevetve egyetlen játékképernyőt rajzol ki a mátrixokra, így lehetővé válik a Snake PvP üzemmód. A projekt során a résztvevők megismerik az ESP-NOW kommunikáció alapjait, mátrixkezelést, játékszabály-implementációt, és többkijelzős grafikus megjelenítést.

- 2 db ESP32 mikrokontroller
- 8 db 8x8 LED mátrix (MAX7219-es vagy hasonló, sorba köthető)
- 2 db joystick modul
- ESP-NOW protokoll (ESP32 közötti kommunikációhoz)
- Kettős vezérlés, közös játéktér frissítéssel


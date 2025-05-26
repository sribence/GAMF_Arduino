# Okosóra feladatleírása

A projekt célja egy olyan hordozható egészségügyi monitor megvalósítása, amely képes az emberi pulzusszám, testhőmérséklet és alkoholszint mérésére. Az értékek egy 240x240 pixel felbontású, kör alakú SPI kijelzőn jelennek meg, letisztult felületen. A felhasználó egy rotary encoder segítségével tud navigálni a menüpontok között, így egyszerre csak egy mérés (pulzus, hőmérséklet vagy alkoholszint) eredménye jelenik meg a kijelzőn. A rendszer célja az adatok könnyen értelmezhető, kényelmes megjelenítése, és a szenzorhasználat gyakorlása valós alkalmazásban.

- Arduino Mega
- MAX30100 vagy hasonló pulzusmérő szenzor
- Hőmérséklet-érzékelő (pl. DS18B20 vagy LM35)
- MQ-3 alkoholérzékelő
- 240x240 pixel kör alakú SPI TFT kijelző
- Rotary Encoder (menünavigációhoz)


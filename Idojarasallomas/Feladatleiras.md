# Időjárásállomás feladatleírása

Mini időjárásállomás 
Valósíts meg egy környezeti szenzorokon alapuló időjárásállomást Arduino Nano 33 Sense segítségével, amely hőmérsékletet, páratartalmat, napfényerősséget és hangszennyezettséget mér. Az adatok grafikonos formában jelennek meg egy weboldalon, amelyet a Nano beépített WiFi kapcsolattal szolgál ki. A rendszer napelemes táplálásra van tervezve, és a napelem aktuális feszültségszintjét is megjeleníti, hogy követhető legyen a töltés. Opcionálisan egy szervómotor a fény irányába fordítja a napelemet, a beépített fényérzékelő adatainak felhasználásával.

- Arduino MKR WIFI
- Napelem + feszültségosztó (töltöttség méréshez)
- Beépített: fényérzékelő (ALS), mikrofon (hangszint)
- DHT11 vagy beépített szenzor: hőmérséklet, páratartalom
- Szervómotor (napkövető funkció, opcionális)
- Webes adatmegjelenítés grafikonokkal WiFi-n keresztül

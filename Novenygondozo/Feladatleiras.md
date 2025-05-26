# Növénygondozó feladatleírása

Készíts egy automatikusan öntöző és fénykiegészítő rendszert, amely a növény környezeti állapotát (fény, talajnedvesség, eső) figyeli, és az adatokat WiFi-n keresztül továbbítja egy weboldalra. Az Arduino MKR1000 eszközön keresztül a felhasználó mobiltelefonról WiFi-n is vezérelheti a szivattyút és a világítást (be/ki kapcsolás). Az öntözést egy relén keresztül vezérelt szivattyú, a világítást egy nagy fényerejű power LED biztosítja. Az eszköz opcionálisan gyorsulásérzékelővel figyelheti a mozgatást, például lopási kísérlet esetén. Napelemről akkumulátor töltést végez az eszköz, mely napelem mozgatását szervómotorral lehet megoldani a napsugarak felé. Ehhez két photoresistor értékéből kell kiszámolni a motor állását. 

- Arduino MKR1000
- Soil Humidity Sensor
- Water sensor (esőérzékelő)
- TEMT6000 Light Sensor
- Power LED
- Szivattyú + 12V relay
- MMA8452Q gyorsulásérzékelő (opcionális)
- WiFi webes vezérlés – ki/bekapcsoló gombok a világításhoz és szivattyúhoz
- Photoresistor + napelem
 

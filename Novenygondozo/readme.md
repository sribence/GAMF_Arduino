# Növénygondozó 🌱🧑‍🌾

Készíts egy automatikusan öntöző és fénykiegészítő rendszert, amely a növény környezeti állapotát (fény, talajnedvesség, eső) figyeli, és az adatokat WiFi-n keresztül továbbítja egy weboldalra. Az Arduino MKR1000 eszközön keresztül a felhasználó mobiltelefonról WiFi-n is vezérelheti a szivattyút és a világítást (be/ki kapcsolás). Az öntözést egy relén keresztül vezérelt szivattyú, a világítást egy nagy fényerejű power LED biztosítja. Az eszköz opcionálisan gyorsulásérzékelővel figyelheti a mozgatást, például lopási kísérlet esetén. 
 
**🛠️ Fontos:** 📝 mindent a rajz alapján csináljatok, mert így biztosított a tökéletes működés. A progranban az elnevezések relatívak, nem muszáj azt használni. Ha mást használtok, akkor figyeljetek arra, hogy könnyen lehessen azonosítani az egyes vátozó neveket. 🔍

🤓 Aki foglalkozott már hasonlóval és szertne egy kicsit bonyolultabb feladaton gondolkodni annak van egy **exta feladat** a füzet végén. 📖💡

🔗 Minden feladatrész ugyanahoz a feladathoz tartozik. A feladatok között nem kell semmit átállítani, vagy megváltoztani. Ha egy feladatban egy elemet nem használsz és be van kötve attól nem lesz rossz, nem kell kivenni az alapból. 🔄✅

---
**Tartalomjegyzék:**
-   [Eszközök](#️-eszközök-amikre-szükséged-lesz)
-   [0. Feladat](#0-feladat)
-   [1. Feladat](#1-feladat)
-   [2. Feladat](#2-feladat) 
-   [3. Feladat](#3-feladat)
-   [4. Feladat](#4-feladat)
-   [Teljes rendszer](#a-teljes-rendszer-működtetése)
-   [Extra Feladat](#extra-feladat)

---

# 🛠️ Eszközök, amikre szükséged lesz:
- 📡 Arduino MKR1000
- 🌱 Soil Humidity Sensor 
- 💧 Water Sensor 
- 💡 TEMT6000 Light Sensor 
- 🔦 Power LED
- 🚰 Szivattyú + 12V relay
- 🌀 MMA8452Q gyorsulásérzékelő
- 🌐 WiFi webes vezérlés – 🔘 ki/bekapcsoló gombok a világításhoz és szivattyúhoz

---

# 0. Feladat:
⚙️ Kapcsolási rajz: (Először ez alapján csináljátok meg a kezdő állapotot.) 
![kapcsolási rajz](bekotes.png)

---

# 1. Feladat:


![1. Feladat](1.png)

---

# 2. Feladat:


![2. Feladat](2.png)

---

# 3. Feladat:


![3. Feladat](3.png)

---

# 4. Feladat:


![4. Feladat](4.png)

---

# Teljes rendszer
**A teljes növénygondozó vezérlése** 

🛠️ Eszközök: 
- 📡 Arduino MKR1000
- 🌱 Soil Humidity Sensor ( talajnedvesség-érzékelő )
- 💧 Water Sensor ( esőérzékelő )
- 💡 TEMT6000 Light Sensor ( fényérzékelő )
- 🔦 Power LED
- 🚰 Szivattyú + 12V relay
- 🌀 MMA8452Q gyorsulásérzékelő ( opcionális )
- 🌐 WiFi webes vezérlés – 🔘 ki/bekapcsoló gombok a világításhoz és szivattyúhoz


### **🏆 Extra feladat:**  
**🛠️ Extra feladat:** Ha elkészült az alap projekt, és van kedved feltúrbózni, itt egy gondolkodós kihívás! 🤔


✅ Sok sikert! 😊

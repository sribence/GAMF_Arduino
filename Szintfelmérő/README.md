# Szintfelmérő

🔍 Ez a feladat arra szolgál, hogy felmérjük, milyen szinten álltok jelenleg – így a későbbi feladatokat a ti tudásotokhoz tudjuk igazítani.

📚 A következő részben különböző nehézségű feladatokat kaptok, lesz köztük könnyebb és nehezebb is. Segítséget nem adunk hozzá direktben, viszont használhatjátok az internetet, dokumentációkat, korábbi jegyzeteket – ahogy a való életben is tennétek.

🎯 A cél: próbáljátok megoldani az összes feladatot! Nem gond, ha nem sikerül minden – éppen ez fog segíteni nekünk abban, hogy lássuk, mit érdemes majd jobban átnézni, vagy hol lehet még fejlődni.

📈 A feladatok lépésről lépésre egyre összetettebbek lesznek, az alapoktól indulunk, majd szépen haladunk a bonyolultabb, összetettebb megoldások felé.

💪 Ne stresszeljetek rajta – ez nem vizsga, hanem egy gyakorlati felmérés, aminek az a célja, hogy minél hasznosabb tanulási élményt kapjatok a továbbiakban!

## Eszközök

Minden csapat kap:

- 1 db Arduino UNO
- 1 db LED
- 2 db nyomógomb
- 1 db szervómotor

🔧 A következő feladatokat ezeknek az eszközöknek a felhasználásával fogjátok megoldani. Fontos, hogy minden részfeladat ezek köré épül majd, így érdemes alaposan megismerni őket.

💡 Ha még nem használtátok valamelyik alkatrészt, az sem gond – a feladatok során egyre jobban meg fogjátok érteni a működésüket.

## 📄 Segédanyag a munkához

Az alábbi linken találjátok az eszközökhöz tartozó dokumentációt. Ebben:

- részletes bekötési útmutatót,
- és példakódokat is találtok.

[Dokumentáció (keyestudio 48 in 1 kit)](https://docs.keyestudio.com/projects/KS0522/en/latest/KS0522.html)

💡 Fontos viszont, hogy a feladatok nem pontosan ezeket a példákat kérik majd, így ezt a dokumentációt inkább kiindulási pontként használjátok – nem ez lesz a végső megoldás. Használjátok bátran, de gondolkodjatok tovább is a példákon túl! 🚀

## 1. feladat - egyszerű LED vezérlése

Ebben a feladatban kösd be a LED-et, majd írj olyan programot, ami a következő mintát hajtja végre:

1. A LED gyorsan kétszer felvillan – vagyis:

      - Kapcsold fel a LED-et,
      - rövid idő múlva kapcsold le,
      - kis szünet,
      - ismét kapcsold fel és le gyorsan.
      
2. Ezután várj egy hosszabb szünetet.
3. Ez a mintázat ismétlődjön folyamatosan.

A cél tehát: gyors villogás → szünet → gyors villogás → szünet... és így tovább.

## 2. feladat - gombok használata

🧪 Feladat – Gombokkal vezérelt LED

Ebben a feladatban a két kapott gomb segítségével fogunk egy LED-et vezérelni.
Feladat leírása:

1. Kösd be a két gombot és a LED-et az Arduino-hoz.
2. Írj olyan programot, amely:

      - Ha az első gombot megnyomod, a LED felkapcsol.
      - Ha a második gombot nyomod meg, a LED lekapcsol.

Ez a feladat segít megérteni a digitális bemenetek (gombok) és a digitális kimenetek (LED) működését, valamint a feltételes vezérlést.

## 3. feladat - szervó motor bekotése és vezértlése

🧠 A legnehezebb feladat – Szervóvezérlés gombokkal és LED-del

Ez lesz a legösszetettebb feladat, mert a szervómotor vezérléséhez egy külön könyvtárat (library-t) is használnod kell. A dokumentációban található példa nem használ könyvtárat, de az a megoldás sokkal bonyolultabb lenne, ezért itt a könyvtáras módszert ajánljuk.
Feladat leírása:

- Kösd be a két gombot, a LED-et, és a szervómotort.
- Ha az első gombot lenyomod, a szervó 0 fokba forduljon.
- Ha a második gombot nyomod meg, a szervó 180 fokba forduljon.
- A LED világítson, csak akkor, amikor a szervó 180 fokos állásban van.

A feladat során tehát:

- Meg kell ismerned a Servo könyvtár használatát.
- Érzékelned kell a gombnyomásokat.
- A szervót a megfelelő pozícióba kell mozgatnod.
- A LED-et az aktuális pozíció alapján kell ki-/bekapcsolni.

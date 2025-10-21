# C++ Tananyag – Foci forduló feldolgozása fájlból

---

## 1. Fejezet – Fájlbeolvasás és adatszerkezetek

### 🧩 1.1. A feladat célja

Egy focibajnokság fordulóinak eredményeit kell feldolgoznunk.  
A mérkőzéseket a **merkozes.txt** fájl tartalmazza, minden sorban:  
``lőtt_gólok kapott_gólok hazai_csapat idegen_csapat``  

Példa a fájl tartalmára:
```

2 1 fradi ute
3 3 vasas mtk
1 0 dvsc diosgyor

```

Célunk:
- beolvasni az adatokat,
- megszámolni a mérkőzéseket,
- megállapítani hány csapat nyert otthon,
- megkeresni, ki rúgta a legtöbb gólt,
- vizsgálni volt-e döntetlen,
- és lekérdezni, hány gólt lőtt az **UTE**.

---

### 🧩 1.2. A program váza és a `struct` létrehozása

Minden mérkőzést egy **struktúrában** tárolunk.  
A struktúra olyan, mint egy „doboz”, ami különböző típusú adatokat tartalmaz: számokat, szövegeket együtt.

```cpp
// innentől új kód.
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

// Egy mérkőzés adatai
struct fordulo
{
    int lott;    // hány gólt rúgott a hazai csapat
    int kapott;  // hány gólt kapott
    string nev1; // hazai csapat neve
    string nev2; // vendégcsapat neve
};

int main()
{
    int i, db = 0; // számlálók
    fordulo A[8];  // legfeljebb 8 mérkőzést tárolunk
}
```

> 💡 **Megjegyzés:**
> A `struct` C++-ban hasonló, mint C#-ban a `class`,
> de alapértelmezetten minden adattagja **publikus**, és általában adathalmazokra használjuk.

---

### 🧩 1.3. Fájl megnyitása és beolvasása

A fájlbeolvasáshoz az `ifstream` osztályt használjuk.
Ha a fájl nem nyitható meg, a program leáll.

```cpp
// innentől új kód.
int main()
{
int i, db = 0;
fordulo A[8];

ifstream be("merkozes.txt"); // fájl megnyitása
if (be.fail())               // hiba esetén kilép
{
    cout << "Hiba a fájl megnyitásakor!" << endl;
    return 1; // program leáll
}

// soronként beolvasás
for (i = 0; i < 8 && !be.eof(); i++)
{
    be >> A[i].lott >> A[i].kapott >> A[i].nev1 >> A[i].nev2;
    db++; // nő a meccsek száma
    cout << A[i].lott << " " << A[i].kapott << " " 
         << A[i].nev1 << " " << A[i].nev2 << endl;
}

be.close(); // fájl bezárása
cout << "\nA fordulóban " << db << " mérkőzést játszottak." << endl;
}
```



> ⚙️ **Mi történik a memóriában?**  
> - Az `A` tömb 8 darab `fordulo` struktúrát tartalmaz.  
> - Minden `A[i]` külön meccs adatait őrzi.  
> - A `db` változó mutatja, hányat olvastunk be ténylegesen.

---

## 2. Fejezet – Elemzések: győzelmek, gólok, döntetlen

### 🧩 2.1. Hány csapat nyert otthon?

A hazai csapat nyert, ha `lott > kapott`.

```cpp
int nyert = 0;
for (i = 0; i < db; i++)
    if (A[i].lott > A[i].kapott)
        nyert++;

cout << nyert << " csapat győzött otthon." << endl;
```

> 🧠 **Logika:**
>
> * Minden elemnél megnézzük, ki lőtt több gólt.
> * A `nyert` számláló növekszik, ha a hazai csapat több gólt szerzett.

---

### 🧩 2.2. Melyik csapat rúgta a legtöbb gólt?

Itt **maximumkeresést** végzünk:

* összevetjük az aktuális legtöbb gólt (`max`),
* ha találunk nagyobbat, frissítjük a `max` értéket és elmentjük a csapat nevét.

```cpp
string maxcsapat;
int max = 0;

for (i = 0; i < db; i++)
{
if (A[i].lott > max)
{
max = A[i].lott;
maxcsapat = A[i].nev1;
}
if (A[i].kapott > max)
{
max = A[i].kapott;
maxcsapat = A[i].nev2;
}
}

cout << "A legtöbb gólt a " << maxcsapat << " lőtte (" << max << ")." << endl;

```

> 💬 **Tipp:**  
> Mivel mind a hazai, mind a vendég csapat rúghat sok gólt, mindkettőt külön vizsgálni kell.

---

### 🧩 2.3. Volt-e döntetlen mérkőzés?

Ha `lott == kapott`, akkor döntetlen.  
Ezt `while` ciklussal is vizsgálhatjuk: ha találunk ilyet, megállunk.

```cpp
i = 0;
while (i < db && A[i].lott != A[i].kapott)
    i++;

if (i < db)
    cout << "Volt döntetlen mérkőzés." << endl;
else
    cout << "Nem volt döntetlen mérkőzés." << endl;
```

> 🔍 **Megfigyelés:**
> A `while` addig fut, amíg nincs döntetlen.
> Ha a ciklus vége előtt megáll, akkor találtunk ilyet.

---

## 3. Fejezet – Keresés: az UTE csapat góljai

A cél: megkeresni, hány gólt lőtt (vagy kapott) az **UTE**.

* Ha az UTE az első csapat (`nev1`), akkor a `lott` értéke az övé.
* Ha az UTE a második (`nev2`), akkor a `kapott` érték lesz a rúgott góljai száma a másik szemszögből.

```cpp
i = 0;
while (i < db && !(A[i].nev1 == "ute" || A[i].nev2 == "ute"))
i++;

if (A[i].nev1 == "ute")
cout << A[i].lott << " gólt lőtt az UTE." << endl;
else
cout << A[i].kapott << " gólt kapott az UTE." << endl;

```

> 🧠 **Memóriában:**  
> - A ciklus végigmegy a tömbön,  
> - megkeresi azt az indexet (`i`), ahol bármelyik csapat neve `"ute"`.  
> - Az `if` alapján eldönti, hogy hazai vagy vendég volt.

---

### ✅ Összefoglalás

A program:
1. Beolvassa a meccsek adatait fájlból  
2. Kiírja a meccsek számát  
3. Megszámolja a hazai győzelmeket  
4. Megkeresi, ki rúgta a legtöbb gólt  
5. Ellenőrzi, volt-e döntetlen  
6. Megmutatja az UTE eredményét  

---

### 🎯 Teljes, futtatható kód

```cpp
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct fordulo
{
    int lott, kapott;
    string nev1, nev2;
};

int main()
{
    int i, db = 0, nyert = 0;
    fordulo A[8];
    ifstream be("merkozes.txt");
    if (be.fail())
    {
        cout << "hiba" << endl;
        return 1;
    }

    for (i = 0; i < 8 && !be.eof(); i++)
    {
        be >> A[i].lott >> A[i].kapott >> A[i].nev1 >> A[i].nev2;
        db++;
        cout << A[i].lott << " " << A[i].kapott << " "
             << A[i].nev1 << " " << A[i].nev2 << endl;
    }

    cout << "\nA fordulóban " << db << " mérkőzést játszottak.\n";

    for (i = 0; i < db; i++)
        if (A[i].lott > A[i].kapott)
            nyert++;
    cout << nyert << " csapat győzött otthon.\n";

    string maxcsapat;
    int max = 0;
    for (i = 0; i < db; i++)
    {
        if (A[i].lott > max) { max = A[i].lott; maxcsapat = A[i].nev1; }
        if (A[i].kapott > max) { max = A[i].kapott; maxcsapat = A[i].nev2; }
    }
    cout << "A legtöbb gólt a " << maxcsapat << " lőtte.\n";

    i = 0;
    while (i < db && A[i].lott != A[i].kapott)
        i++;
    if (i < db)
        cout << "Volt döntetlen mérkőzés.\n";

    i = 0;
    while (i < db && !(A[i].nev1 == "ute" || A[i].nev2 == "ute"))
        i++;
    if (A[i].nev1 == "ute")
        cout << A[i].lott << " gólt lőtt az UTE.\n";
    else
        cout << A[i].kapott << " gólt kapott az UTE.\n";

    return 0;
}
```


---

Szeretnéd, hogy a következő anyagban (pl. **2. rész – algoritmusok elemzése és bővítése**) mélyebben bemutassam a `max keresés`, `while` logika, és `fájlkezelés` működését (pl. memóriaábra, példák, hibakezelés)?
```

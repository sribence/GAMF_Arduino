# 1. feladat - A lift mozgatása és alap vezérlése

```cpp
// A motor csatlakozói
const int DIR_PIN = 10;
const int STEP_PIN = 9;
const int EN_PIN = 8;

// Minél nagyobb annál lassabb, de ne vedd túl lassúra mert akkor nem fog menni
const int Sebesseg = 200;

void setup() 
{
    // Soros port indítása
    Serial.begin(9600);

    // Csatlakozások beállítása kimenetire
    pinMode(DIR_PIN, OUTPUT);
    pinMode(STEP_PIN, OUTPUT);
    pinMode(EN_PIN, OUTPUT);

    // Kikapcsoljuk a motor működését
    digitalWrite(EN_PIN, HIGH);

    Serial.println("\n\nHello vilag");
    delay(1000); // Várjunk 1 másodpercet
}

void loop() 
{
    // 10000 lépés felfelé
    Serial.println("Mozgas fel . . .");
    digitalWrite(DIR_PIN, LOW);
    digitalWrite(EN_PIN, LOW);
    for (int i = 0; i < 10000; i++)
    {
        digitalWrite(STEP_PIN, HIGH);
        delayMicroseconds(Sebesseg);
        digitalWrite(STEP_PIN, LOW);
        delayMicroseconds(Sebesseg);
    }
    
    // 10000 lépés lefelé
    Serial.println("Mozgas le . . .");
    digitalWrite(DIR_PIN, HIGH);
    digitalWrite(EN_PIN, LOW);
    for (int i = 0; i < 10000; i++)
    {
        digitalWrite(STEP_PIN, HIGH);
        delayMicroseconds(Sebesseg);
        digitalWrite(STEP_PIN, LOW);
        delayMicroseconds(Sebesseg);
    }
}
```

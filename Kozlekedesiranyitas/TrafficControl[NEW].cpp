//////////////////////////////////////////////////////////
//                  Változók definíciója                 //
//////////////////////////////////////////////////////////
const int SOROMPO_PIN = 6;              // Sorompó szervó motor PIN-je
const int ELSO_PAR_ZOLD = 8;            // Első pár zöld lámpa PIN-je
const int ELSO_PAR_SARGA = 9;           // Első pár sárga lámpa PIN-je
const int ELSO_PAR_PIROS = 10;          // Első pár piros lámpa PIN-je
const int MASODIK_PAR_ZOLD = 11;        // Második pár zöld lámpa PIN-je
const int MASODIK_PAR_SARGA = 12;       // Második pár sárga lámpa PIN-je
const int MASODIK_PAR_PIROS = 13;       // Második pár piros lámpa PIN-je
const int VARAKOZAS_GOMB = 2;           // Várakozási mód gomb PIN-je
const int VONAT_ERKEZIK = 3;            // Vonat érkezik gomb PIN-je
const int VONAT_ELMENT = 4;             // Vonat elment gomb PIN-je

// Időzítések (milliszekundumban)
const unsigned int ZOLD_IDO = 5000;     // Zöld lámpa időtartama
const unsigned int VARAKOZAS_IDO = 1500;// Várakozási idő
const unsigned int VILLOGAS_IDO = 500;  // Várakozási mód villogás ideje

// Állapotgép definíciója
enum Allapot {
    ELSO_PAR_ZOLD_ON,
    MASODIK_PAR_ZOLD_ON,
    ELSO_PAR_VARAKOZIK,
    MASODIK_PAR_VARAKOZIK,
    VARAKOZASI_MOD
};

// Segédváltozók
unsigned int Idozito;
bool VarakozasGombNyomva = false;
Allapot JelenlegiAllapot = ELSO_PAR_ZOLD_ON;

// Lámpa állapotok kezelése
struct LampakAllapota {
    bool zold;
    bool sarga;
    bool piros;
};

// Lámpa állapotok beállítása
void LampakBeallitasa(int zold_pin, int sarga_pin, int piros_pin, LampakAllapota allapot) {
    digitalWrite(zold_pin, allapot.zold ? HIGH : LOW);
    digitalWrite(sarga_pin, allapot.sarga ? HIGH : LOW);
    digitalWrite(piros_pin, allapot.piros ? HIGH : LOW);
}

// Sorompó vezérlése
void SorompoVezerele(int szog) {
    int impulzus = (szog * 11) + 500;
    for (int i = 0; i < 50; i++) {
        digitalWrite(SOROMPO_PIN, HIGH);
        delayMicroseconds(impulzus);
        digitalWrite(SOROMPO_PIN, LOW);
        delay(20 - impulzus / 1000);
    }
}

void setup() {
    // PIN-ek beállítása
    pinMode(SOROMPO_PIN, OUTPUT);
    pinMode(ELSO_PAR_ZOLD, OUTPUT);
    pinMode(ELSO_PAR_SARGA, OUTPUT);
    pinMode(ELSO_PAR_PIROS, OUTPUT);
    pinMode(MASODIK_PAR_ZOLD, OUTPUT);
    pinMode(MASODIK_PAR_SARGA, OUTPUT);
    pinMode(MASODIK_PAR_PIROS, OUTPUT);
    pinMode(VARAKOZAS_GOMB, INPUT);
    pinMode(VONAT_ERKEZIK, INPUT);
    pinMode(VONAT_ELMENT, INPUT);

    Serial.begin(9600);
    Idozito = millis();
}

// Állapotgép függvények
void ElsoParZoldAllapot() {
    LampakBeallitasa(ELSO_PAR_ZOLD, ELSO_PAR_SARGA, ELSO_PAR_PIROS, {true, false, false});
    LampakBeallitasa(MASODIK_PAR_ZOLD, MASODIK_PAR_SARGA, MASODIK_PAR_PIROS, {false, false, true});
    if (millis() - Idozito >= ZOLD_IDO) {
        Idozito = millis();
        JelenlegiAllapot = MASODIK_PAR_VARAKOZIK;
    }
}

void MasodikParZoldAllapot() {
    LampakBeallitasa(ELSO_PAR_ZOLD, ELSO_PAR_SARGA, ELSO_PAR_PIROS, {false, false, true});
    LampakBeallitasa(MASODIK_PAR_ZOLD, MASODIK_PAR_SARGA, MASODIK_PAR_PIROS, {true, false, false});
    if (millis() - Idozito >= ZOLD_IDO) {
        Idozito = millis();
        JelenlegiAllapot = ELSO_PAR_VARAKOZIK;
    }
}

void ElsoParVarakozik() {
    LampakBeallitasa(ELSO_PAR_ZOLD, ELSO_PAR_SARGA, ELSO_PAR_PIROS, {false, true, true});
    LampakBeallitasa(MASODIK_PAR_ZOLD, MASODIK_PAR_SARGA, MASODIK_PAR_PIROS, {false, true, false});
    if (millis() - Idozito >= VARAKOZAS_IDO) {
        Idozito = millis();
        JelenlegiAllapot = ELSO_PAR_ZOLD_ON;
    }
}

void MasodikParVarakozik() {
    LampakBeallitasa(ELSO_PAR_ZOLD, ELSO_PAR_SARGA, ELSO_PAR_PIROS, {false, true, false});
    LampakBeallitasa(MASODIK_PAR_ZOLD, MASODIK_PAR_SARGA, MASODIK_PAR_PIROS, {false, true, true});
    if (millis() - Idozito >= VARAKOZAS_IDO) {
        Idozito = millis();
        JelenlegiAllapot = MASODIK_PAR_ZOLD_ON;
    }
}

void VarakozasiMod() {
    if (millis() - Idozito < VILLOGAS_IDO) {
        // Mindkét pár sárgán villog
        LampakBeallitasa(ELSO_PAR_ZOLD, ELSO_PAR_SARGA, ELSO_PAR_PIROS, {false, true, false});
        LampakBeallitasa(MASODIK_PAR_ZOLD, MASODIK_PAR_SARGA, MASODIK_PAR_PIROS, {false, true, false});
    } else if (millis() - Idozito < VILLOGAS_IDO * 2) {
        // Mindkét pár kikapcsolva
        LampakBeallitasa(ELSO_PAR_ZOLD, ELSO_PAR_SARGA, ELSO_PAR_PIROS, {false, false, false});
        LampakBeallitasa(MASODIK_PAR_ZOLD, MASODIK_PAR_SARGA, MASODIK_PAR_PIROS, {false, false, false});
    } else {
        Idozito = millis();
    }
}

void loop() {
    // Állapotgép kezelése
    switch (JelenlegiAllapot) {
        case ELSO_PAR_ZOLD_ON:
            ElsoParZoldAllapot();
            break;
        case MASODIK_PAR_ZOLD_ON:
            MasodikParZoldAllapot();
            break;
        case ELSO_PAR_VARAKOZIK:
            ElsoParVarakozik();
            break;
        case MASODIK_PAR_VARAKOZIK:
            MasodikParVarakozik();
            break;
        case VARAKOZASI_MOD:
            VarakozasiMod();
            break;
    }

    // Várakozási mód gomb kezelése
    if (digitalRead(VARAKOZAS_GOMB) == HIGH && !VarakozasGombNyomva) {
        VarakozasGombNyomva = true;
        JelenlegiAllapot = (JelenlegiAllapot == VARAKOZASI_MOD) ? ELSO_PAR_ZOLD_ON : VARAKOZASI_MOD;
    } else if (digitalRead(VARAKOZAS_GOMB) == LOW) {
        VarakozasGombNyomva = false;
    }

    // Vonat érzékelés kezelése
    if (digitalRead(VONAT_ERKEZIK) == HIGH) {
        SorompoVezerele(70);  // Sorompó leengedése
    } else if (digitalRead(VONAT_ELMENT) == HIGH) {
        SorompoVezerele(160); // Sorompó felemelése
    }
}

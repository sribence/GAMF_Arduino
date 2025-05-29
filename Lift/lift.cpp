#include <Arduino.h>
#include <Wire.h>
#include <Servo.h>
#include <Adafruit_LEDBackpack.h>
#include <Adafruit_GFX.h>

#define CS_PIN 2

#define DIR_PIN 10
#define STEP_PIN 9
#define EN_PIN 8

#define SERVO_PIN 11

#define BUZZER_PIN 12

const byte gomb[3] = {5, 6, 7};

Adafruit_8x8matrix matrix = Adafruit_8x8matrix();
Servo ajto;
byte ajto_poz = 0;
int motor_var = 0;
const int var_gyors = 200;
const int var_lassu = 400;
long poz = 0;
long cel_poz = 0;
long frissit = 0;
const long emelet_tavolsag = 30000;
const long atmenet = 3000;
byte emelet = 0;
byte cel_emelet = 0;
enum Irany {
    LE,
    FEL,
    NINCS,
};
Irany irany;
enum Allapot {
    STOP,
    VARAKOZAS,
    START,
    AJTONYITAS,
    AJTO_NYITVA,
    AJTOZARAS,
    INDULAS,
    MOZGASBAN,
    ERKEZES,
};
volatile Allapot allapot;

byte reverse(byte b) {
   b = (b & 0xF0) >> 4 | (b & 0x0F) << 4;
   b = (b & 0xCC) >> 2 | (b & 0x33) << 2;
   b = (b & 0xAA) >> 1 | (b & 0x55) << 1;
   return b;
}

byte rotr(byte val) {
    return (val >> 1) | (val << 7);
}

const uint16_t szam[4][5] = {
    {
        0b00000111,
        0b00000100,
        0b00000111,
        0b00000100,
        0b00000100,
    },
    {
        0b00000010,
        0b00000110,
        0b00000010,
        0b00000010,
        0b00000010,
    },
    {
        0b00000110,
        0b00000001,
        0b00000010,
        0b00000100,
        0b00000111,
    },
    {
        0b00000000,
        0b00000000,
        0b00000111,
        0b00000000,
        0b00000000,
    },
};

const uint16_t nyil[3][5] = {
    {
        0b00000010,
        0b00000010,
        0b00000010,
        0b00000111,
        0b00000010,
    },
    {
        0b00000010,
        0b00000111,
        0b00000010,
        0b00000010,
        0b00000010,
    },
    {
        0b00000000,
        0b00000000,
        0b00000000,
        0b00000000,
        0b00000000,
    },
};

void matrix_kiir() {
    for (byte i = 0; i < 5; ++i) {
        matrix.displaybuffer[i + 1] = rotr((reverse(nyil[irany][i]) >> 5) | (reverse(szam[emelet][i]) >> 1));
    }
    matrix.writeDisplay();
}

void serial_kiir() {
    Serial.print("a: ");
    Serial.print(allapot);
    Serial.print(", e: ");
    Serial.print(emelet);
    Serial.print(", ce: ");
    Serial.print(cel_emelet);
    Serial.print(", p: ");
    Serial.print(poz);
    Serial.print(", cp: ");
    Serial.print(cel_poz);
    Serial.println();
}

void leptet() {
    digitalWrite(STEP_PIN, HIGH);
    delayMicroseconds(motor_var);
    digitalWrite(STEP_PIN, LOW);
    delayMicroseconds(motor_var);
}

void allapotot_frissit(Allapot uj) {
    if (allapot == STOP) {
        return;
    }
    allapot = uj;
}

void iranyt_frissit(Irany uj) {
    irany = uj;
    switch (irany) {
        case FEL:
            digitalWrite(DIR_PIN, LOW);
            digitalWrite(EN_PIN, LOW);
            break;
        case LE:
            digitalWrite(DIR_PIN, HIGH);
            digitalWrite(EN_PIN, LOW);
            break;
        default:
            digitalWrite(EN_PIN, HIGH);
            break;
    }
}

void stop() {
    if (allapot == START) {
        return;
    }
    allapot = STOP;
}

void poziciot_frissit() {
    switch (irany) {
        case FEL:
            ++poz;
            break;
        case LE:
            --poz;
            break;
        default:
            break;
    }
}

void emeletet_frissit_indulaskor() {
    frissit = poz;
    switch (irany) {
        case FEL:
            frissit += emelet_tavolsag / 2;
            break;
        case LE:
            frissit -= emelet_tavolsag / 2;
            break;
        default:
            break;
    }
}

void emeletet_frissit() {
    if (poz != frissit) {
        return;
    }
    switch (irany) {
        case FEL:
            ++emelet;
            frissit += emelet_tavolsag;
            break;
        case LE:
            --emelet;
            frissit -= emelet_tavolsag;
            break;
        default:
            break;
    }
    matrix_kiir();
}

void ajtot_mozgat(int poz) {
    ajto.attach(SERVO_PIN);
    while (ajto_poz != poz) {
        ajto_poz < poz ? ++ajto_poz : --ajto_poz;
        ajto.write(ajto_poz);
        delay(10);
    }
    delay(500);
    ajto.detach();
}

void hang() {
    tone(BUZZER_PIN, 200);
    delay(500);
    noTone(BUZZER_PIN);
}

void setup() {
    Serial.begin(9600);
    Serial.println();
    Serial.println("Setup started");
    attachInterrupt(digitalPinToInterrupt(CS_PIN), stop, FALLING);
    matrix.begin(0x70);
    pinMode(DIR_PIN, OUTPUT);
    pinMode(STEP_PIN, OUTPUT);
    pinMode(EN_PIN, OUTPUT);
    digitalWrite(EN_PIN, HIGH);
    pinMode(BUZZER_PIN, OUTPUT);
    allapot = STOP;
    Serial.println("Setup completed");
}

void loop() {
    switch (allapot) {
        case STOP:
            emelet = 3;
            iranyt_frissit(NINCS);
            matrix_kiir();
            serial_kiir();
            Serial.println("Stop");
            delay(1000);
            allapot = VARAKOZAS;
            break;
        case VARAKOZAS:
        {
            unsigned long start = millis();
            while (!digitalRead(gomb[0])) {
                if (millis() - start > 2000) {
                    allapotot_frissit(START);
                    return;
                }
            }
            break;
        }
        case START:
            emelet = 3;
            iranyt_frissit(LE);
            matrix_kiir();
            ajtot_mozgat(10);
            delay(4000);
            motor_var = 300;
            while (digitalRead(CS_PIN)) {
                leptet();
            }
            iranyt_frissit(FEL);
            matrix_kiir();
            for (long i = 0; i < 10000; ++i) {
                leptet();
            }
            poz = 0;
            emelet = 0;
            iranyt_frissit(NINCS);
            allapotot_frissit(AJTONYITAS);
            matrix_kiir();
            serial_kiir();
            break;
        case AJTONYITAS:
            delay(2000);
            ajtot_mozgat(170);
            delay(2000);
            allapotot_frissit(AJTO_NYITVA);
            break;
        case AJTO_NYITVA:
            for (byte i = 0; i < 3; ++i) {
                if (i != emelet && !digitalRead(gomb[i])) {
                    cel_emelet = i;
                    cel_poz = cel_emelet * emelet_tavolsag;
                    iranyt_frissit(cel_emelet > emelet ? FEL : LE);
                    emeletet_frissit_indulaskor();
                    allapotot_frissit(AJTOZARAS);
                    matrix_kiir();
                    serial_kiir();
                    break;
                }
            }
            break;
        case AJTOZARAS:
            delay(2000);
            ajtot_mozgat(10);
            delay(2000);
            allapotot_frissit(INDULAS);
            break;
        case INDULAS:
            for (long i = 0; i < atmenet; ++i) {
                motor_var = var_gyors + (1 - ((float)i / atmenet)) * (var_lassu - var_gyors);
                leptet();
                poziciot_frissit();
                if (allapot == STOP) {
                    return;
                }
            }
            allapotot_frissit(MOZGASBAN);
            break;
        case MOZGASBAN:
            motor_var = var_gyors;
            while (abs(cel_poz - poz) > atmenet) {
                leptet();
                poziciot_frissit();
                emeletet_frissit();
                if (allapot == STOP) {
                    return;
                }
            }
            allapotot_frissit(ERKEZES);
            break;
        case ERKEZES:
            for (long i = 0; i < atmenet; ++i) {
                motor_var = var_gyors + ((float)i / atmenet) * (var_lassu - var_gyors);
                leptet();
                poziciot_frissit();
                if (allapot == STOP) {
                    return;
                }
            }
            iranyt_frissit(NINCS);
            allapotot_frissit(AJTONYITAS);
            matrix_kiir();
            serial_kiir();
            hang();
            break;
    }
}

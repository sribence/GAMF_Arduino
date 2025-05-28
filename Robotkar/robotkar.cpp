#include <Arduino.h>
#include <Servo.h>
#include <Adafruit_NeoPixel.h>

/*
D0
D1

GND
5V

D11 - Servo 1
D10 - Servo 2
D9 - Servo 3
D6 - Servo 4
D5 - Servo 5
D4 - Servo 6

A0 - Control 1
A1 - Control 2
A2 - Control 3
A3 - Control 4
*/

Adafruit_NeoPixel strip(16, 23, NEO_GRB + NEO_KHZ800);

uint32_t yellow = strip.Color(25, 15, 0);
uint32_t red = strip.Color(25, 0, 0);

class MyServo {
private:
    byte pin;
    bool reversed;
    float deg;
    int pulse_width;
    Servo servo;
public:
    byte speed;
    int p_min;
    int p_max;
    int d_min;
    int d_max;
    MyServo() {};
    MyServo(byte pin, int p_min, int p_max, int d_min, int d_max, byte speed, float pos, bool reversed = false) {
        this->pin = pin;
        this->p_min = p_min;
        this->p_max = p_max;
        this->d_min = d_min;
        this->d_max = d_max;
        this->deg = d_min + (d_max - d_min) * pos;
        this->reversed = reversed;
    }
    void attach() {
        servo.attach(pin, 400, 2500);
        set_deg(deg);
    }
    int get_pulse_width() {
        return pulse_width;
    }
    float step() {
        return (float)(d_max - d_min) / (p_max - p_min);
    }
    float get_deg() {
        return deg;
    }
    float get_deg_calc() {
        return d_min + (float)(d_max - d_min) * (pulse_width - p_min) / (p_max - p_min);
    }
    int map_deg(float v) {
        return p_min + (v - d_min) * (p_max - p_min) / (d_max - d_min);
    }
    void add_deg(float v) {
        set_deg(deg + v);
    }
    void set_deg(float v) {
        if (v < d_min || v > d_max) {
            return;
        }
        deg = v;
        pulse_width = map_deg(deg);
        servo.writeMicroseconds(pulse_width);
    }
    void set_pulse(int v) {
        //pulse_width = v;
        servo.writeMicroseconds(v);
    }
};

MyServo servo_array[] = {
    MyServo(11, 650, 1950, -90, 90, 1, 0.5),
    MyServo(10, 500, 1800, -90, 90, 1, 0.5),
    MyServo( 9, 750, 1750,   0, 90, 1, 0),
    MyServo( 6, 700, 1700,   0, 90, 1, 0),
    MyServo( 5, 500, 1700,   0, 90, 1, 1),
    MyServo( 4, 544, 2400, -90, 90, 1, 0.5),
};

byte const servo_count = sizeof(servo_array) / sizeof(servo_array[0]);

class Servos {
private:
    MyServo* servos;
public:
    float new_deg[servo_count];
    float saved[10][servo_count];
    Servos(MyServo* s) {
        servos = s;
    }
    MyServo& operator[](int index) {
        return servos[index];
    }
    void move(int del = 10) {
        strip.fill(red);
        strip.show();
        int max = 0;
        for (byte i = 0; i < servo_count; ++i) {
            int dif = ceil(abs(new_deg[i] - servos[i].get_deg()));
            if (dif > max) {
                max = dif;
            }
        }
        max *= 5;
        for (int i = max; i > 0; --i) {
            for (byte j = 0; j < servo_count; ++j) {
                servos[j].add_deg((new_deg[j] - servos[j].get_deg()) / i);
            }
            delay(del);
        }
        delay(1000);
        strip.fill(yellow);
        strip.show();
    }
    void save(byte idx) {
        for (byte i = 0; i < servo_count; ++i) {
            saved[idx][i] = servos[i].get_deg();
        }
    }
    void load(byte idx) {
        for (byte i = 0; i < servo_count; ++i) {
            new_deg[i] = saved[idx][i];
        }
    }
};

Servos servos(servo_array);

String get_param(String& com, char delim = ' ') {
    if (com.length() == 0) {
        return com;
    }
    String param;
    int first = 0;
    int last = com.indexOf(delim);
    while (last == first) {
        first = last + 1;
        last = com.indexOf(delim, first);
    }
    if (last >= 0) {
        param = com.substring(first, last);
        com = com.substring(last + 1);
    } else {
        param = com;
        com = "";
    }
    return param;
}

void process_command() {
    if (Serial.available() == 0) {
        return;
    }
    String com = Serial.readStringUntil('\n');
    if (com.length() >= 1 && com[com.length() - 1] == '\r') {
        com = com.substring(0, com.length() - 1);
    }
    String param = get_param(com);
    if (param == "go") {
        servos.move();
    } else if (param == "mov") {
        int i = get_param(com).toInt();
        float deg = get_param(com).toFloat();
        if (i < 0 || i >= servo_count) {
            return;
        }
        if (deg < servos[i].d_min || deg > servos[i].d_max) {
            return;
        }
        servos.new_deg[i] = deg;
    } else if (param == "save") {
        int i = get_param(com).toInt();
        for (byte j = 0; j < servo_count; ++j) {
            servos.saved[i][j] = get_param(com).toFloat();
        }
    } else if (param == "save_cur") {
        int i = get_param(com).toInt();
        servos.save(i);
    } else if (param == "load") {
        int i = get_param(com).toInt();
        servos.load(i);
    } else if (param == "info") {
        for (byte i = 0; i < servo_count; ++i) {
            Serial.print(i);
            Serial.print(". ");
            Serial.print(servos[i].get_deg(), 1);
            Serial.print(" [");
            Serial.print(servos[i].d_min);
            Serial.print(" - ");
            Serial.print(servos[i].d_max);
            Serial.print("], step: ");
            Serial.println(servos[i].step(), 1);
        }
        for (byte i = 0; i < servo_count; ++i) {
            Serial.print(servos[i].get_deg(), 1);
            Serial.print(" ");
        }
        Serial.println();
    } else {
        Serial.println("Command not found");
        return;
    }
    Serial.println("Success");
}

void wait_serial() {
    Serial.println("Press Enter to continue...");
    while (Serial.available() == 0);
    Serial.readStringUntil('\n');
}

void setup() {
    Serial.begin(9600);
    Serial.println();
    Serial.println("Setup started");
    strip.begin();
    strip.fill(red);
    strip.show();
    for (byte i = 0; i < servo_count; ++i) {
        Serial.print(i);
        Serial.println(". servo init");
        wait_serial();
        servos[i].attach();
        servos.new_deg[i] = servos[i].get_deg();
    }
    strip.fill(yellow);
    strip.show();
    Serial.println("Setup completed");
}

void loop() {
    process_command();
}

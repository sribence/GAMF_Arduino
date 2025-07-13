/*  ___   ___  ___  _   _  ___   ___   ____ ___  ____  
 * / _ \ /___)/ _ \| | | |/ _ \ / _ \ / ___) _ \|    \ 
 *| |_| |___ | |_| | |_| | |_| | |_| ( (__| |_| | | | |
 * \___/(___/ \___/ \__  |\___/ \___(_)____)___/|_|_|_|
 *                  (____/ 
 * Arduino Mecanum Omni Direction Wheel Robot Car lesson 3: Line Tracking - 5-point tracking sensor
 * Tutorial URL http://osoyoo.com/?p=30022
 * CopyRight www.osoyoo.com
 * 
 */
//if your car speed too fast or too slow or not moving, please adjust MID_SPEED,HIGH_SPEED,LOW_SPEED value in line 13,14,15,
 // these values control the current power of your car motors


// Ha a robot túl gyors, túl lassú, vagy nem mozdul meg,
// akkor itt lehet állítani a motorok sebességét 0-255 értéken
#define MID_SPEED 20       // Közepes sebesség
#define HIGH_SPEED 20      // Magas sebesség
#define LOW_SPEED 20       // Alacsony sebesség

// Késleltetési idők (ms)
#define LONG_DELAY_TIME 150 
#define DELAY_TIME 150
#define SHORT_DELAY_TIME 150

// Elülső jobb motorvezérlés
#define speedPinR 9               // PWM kimenet jobb első motorra
#define RightMotorDirPin1  22     // Irányvezérlés IN1
#define RightMotorDirPin2  24     // Irányvezérlés IN2

// Elülső bal motorvezérlés
#define LeftMotorDirPin1  26      // IN3
#define LeftMotorDirPin2  28      // IN4
#define speedPinL 10              // PWM kimenet bal első motorra

// Hátsó jobb motorvezérlés
#define speedPinRB 11
#define RightMotorDirPin1B  5     // IN1 (hátsó jobb)
#define RightMotorDirPin2B  6     // IN2 (hátsó jobb)

// Hátsó bal motorvezérlés
#define LeftMotorDirPin1B  7      // IN3 (hátsó bal)
#define LeftMotorDirPin2B  8      // IN4 (hátsó bal)
#define speedPinLB 12             // PWM kimenet hátsó bal motorra

// 5 pontból álló vonalkövető szenzor definiálása (balról jobbra)
#define sensor1   A4  // Bal szélső
#define sensor2   A3  // Bal közép
#define sensor3   A2  // Középső
#define sensor4   A1  // Jobb közép
#define sensor5   A0  // Jobb szélső

#include <Servo.h>        // Szervó vezérléséhez szükséges könyvtár

Servo servo;              // Szervó példány létrehozása

const int TrigPin = 31;   // Ultrahangos szenzor trigger láb
const int EchoPin = 30;   // Ultrahangos szenzor echo láb

int duration = 0;         // A visszaverődő jel időtartama
int distance = 0;         // Távolság centiméterben

/*motor vezérlés*/
// Elülső jobb kerék előre
void FR_fwd(int speed) {
  digitalWrite(RightMotorDirPin1, HIGH);
  digitalWrite(RightMotorDirPin2, LOW); 
  analogWrite(speedPinR, speed);  // PWM jel a sebesség szabályozásához
}

// Elülső jobb kerék hátra
void FR_bck(int speed) {
  digitalWrite(RightMotorDirPin1, LOW);
  digitalWrite(RightMotorDirPin2, HIGH); 
  analogWrite(speedPinR, speed);
}

// Elülső bal kerék előre
void FL_fwd(int speed) {
  digitalWrite(LeftMotorDirPin1, HIGH);
  digitalWrite(LeftMotorDirPin2, LOW);
  analogWrite(speedPinL, speed);
}

// Elülső bal kerék hátra
void FL_bck(int speed) {
  digitalWrite(LeftMotorDirPin1, LOW);
  digitalWrite(LeftMotorDirPin2, HIGH);
  analogWrite(speedPinL, speed);
}

// Hátsó jobb kerék előre
void RR_fwd(int speed) {
  digitalWrite(RightMotorDirPin1B, HIGH);
  digitalWrite(RightMotorDirPin2B, LOW); 
  analogWrite(speedPinRB, speed);
}

// Hátsó jobb kerék hátra
void RR_bck(int speed) {
  digitalWrite(RightMotorDirPin1B, LOW);
  digitalWrite(RightMotorDirPin2B, HIGH); 
  analogWrite(speedPinRB, speed);
}

// Hátsó bal kerék előre
void RL_fwd(int speed) {
  digitalWrite(LeftMotorDirPin1B, HIGH);
  digitalWrite(LeftMotorDirPin2B, LOW);
  analogWrite(speedPinLB, speed);
}

// Hátsó bal kerék hátra
void RL_bck(int speed) {
  digitalWrite(LeftMotorDirPin1B, LOW);
  digitalWrite(LeftMotorDirPin2B, HIGH);
  analogWrite(speedPinLB, speed);
}

// Előrehaladás: bal és jobb oldal eltérő sebességgel
void forward(int speed_left, int speed_right) {
  RL_fwd(speed_left);
  RR_fwd(speed_right);
  FR_fwd(speed_right);
  FL_fwd(speed_left); 
}

// Hátramenet minden kerékkel
void reverse(int speed) {
  RL_bck(speed);
  RR_bck(speed);
  FR_bck(speed);
  FL_bck(speed); 
}

// Jobbra csúszás (right strafe)
void right_shift(int speed_fl_fwd, int speed_rl_bck, int speed_rr_fwd, int speed_fr_bck) {
  FL_fwd(speed_fl_fwd); 
  RL_bck(speed_rl_bck); 
  RR_fwd(speed_rr_fwd);
  FR_bck(speed_fr_bck);
}

// Balra csúszás (left strafe)
void left_shift(int speed_fl_bck, int speed_rl_fwd, int speed_rr_bck, int speed_fr_fwd) {
  FL_bck(speed_fl_bck);
  RL_fwd(speed_rl_fwd);
  RR_bck(speed_rr_bck);
  FR_fwd(speed_fr_fwd);
}

// Balra fordulás (statikus balra)
void left_turn(int speed) {
  RL_bck(0);        // bal hátsó nem forog
  RR_fwd(speed);    // jobb hátsó előre
  FR_fwd(speed);    // jobb első előre
  FL_bck(0);        // bal első nem forog
}

// Jobbra fordulás (statikus jobbra)
void right(int speed) {
  RL_fwd(speed);
  RR_bck(0);
  FR_bck(0);
  FL_fwd(speed); 
}

// Balra fordulás másik variáns
void left(int speed) {
  RL_fwd(0);
  RR_bck(speed);
  FR_bck(speed);
  FL_fwd(0); 
}

// Jobbra hátramenet (íves mozgás)
void right_back(int speed) {
  RL_bck(speed);
  RR_fwd(0);
  FR_fwd(0);
  FL_bck(speed); 
}

// Éles jobbra fordulás (U-turn jobbra)
void sharpRightTurn(int speed_left, int speed_right) {
  RL_fwd(speed_left);
  RR_bck(speed_right);
  FR_bck(speed_right);
  FL_fwd(speed_left); 
}

// Éles balra fordulás (U-turn balra)
void sharpLeftTurn(int speed_left, int speed_right) {
  RL_bck(speed_left);
  RR_fwd(speed_right);
  FR_fwd(speed_right);
  FL_bck(speed_left); 
}

 
// A robot összes motorját leállítja
void stop_bot() {
  // PWM-eket 0-ra állítjuk
  analogWrite(speedPinLB, 0);
  analogWrite(speedPinRB, 0);
  analogWrite(speedPinL, 0);
  analogWrite(speedPinR, 0);
  
  // Irányvezérlő lábakat LOW-ra állítjuk
  digitalWrite(RightMotorDirPin1B, LOW);
  digitalWrite(RightMotorDirPin2B, LOW);   
  digitalWrite(LeftMotorDirPin1B, LOW);
  digitalWrite(LeftMotorDirPin2B, LOW); 
  digitalWrite(RightMotorDirPin1, LOW);
  digitalWrite(RightMotorDirPin2, LOW);   
  digitalWrite(LeftMotorDirPin1, LOW);
  digitalWrite(LeftMotorDirPin2, LOW); 
  
  delay(150);  // rövid szünet a megállás után
}


//Pins initialize
void init_GPIO()
{
  // Első jobb oldali motor – irányvezérlő lábak (K1 relé modulhoz)
  pinMode(RightMotorDirPin1, OUTPUT); 
  pinMode(RightMotorDirPin2, OUTPUT); 

  // Első bal oldali motor – sebességvezérlés (PWM jel a motorvezérlőhöz)
  pinMode(speedPinL, OUTPUT);  

  // Első bal oldali motor – irányvezérlő lábak (K3 relé modulhoz)
  pinMode(LeftMotorDirPin1, OUTPUT);
  pinMode(LeftMotorDirPin2, OUTPUT); 

  // Első jobb oldali motor – sebességvezérlés (PWM jel a motorvezérlőhöz)
  pinMode(speedPinR, OUTPUT);

  // Hátsó jobb oldali motor – irányvezérlő lábak (másik motorvezérlő modul K1)
  pinMode(RightMotorDirPin1B, OUTPUT); 
  pinMode(RightMotorDirPin2B, OUTPUT); 

  // Hátsó bal oldali motor – sebességvezérlés (PWM jel)
  pinMode(speedPinLB, OUTPUT);  

  // Hátsó bal oldali motor – irányvezérlő lábak (K3 relé modul)
  pinMode(LeftMotorDirPin1B, OUTPUT);
  pinMode(LeftMotorDirPin2B, OUTPUT); 

  // Hátsó jobb oldali motor – sebességvezérlés (PWM jel)
  pinMode(speedPinRB, OUTPUT);

  // IR vonalkövető szenzorok bemeneti üzemmódban
  pinMode(sensor1, INPUT);  // Bal szélső szenzor
  pinMode(sensor2, INPUT);  // Bal középső szenzor
  pinMode(sensor3, INPUT);  // Középső szenzor
  pinMode(sensor4, INPUT);  // Jobb középső szenzor
  pinMode(sensor5, INPUT);  // Jobb szélső szenzor

  // Robot leállítása biztonsági okokból indulás előtt
  stop_bot();
}

void init_ultras()
{
  pinMode(TrigPin , OUTPUT);  // Trigger láb – jelet küld ki
  pinMode(EchoPin , INPUT);   // Echo láb – jelet fogad visszaverődés után
}

void init_servo()
{
  servo.attach(4);  // A szervó motor jele a digitális D4 lábra van kötve
}

void setup()
{
  init_servo();   // szervó inicializálása (pl. távolságméréshez forgatható érzékelő)
  init_ultras();  // ultrahangos szenzor (távolságmérés) inicializálása
  init_GPIO();    // motorvezérlő és szenzor lábak beállítása
  Serial.begin(9600); // soros port megnyitása a debughoz, 9600 baud sebességgel
}

void loop(){
  i_servo();    // szervó működtetése (jelenleg csak delay, de bővíthető)
  trigpin();    // ultrahangos érzékelő lekérdezése (távolságmérés)
  tracking();   // vonalkövetés (fő logika)
}

void i_servo()
{
  delay(150); // jelenleg csak egy rövid késleltetés (lehet ide mozgatást, pásztázást tenni)
}

void trigpin()
{
  // trigger impulzus küldése
  digitalWrite(TrigPin , HIGH);
  delayMicroseconds(10);
  digitalWrite(TrigPin , LOW);

  // visszaverődött jel ideje
  duration = pulseIn(EchoPin , HIGH);

  // távolság kiszámítása cm-ben (hangsebesség alapján)
  distance = (duration / 2) / 28.5;

  // kiírás a soros monitorra
  Serial.print("Distance: ");
  Serial.print(distance); 
  Serial.print(" cm\t");
  Serial.print("\t");
}


void tracking()
{
  String senstr="";

  // A szenzorok értékei (0: fekete vonal alatt, 1: fehér háttér)
  int s0 = !digitalRead(sensor1); // bal szél
  int s1 = !digitalRead(sensor2); // bal közép
  int s2 = !digitalRead(sensor3); // közép
  int s3 = !digitalRead(sensor4); // jobb közép
  int s4 = !digitalRead(sensor5); // jobb szél

  // 5 bites értékké alakítva (pl. 01010)
  int sensorvalue = 32; // 0b100000: biztonsági alapérték, 6 bitből csak az 5 utolsó kell
  sensorvalue += s0*16 + s1*8 + s2*4 + s3*2 + s4;
  senstr = String(sensorvalue, BIN);       // binárisra konvertáljuk
  senstr = senstr.substring(1,6);          // csak az 5 szenzor releváns bitjét vesszük

  Serial.print(senstr);
  Serial.print("\t");

  // Vonalkövetés: karakterlánc alapján döntés
  // - A szenzorok szerint hol van a vonal
  // - Balra vagy jobbra kell-e kormányozni

  if (senstr == "10000" || senstr == "01000" || senstr == "11000") {
    Serial.println("Shift Left");
    sharpLeftTurn(LOW_SPEED, MID_SPEED);
    delay(DELAY_TIME);
    stop_bot();
  }

  if (senstr == "11100" || senstr == "10100") {
    Serial.println("Slight Shift Left");
    forward(0, HIGH_SPEED);  // csak jobb oldal megy
    delay(DELAY_TIME);
    stop_bot();
  }

  if (senstr == "01100" || senstr == "11110" || senstr == "10010" || senstr == "10110" || senstr == "11010") {
    Serial.println("Slight Left");
    forward(LOW_SPEED, MID_SPEED);
    delay(DELAY_TIME);
    stop_bot();
  }

  if (senstr == "01110" || senstr == "01010" || senstr == "00100" || senstr == "10001" ||
           senstr == "10101" || senstr == "10011" || senstr == "11101" || senstr == "10111" ||
           senstr == "11011" || senstr == "11001") {
    Serial.println("Forward");
    forward(MID_SPEED, MID_SPEED);
    delay(DELAY_TIME);
    stop_bot();
  }

  if (senstr == "00110" || senstr == "01111" || senstr == "01001" || senstr == "01011" || senstr == "01101") {
    Serial.println("Slight Right");
    forward(MID_SPEED, LOW_SPEED);
    delay(DELAY_TIME);
    stop_bot();
  }

  if (senstr == "00111" || senstr == "00101") {
    Serial.println("Slight Shift to Right");
    forward(HIGH_SPEED, 0); // csak bal oldal megy
    delay(DELAY_TIME);
    stop_bot();
  }

  if (senstr == "00001" || senstr == "00010" || senstr == "00011") {
    Serial.println("Shift to Right");
    sharpRightTurn(MID_SPEED, LOW_SPEED);
    delay(DELAY_TIME);
    stop_bot();
  }

  if (senstr == "00000") {
    // nem lát vonalat – valószínűleg elvesztette a pályát
    reverse(MID_SPEED);  // visszatolat
    delay(DELAY_TIME * 1.5);
    stop_bot();
  }

  if (senstr == "11111") {
    // valószínűleg kereszteződés vagy éles forduló
    Serial.println("Sharp Right U Turn");
    sharpRightTurn(MID_SPEED, MID_SPEED);
    delay(DELAY_TIME);
    stop_bot();
  }
}


#include "CarController.h"
#include "Arduino.h"

CarController::CarController() :
  FrontRightSpeed(6),
  FrontRightMotor1(29),
  FrontRightMotor2(28),
  FrontLeftMotor1(26),
  FrontLeftMotor2(27),
  FrontLeftSpeed(5),
  RearRightSpeed(8),
  RearRightMotor1(33),
  RearRightMotor2(32),
  RearLeftMotor1(31),
  RearLeftMotor2(30),
  RearLeftSpeed(7),
  FrontUltrasonicEcho(40),
  FrontUltrasonicTrig(41),
  RearUltrasonicEcho(42),
  RearUltrasonicTrig(43),
  AvoidanceEcho(34),
  AvoidanceTrig(35),
  linearSpeed(100),
  angularSpeed(100),
  maxLinearSpeed(200),
  maxAngularSpeed(200),
  minLinearSpeed(30),
  minAngularSpeed(30),
  FarLeft(A0),
  Left(A1),
  Middle(A2),
  Right(A3),
  FarRight(A4),
  temp(20),
  factor(sqrt(1 + temp / 273.15) / 60.368)
  {}


void CarController::init_GPIO()
{
  pinMode(FrontUltrasonicEcho, INPUT);
  pinMode(FrontUltrasonicTrig, OUTPUT);
  pinMode(RearUltrasonicEcho, INPUT);
  pinMode(RearUltrasonicTrig, OUTPUT);
  pinMode(FrontRightMotor1, OUTPUT);
  pinMode(FrontRightMotor2, OUTPUT);
  pinMode(FrontRightSpeed, OUTPUT);
  pinMode(FrontLeftMotor1, OUTPUT);
  pinMode(FrontLeftMotor2, OUTPUT);
  pinMode(FrontLeftSpeed, OUTPUT);
  pinMode(RearRightMotor1, OUTPUT);
  pinMode(RearRightMotor2, OUTPUT);
  pinMode(RearRightSpeed, OUTPUT);
  pinMode(RearLeftMotor1, OUTPUT);
  pinMode(RearLeftMotor2, OUTPUT);
  pinMode(RearLeftSpeed, OUTPUT);

  pinMode(FarLeft, INPUT);
  pinMode(Left, INPUT);
  pinMode(Middle, INPUT);
  pinMode(Right, INPUT);
  pinMode(FarRight, INPUT);
  
}

void CarController::setOneMotor(int speedpin, int pin1, int pin2, float speed)
{
  if (speed == 0) { // Motor stop
    digitalWrite(pin1, LOW);
    digitalWrite(pin2, LOW);
    analogWrite(speedpin, speed);
  } else if (speed > 0) { // Motor turn forward
    digitalWrite(pin1, HIGH);
    digitalWrite(pin2, LOW);
    analogWrite(speedpin, speed);
  } else { // Motor turn backward
    digitalWrite(pin1, LOW);
    digitalWrite(pin2, HIGH);
    analogWrite(speedpin, -speed);
  }
}

void CarController::setEachMotorSpeed(float speed1, float speed2, float speed3, float speed4)
{
  setOneMotor(FrontRightSpeed, FrontRightMotor1, FrontRightMotor2, speed1); // Front-right wheel turn
  setOneMotor(FrontLeftSpeed, FrontLeftMotor1, FrontLeftMotor2, -speed2); // Front-left wheel turn
  setOneMotor(RearRightSpeed, RearRightMotor1, RearRightMotor2, speed3); // Rear-right wheel turn
  setOneMotor(RearLeftSpeed, RearLeftMotor1, RearLeftMotor2, speed4); // Rear-left wheel turn
}

void CarController::mecanumRun(float xSpeed, float ySpeed, float aSpeed)
{
  float speed1 = ySpeed - xSpeed + aSpeed;
  float speed2 = ySpeed + xSpeed - aSpeed;
  float speed3 = ySpeed - xSpeed - aSpeed;
  float speed4 = ySpeed + xSpeed + aSpeed;

  setEachMotorSpeed(speed1, speed2, speed3, speed4);
}

void CarController::LineSensor(){
  bool a1 = 200 > analogRead(FarLeft);
  bool a2 = 200 > analogRead(Left);
  bool a3 = 200 > analogRead(Middle);
  bool a4 = 200 > analogRead(Right);
  bool a5 = 200 > analogRead(FarRight);
  
}


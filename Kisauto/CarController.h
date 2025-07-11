#ifndef CarController_h
#define CarController_h

class CarController {
  public:
    CarController();
    void init();
    int FarLeft;
    int Left;
    int Middle;
    int Right;
    int FarRight;

    int FrontRightSpeed;
    int FrontRightMotor1;
    int FrontRightMotor2;
    int FrontLeftMotor1;
    int FrontLeftMotor2;
    int FrontLeftSpeed;
    int ServoMotorPin;
    int RearRightSpeed;
    int RearRightMotor1;
    int RearRightMotor2;
    int RearLeftMotor1;
    int RearLeftMotor2;
    int RearLeftSpeed;
    int FrontUltrasonicEcho;
    int FrontUltrasonicTrig;
    int RearUltrasonicEcho;
    int RearUltrasonicTrig;
    int AvoidanceEcho;
    int AvoidanceTrig;
  
    float linearSpeed;
    float angularSpeed;
    float maxLinearSpeed;
    float maxAngularSpeed;
    float minLinearSpeed;
    float minAngularSpeed;
    float temp;
    float factor;
  
    void init_GPIO();
    void setOneMotor(int speedpin, int pin1, int pin2, float speed);
    void setEachMotorSpeed(float speed1, float speed2, float speed3, float speed4);
    void mecanumRun(float xSpeed, float ySpeed, float aSpeed);
    void LineSensor();
};

#endif

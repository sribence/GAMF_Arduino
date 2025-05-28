//////////////////////////////////////////////////////////
//                      Variables                       //
//////////////////////////////////////////////////////////
const int SERVO_PIN = 6;
const int PAIR_ONE_GREEN = 8;
const int PAIR_ONE_YELLOW = 9;
const int PAIR_ONE_RED = 10;
const int PAIR_TWO_GREEN = 11;
const int PAIR_TWO_YELLOW = 12;
const int PAIR_TWO_RED = 13;
const int STANDBY_TRIGGER = 2;
const int TRAIN_ON = 3;
const int TRAIN_OFF = 4;
const unsigned int GO_PERIOD = 5000;
const unsigned int WAIT_PERIOD = 1500;
const unsigned int STANDBY_BLINK_PERIOD = 500;
//////////////////////////////////////////////////////////

// State machine enum
enum StateMachine {
    PAIR_ONE_GO,
    PAIR_TWO_GO,
    PAIR_ONE_WAIT,
    PAIR_TWO_WAIT,
    STANDBY,
};

// Helper variables
unsigned int TimeCheckpoint;
bool IsStandbyButtonPressed = false;
StateMachine CurrentState = PAIR_ONE_GO;

// This function runs once after the Arduino is turned on
void setup()
{
    pinMode(SERVO_PIN, OUTPUT);         // Set `SERVO_PIN` pin to `OUTPUT`
    pinMode(PAIR_ONE_GREEN, OUTPUT);    // Set `PAIR_ONE_GREEN` pin to `OUTPUT`
    pinMode(PAIR_ONE_YELLOW, OUTPUT);   // Set `PAIR_ONE_YELLOW` pin to `OUTPUT`
    pinMode(PAIR_ONE_RED, OUTPUT);      // Set `PAIR_ONE_RED` pin to `OUTPUT`
    pinMode(PAIR_TWO_GREEN, OUTPUT);    // Set `PAIR_TWO_GREEN` pin to `OUTPUT`
    pinMode(PAIR_TWO_YELLOW, OUTPUT);   // Set `PAIR_TWO_YELLOW` pin to `OUTPUT`
    pinMode(PAIR_TWO_RED, OUTPUT);      // Set `PAIR_TWO_RED` pin to `OUTPUT`
    pinMode(STANDBY_TRIGGER, INPUT);    // Set `STANDBY` pin to `INPUT`
    pinMode(TRAIN_ON, INPUT);           // Set `TRAIN_ON` pin to `INPUT`
    pinMode(TRAIN_OFF, INPUT);          // Set `TRAIN_OFF` pin to `INPUT`

    Serial.begin(9600);                 // Connect to serial port, set baud rate at `9600`

    TimeCheckpoint = millis();          // Set an initial value of `TimeCheckpoint`
}

// This function repeats itself after the `setup()` has finished running
void loop()
{
    // State machine
    switch (CurrentState)
    {
        case PAIR_ONE_GO:
            PairOneGo();
            break;
        case PAIR_TWO_GO:
            PairTwoGo();
            break;
        case PAIR_ONE_WAIT:
            PairOneWait();
            break;
        case PAIR_TWO_WAIT:
            PairTwoWait();
            break;    
        case STANDBY:
            Standby();
            break;         
    }

    // If the program isn't in the `STANDBY` state and the button is pressed then change to that state
    if (digitalRead(STANDBY) == HIGH && !IsStandbyButtonPressed && CurrentState != STANDBY) 
    {
        IsStandbyButtonPressed = true;
        CurrentState = STANDBY;
    } 

    // If the program is in the `STANDBY` state and the button is pressed then change to the default state (`PAIR_ONE_GO`)
    else if (digitalRead(STANDBY) == HIGH && !IsStandbyButtonPressed)
    {
        IsStandbyButtonPressed = true;
        CurrentState = PAIR_ONE_GO;
    }

    // Reset the `IsStandbyButtonPressed` helper variable
    else
    {
        IsStandbyButtonPressed = false;
    }

    // If the train is coming button pressed then lower the barrier
    if (digitalRead(TRAIN_ON) == HIGH)
    {
        SetBarrier("down");
    }

    // If the train has passed button pressed then raise the barrier
    else if (digitalRead(TRAIN_OFF) == HIGH)
    {
        SetBarrier("up");
    }
}

// Function to call when the program is in the `PAIR_ONE_GO` state
void PairOneGo()
{
    // Set the lights
    ManagePairOne("green");
    ManagePairTwo("red");

    // After a fix amount of time enter to the next state
    if (millis() - TimeCheckpoint >= GO_PERIOD)
    {
        TimeCheckpoint = millis();
        CurrentState = PAIR_TWO_WAIT;
    }
}

// Function to call when the program is in the `PAIR_TWO_GO` state
void PairTwoGo()
{
    // Set the lights
    ManagePairOne("red");
    ManagePairTwo("green");

    // After a fix amount of time enter to the next state
    if (millis() - TimeCheckpoint >= GO_PERIOD)
    {
        TimeCheckpoint = millis();
        CurrentState = PAIR_ONE_WAIT;
    }
}

// Function to call when the program is in the `PAIR_ONE_WAIT` state
void PairOneWait()
{
    // Set the lights
    ManagePairOne("red-yellow");
    ManagePairTwo("yellow");

    // After a fix amount of time enter to the next state
    if (millis() - TimeCheckpoint >= WAIT_PERIOD)
    {
        TimeCheckpoint = millis();
        CurrentState = PAIR_ONE_GO;
    }
}

// Function to call when the program is in the `PAIR_TWO_WAIT` state
void PairTwoWait()
{
    // Set the lights
    ManagePairOne("yellow");
    ManagePairTwo("red-yellow");

    // After a fix amount of time enter to the next state
    if (millis() - TimeCheckpoint >= WAIT_PERIOD)
    {
        TimeCheckpoint = millis();
        CurrentState = PAIR_TWO_GO;
    }
}

// Function to call when the program is in the `STANDBY` state
void Standby()
{
    // Turn on yellow
    if (millis() - TimeCheckpoint < STANDBY_BLINK_PERIOD)
    {
        ManagePairOne("yellow");
        ManagePairTwo("yellow");
    }

    // Turn off yellow
    else if (millis() - TimeCheckpoint < STANDBY_BLINK_PERIOD * 2)
    {
        ManagePairOne("off");
        ManagePairTwo("off");
    }

    // Reset time
    else
    {
        TimeCheckpoint = millis();
    }
}

//////////////////////////////////////////////////////////
//                   Helper Functions                   //
//////////////////////////////////////////////////////////

// This function controls the barrier
// Usage: SetBarrier("up");
//        SetBarrier("down");
void SetBarrier(String state)
{
    // Set the degree based on the state and calculate the pulse with
    int angle;
    if (state == "up") angle = 160;
    else if (state == "down") angle = 70;
    int pulsewidth = (angle * 11) + 500;                  // Calculate pulse with based on the degree (range: 500-2480)

    // Send the signal to the servo motor
    for (int i = 0; i < 50; i++)
    {
        digitalWrite(SERVO_PIN, HIGH);                    // Set the level of servo pin as `HIGH`
        delayMicroseconds(pulsewidth);                    // Delay microsecond of pulse width
        digitalWrite(SERVO_PIN, LOW);                     // Set the level of servo pin as `LOW`
        delay(20 - pulsewidth / 1000);
    }
}

// This function controls a pair of traffic lights
// Usage: ManagePairOne("red");
//        ManagePairOne("yellow");
//        ManagePairOne("green");
//        ManagePairOne("red-yellow");
//        ManagePairOne("off");
void ManagePairOne(String state)
{
    // Variables to change based on the required state of the lights
    auto IsGreenEnabled = HIGH;
    auto IsYellowEnabled = HIGH;
    auto IsRedEnabled = HIGH;

    // Set in case of state `red`
    if (state == "red")
    {
        IsGreenEnabled = LOW;
        IsYellowEnabled = LOW;
        IsRedEnabled = HIGH;
    }

    // Set in case of state `yellow`
    else if (state == "yellow")
    {
        IsGreenEnabled = LOW;
        IsYellowEnabled = HIGH;
        IsRedEnabled = LOW;
    }

    // Set in case of state `green`
    else if (state == "green")
    {
        IsGreenEnabled = HIGH;
        IsYellowEnabled = LOW;
        IsRedEnabled = LOW;
    }

    // Set in case of state `red-yellow`
    else if (state == "red-yellow")
    {
        IsGreenEnabled = LOW;
        IsYellowEnabled = HIGH;
        IsRedEnabled = HIGH;
    }

    // Set in case of state `off`
    else if (state == "off")
    {
        IsGreenEnabled = LOW;
        IsYellowEnabled = LOW;
        IsRedEnabled = LOW;
    }

    // Turn on all lights in any other case
    else
    {
        IsGreenEnabled = HIGH;
        IsYellowEnabled = HIGH;
        IsRedEnabled = HIGH;
    }

    // Write the date to the lights
    digitalWrite(PAIR_ONE_GREEN, IsGreenEnabled);
    digitalWrite(PAIR_ONE_YELLOW, IsYellowEnabled);
    digitalWrite(PAIR_ONE_RED, IsRedEnabled);
}

// This function controls a pair of traffic lights
// Usage: ManagePairTow("red");
//        ManagePairTow("yellow");
//        ManagePairTow("green");
//        ManagePairTow("red-yellow");
//        ManagePairTow("off");
void ManagePairTwo(String state)
{
    // Variables to change based on the required state of the lights
    auto IsGreenEnabled = HIGH;
    auto IsYellowEnabled = HIGH;
    auto IsRedEnabled = HIGH;

    // Set in case of state `red`
    if (state == "red")
    {
        IsGreenEnabled = LOW;
        IsYellowEnabled = LOW;
        IsRedEnabled = HIGH;
    }

    // Set in case of state `yellow`
    else if (state == "yellow")
    {
        IsGreenEnabled = LOW;
        IsYellowEnabled = HIGH;
        IsRedEnabled = LOW;
    }

    // Set in case of state `green`
    else if (state == "green")
    {
        IsGreenEnabled = HIGH;
        IsYellowEnabled = LOW;
        IsRedEnabled = LOW;
    }

    // Set in case of state `red-yellow`
    else if (state == "red-yellow")
    {
        IsGreenEnabled = LOW;
        IsYellowEnabled = HIGH;
        IsRedEnabled = HIGH;
    }

    // Set in case of state `off`
    else if (state == "off")
    {
        IsGreenEnabled = LOW;
        IsYellowEnabled = LOW;
        IsRedEnabled = LOW;
    }

    // Turn on all lights in any other case
    else
    {
        IsGreenEnabled = HIGH;
        IsYellowEnabled = HIGH;
        IsRedEnabled = HIGH;
    }

    // Write the date to the lights
    digitalWrite(PAIR_TWO_GREEN, IsGreenEnabled);
    digitalWrite(PAIR_TWO_YELLOW, IsYellowEnabled);
    digitalWrite(PAIR_TWO_RED, IsRedEnabled);
}

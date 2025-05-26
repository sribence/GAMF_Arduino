// Includes
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

//////////////////////////////////////////////////////////
//                      Variables                       //
//////////////////////////////////////////////////////////
const int BUZZER = 3;
const int FLAME_SENSOR = 2;
const int MOTION_SENSOR = 8;
const int SERVO = 13;
const int LED_R = 9;
const int LED_G = 11;
const int LED_B = 10;
const int JOYSTICK_X = A0;
const int JOYSTICK_Y = A1;
const int JOYSTICK_BTN = 4;
const float BRIGHTNESS = 0.1;
const int JOYSTICK_DEADZONE_RADIUS = 150;
const String CORRECT_PASSWORD = "ABC9";      // Password only can be 4 characters and only contains the uppercase English alphabet and numbers
//////////////////////////////////////////////////////////

// State machine enum
enum StateMachine {
    UNARMED,
    ARMED,
    ALARMED,
};

// Helper variables
bool IsBuzzerOn = false;
bool IsMovementDetected = false;
bool IsFlameDetected = false;
int x, y;
bool IsJoyStickPressed = false;
bool PrevIsJoyStickPressed = false;
Adafruit_SSD1306 display(128, 32, &Wire, -1);
bool IsJoyStickMoved = false;
int PasswordPointer = 0;
int Password[4] = { 0, 0, 0, 0 };
const String PasswordChars = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
int LimitT = 512 + JOYSTICK_DEADZONE_RADIUS;
int LimitB = 512 - JOYSTICK_DEADZONE_RADIUS;
StateMachine CurrentState = UNARMED;
bool IsDoorSet = false;

// This function runs once after the Arduino is turned on
void setup()
{
    // Start serial connection at 9600 baud rate
    Serial.begin(9600);

    // Initialize display, if failed then stop the code
    if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) 
    {
        Serial.println(F("SSD1306 allocation failed"));
        while (true); // Don't proceed, loop forever
    }

    // Test display & wait a bit
    display.display();
    delay(2000);

    // Set default values (turn off the LED and clear the display)
    display.clearDisplay();
    SetLed(0, 0, 0);

    pinMode(BUZZER, OUTPUT);            // Set `BUZZER` pin to `OUTPUT`  
    pinMode(LED_R, OUTPUT);             // Set `LED_R` pin to `OUTPUT`
    pinMode(LED_G, OUTPUT);             // Set `LED_G` pin to `OUTPUT`
    pinMode(LED_B, OUTPUT);             // Set `LED_B` pin to `OUTPUT`
    pinMode(SERVO, OUTPUT);             // Set `SERVO` pin to `OUTPUT`
    pinMode(MOTION_SENSOR, INPUT);      // Set `MOTION_SENSOR` pin to `INPUT`
    pinMode(FLAME_SENSOR, INPUT);       // Set `FLAME_SENSOR` pin to `INPUT`
    pinMode(JOYSTICK_BTN, INPUT);       // Set `JOYSTICK_BTN` pin to `INPUT`
}

// This function repeats itself after the `setup()` has finished running
void loop()
{
    // Detect inputs
    DetectMovement();
    DetectFlame();
    UpdateJoystick();
    ReadPass();

    // Update display
    PrintPass();

    // State machine
    switch (CurrentState)
    {
        case UNARMED:
            Unarmed();
            break;
        case ARMED:
            Armed();
            break;
        case ALARMED:
            Alarmed();
            break;
    }

    // If the joystick button is released then reset the `PrevIsJoyStickPressed` variable
    if (!IsJoyStickPressed)
    {
        PrevIsJoyStickPressed = false;
    }

    // If flame detected enter the `ALARMED` state instantly
    if (IsFlameDetected)
    {
        CurrentState = ALARMED;
        IsDoorSet = false;
    }

    // Play the buzzer
    PlayBuzzer();

    // Reset the buzzer controller variable (it will be re-enabled anyway)
    IsBuzzerOn = false;
}

// This function will be called in the `UNARMED` state
void Unarmed()
{
    // If the door is not set then open it
    if (!IsDoorSet)
    {
        ManageDoor("open");
        IsDoorSet = true;
    }

    // If movement detected then turn on the light, otherwise turn it off
    if (IsMovementDetected)
    {
        SetLed(255, 255, 255);
    }
    else 
    {
        SetLed(0, 0, 0);
    }

    // If the joystick button pressed (and it wasn't before) then check password
    if (IsJoyStickPressed && !PrevIsJoyStickPressed)
    {
        // Convert password into a string from an array of indexes
        String pass = "";
        for (int i = 0; i < 4; i++) pass += PasswordChars[Password[i]];

        // Check whether the password is correct, if yes then change the state to `ARMED`
        if (pass == CORRECT_PASSWORD)
        {
            CurrentState = ARMED;
            IsDoorSet = false;
        }

        // Reset password
        for (int i = 0; i < 4; i++) Password[i] = 0;
    }
}

// This function will be called in the `ARMED` state
void Armed()
{
    // If the door is not set then close it
    if (!IsDoorSet)
    {
        ManageDoor("close");
        IsDoorSet = true;
    }

    // Change the LED to orange
    SetLed(255, 255, 0);

    // If the joystick button pressed (and it wasn't before) then check password
    if (IsJoyStickPressed && !PrevIsJoyStickPressed)
    {
        // Convert password into a string from an array of indexes
        String pass = "";
        for (int i = 0; i < 4; i++) pass += PasswordChars[Password[i]];
        
        // Check whether the password is correct, if yes then change the state to `UNARMED`
        if (pass == CORRECT_PASSWORD)
        {
            CurrentState = UNARMED;
            IsDoorSet = false;
        }
        
        // Reset password
        for (int i = 0; i < 4; i++) Password[i] = 0;
    }

    // If movement detected then change state to `ALARMED`
    if (IsMovementDetected)
    {
        CurrentState = ALARMED;
        IsDoorSet = false;
    }
}

// This function will be called in the `ALARMED` state
void Alarmed()
{
    // If the door is not set then close it
    if (!IsDoorSet)
    {
        ManageDoor("close");
        IsDoorSet = true;
    }

    // If the joystick button pressed (and it wasn't before) then check password
    if (IsJoyStickPressed && !PrevIsJoyStickPressed)
    {
        // Convert password into a string from an array of indexes
        String pass = "";
        for (int i = 0; i < 4; i++) pass += PasswordChars[Password[i]];
        
        // Check whether the password is correct, if yes then change the state to `UNARMED`
        if (pass == CORRECT_PASSWORD)
        {
            CurrentState = UNARMED;
            IsDoorSet = false;
        }
        
        // Reset password
        for (int i = 0; i < 4; i++) Password[i] = 0;
    }

    // Turn the light to red and start the buzzer
    SetLed(255, 0, 0);
    IsBuzzerOn = true;
}

//////////////////////////////////////////////////////////
//                   Helper Functions                   //
//////////////////////////////////////////////////////////

// This function lets you set the LED's RGB value
// Usage: SetLed(255, 255, 255);
//        SetLed(0, 0, 0); -> To turn it off
void SetLed(int red, int green, int blue)
{
    // Setting the output values (inverted because of the schematic) and also calculate the brightness
    analogWrite(LED_R, 255 - (red * BRIGHTNESS));       // red
    analogWrite(LED_G, 255 - (green * BRIGHTNESS));     // green
    analogWrite(LED_B, 255 - (blue * BRIGHTNESS));      // blue

}

// This function lets you play the buzzer
// Note:  Use the IsBuzzerOn to change the state of the buzzer
// Usage: PlayBuzzer();
void PlayBuzzer()
{
    // If the buzzer is turned off then exit the function
    if (!IsBuzzerOn) return;

    // Buzz the buzzer
    digitalWrite(BUZZER,HIGH);
    delay(1);
    digitalWrite(BUZZER,LOW);
    delay(1);
}

// This function checks the RIP sensor whether is there movement or not
// Usage: DetectMovement();
void DetectMovement()
{
    IsMovementDetected = digitalRead(MOTION_SENSOR) == 1;
}

// This function checks the flame sensor whether is there flames around or not
// Usage: DetectFlame();
void DetectFlame()
{
    IsFlameDetected = digitalRead(FLAME_SENSOR);
}

// This function controls the door
// Usage: ManageDoor("open");
//        ManageDoor("close");
void ManageDoor(String state)
{
    int angle;
    if (state == "open") angle = 160;
    else if (state == "close") angle = 70;
    int pulsewidth = (angle * 11) + 500;                  // Calculate pulse with based on the degree

    Serial.println(angle);

    for (int i = 0; i < 50; i++)
    {
        digitalWrite(SERVO, HIGH);                    // Set the level of servo pin as “high”
        delayMicroseconds(pulsewidth);                // Delay microsecond of pulse width
        digitalWrite(SERVO, LOW);                     // Set the level of servo pin as “low”
        delay(20 - pulsewidth / 1000);
    }
}

// This function updates the coordinates and the button
// Usage: UpdateJoystick();
void UpdateJoystick()
{
    x = analogRead(JOYSTICK_X);
    y = analogRead(JOYSTICK_Y);
    IsJoyStickPressed = digitalRead(JOYSTICK_BTN) == HIGH;
}

// This function prints text to the OLED display
// Useage: PrintText("Hello world!");
void PrintText(String msg)
{
    display.clearDisplay();                 // Clear the display

    display.setTextSize(2);                 // Normal 1:1 pixel scale
    display.setTextColor(SSD1306_WHITE);    // Draw white text
    display.setCursor(0,0);                 // Start at top-left corner
    display.println(msg);                   // Add the message to the buffer

    display.display();                      // Write the buffer to the display
}

// This function prints the password to the OLED display
// Usage: PrintPass();
void PrintPass()
{
    String passwd = "";

    for (int i = 0; i < 4; i++)
    {
        passwd += PasswordChars[Password[i]];
    }
    PrintText("Password:\n" + passwd);
}

// This function will read the password through joystick input
// Usage: ReadPass();
void ReadPass()
{
    // Save the move
    String JoyStickMove = "";

    // If joystick moved up and isn't checked before then register the movement
    if (IsJoyUp() && !IsJoyStickMoved)
    {
        JoyStickMove = "up";
        IsJoyStickMoved = true;
        ChangeCurrentPassChar(1);       // Change the selecter char in the password
    }

    // If joystick moved down and isn't checked before then register the movement
    else if (IsJoyDown() && !IsJoyStickMoved)
    {
        JoyStickMove = "down";
        IsJoyStickMoved = true;
        ChangeCurrentPassChar(-1);      // Change the selecter char in the password
    }

    // If joystick moved left and isn't checked before then register the movement
    else if (IsJoyLeft() && !IsJoyStickMoved)
    {
        JoyStickMove = "left";
        IsJoyStickMoved = true;
        MovePassPointer(-1);            // Change the selected char in the password
    }

    // If joystick moved right and isn't checked before then register the movement
    else if (IsJoyRight() && !IsJoyStickMoved)
    {
        JoyStickMove = "right";
        IsJoyStickMoved = true;
        MovePassPointer(1);             // Change the selected char in the password
    }

    // If joystick is in the deadzone then let registering possible again
    else if (IsJoyInDeadzone() && IsJoyStickMoved)
    {
        IsJoyStickMoved = false;
    }
}

// Checks if the joystick is moved up
bool IsJoyUp()
{
    bool ConditionX = x < LimitT && x > LimitB;     // Is in deadzone of x
    bool ConditionY = y > LimitT;                   // Is over the top limit of y

    if (ConditionX && ConditionY) return true;
    return false;
}

// Checks if the joystick is moved down
bool IsJoyDown()
{
    bool ConditionX = x < LimitT && x > LimitB;     // Is in deadzone of x
    bool ConditionY = y < LimitB;                   // Is under the bottom limit of y

    if (ConditionX && ConditionY) return true;
    return false;
}

// Checks if the joystick is moved left
bool IsJoyLeft()
{
    bool ConditionX = x < LimitB;                   // Is under the bottom limit of x
    bool ConditionY = y < LimitT && y > LimitB;     // Is in deadzone of y

    if (ConditionX && ConditionY) return true;
    return false;
}

// Checks if the joystick is moved right
bool IsJoyRight()
{
    bool ConditionX = x > LimitT;                   // Is over the top limit of x
    bool ConditionY = y < LimitT && y > LimitB;     // Is in deadzone of y

    if (ConditionX && ConditionY) return true;
    return false;
}

// Checks if the joystick is in the deadzone
bool IsJoyInDeadzone()
{
    bool ConditionX = x < LimitT && x > LimitB;     // Is in deadzone of x
    bool ConditionY = y < LimitT && y > LimitB;     // Is in deadzone of y

    if (ConditionX && ConditionY) return true;
    return false;
}

// Change the selected password character
void MovePassPointer(int value)
{
    PasswordPointer += value;
    if (PasswordPointer >= 4) PasswordPointer = 0;
    else if (PasswordPointer < 0) PasswordPointer = 3;
}

// Change the selecter password character's value
void ChangeCurrentPassChar(int value)
{
    Password[PasswordPointer] = (Password[PasswordPointer] + value + PasswordChars.length()) % PasswordChars.length();
}

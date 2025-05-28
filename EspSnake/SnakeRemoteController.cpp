#include <esp_now.h>
#include <WiFi.h>

// 98:CD:AC:63:9A:F0
uint8_t TargetAddress[] = {0x98, 0xCD, 0xAC, 0x63, 0x9A, 0xF0};

// Structure example to send data

// Must match the receiver structure

typedef struct struct_message 
{
    char a[32];
} struct_message;

// Create a struct_message called myData
struct_message myData;

esp_now_peer_info_t peerInfo;

const int JOYSTICK_X   = 33;
const int JOYSTICK_Y   = 34;
const int JOYSTICK_BTN = 26;

const int JOYSTICK_CENTER          = -150;
const int JOYSTICK_RANGE_MAX       = 4096;
const int JOYSTICK_DEADZONE_RADIUS = 300;

int  x         = 0;
int  y         = 0;
bool IsPressed = false;
bool IsPressedPrev = false;

String Direction = "none";
String PrevDirection = "none";
String DominantAxis = "none";

void setup() 
{
    pinMode(JOYSTICK_X,   INPUT);
    pinMode(JOYSTICK_Y,   INPUT);
    pinMode(JOYSTICK_BTN, INPUT);

    Serial.begin(9600);

    // Set device as a Wi-Fi Station
    WiFi.mode(WIFI_STA);

    // Init ESP-NOW
    if (esp_now_init() != ESP_OK) 
    {
        Serial.println("Error initializing ESP-NOW");
        return;
    }

    // Once ESPNow is successfully Init, we will register for Send CB to
    // get the status of Transmitted packet
    esp_now_register_send_cb(OnDataSent);

    // Register peer
    memcpy(peerInfo.peer_addr, TargetAddress, 6);
    peerInfo.channel = 0;  
    peerInfo.encrypt = false;

    // Add peer        
    if (esp_now_add_peer(&peerInfo) != ESP_OK)
    {
        Serial.println("Failed to add peer");
        return;
    }

}

void loop() 
{
    ReadData();
    DetermineDirection();

    Serial.print("(");
    Serial.print(x);
    Serial.print(", ");
    Serial.print(y);
    Serial.print(", ");
    Serial.print(IsPressed);
    Serial.print(") -> ");
    Serial.println(Direction);

    if (IsPressed && IsPressed != IsPressedPrev)
    {
        IsPressedPrev = IsPressed;

        // Set values to send
        strcpy(myData.a, "button");        

        // Send message via ESP-NOW
        esp_err_t result = esp_now_send(TargetAddress, (uint8_t *) &myData, sizeof(myData));        

        if (result == ESP_OK) 
        {
            Serial.println("Sent with success");
        }
        else 
        {
            Serial.println("Error sending the data");
        }
    }

    if (PrevDirection != Direction)
    {

        PrevDirection = Direction;
        
        // Set values to send
        strcpy(myData.a, Direction.c_str());        

        // Send message via ESP-NOW
        esp_err_t result = esp_now_send(TargetAddress, (uint8_t *) &myData, sizeof(myData));        

        if (result == ESP_OK) 
        {
            Serial.println("Sent with success");
        }
        else 
        {
            Serial.println("Error sending the data");
        }
    }

    if (IsPressed != IsPressedPrev)
    {
        IsPressedPrev = IsPressed;
    }
}

void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) 
{
//   Serial.print("\r\nLast Packet Send Status:\t");
//   Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
}

void ReadData()
{
    x = analogRead(JOYSTICK_X) - (JOYSTICK_RANGE_MAX / 2);
    y = analogRead(JOYSTICK_Y) - (JOYSTICK_RANGE_MAX / 2);
    IsPressed = digitalRead(JOYSTICK_BTN) == HIGH;
}

// Directions:
// "none"  -> In the deadzone
// "up"    -> Positive y axis is the dominant
// "down"  -> Negative y axis is the dominant
// "right" -> Positive x axis is the dominant
// "left"  -> Negative x axis is the dominant
void DetermineDirection()
{
    if (IsInDeadzone())
    {
        Direction = "none";
        return;
    }

    int DominantAxisDirectionX = GetDominantAxisDirection("x");
    int DominantAxisDirectionY = GetDominantAxisDirection("y");

    GetDominantAxis();

    if (DominantAxis == "none") Direction = "none";

    if (DominantAxis == "y" && DominantAxisDirectionY > 0)      Direction = "up";
    else if (DominantAxis == "y" && DominantAxisDirectionY < 0) Direction = "down";
    else if (DominantAxis == "x" && DominantAxisDirectionX > 0) Direction = "right";
    else if (DominantAxis == "x" && DominantAxisDirectionX < 0) Direction = "left";
}

bool IsInDeadzone()
{
    bool ConditionX = x < JOYSTICK_CENTER + JOYSTICK_DEADZONE_RADIUS && x > JOYSTICK_CENTER - JOYSTICK_DEADZONE_RADIUS;
    bool ConditionY = y < JOYSTICK_CENTER + JOYSTICK_DEADZONE_RADIUS && y > JOYSTICK_CENTER - JOYSTICK_DEADZONE_RADIUS;

    if (ConditionX && ConditionY)
        return true;
    return false;
}

int GetDominantAxisDirection(String Axis)
{
    if (Axis == "x")
    {
        if (x > JOYSTICK_CENTER + JOYSTICK_DEADZONE_RADIUS) 
            return 1;
        return -1;
    }
    else if (Axis == "y")
    {
        if (y > JOYSTICK_CENTER + JOYSTICK_DEADZONE_RADIUS) 
            return 1;
        return -1;
    }

    return 0;
}

void GetDominantAxis()
{
    int AbsX = abs(x);
    int AbsY = abs(y);

    if (AbsX == AbsY) 
    {
        return;
    }

    if (AbsX > AbsY)
    {
        DominantAxis = "x";
        return;
    } 

    DominantAxis = "y";
}

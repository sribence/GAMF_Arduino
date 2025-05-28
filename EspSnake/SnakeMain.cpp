// MAC address of device: 98:CD:AC:63:9A:F0

#include <Wire.h>
#include <Adafruit_GFX.h>         // Telepíteni kell
#include <Adafruit_LEDBackpack.h> // Telepíteni kell
#include <esp_now.h>
#include <WiFi.h>

// Structure example to receive data
// Must match the sender structure
typedef struct struct_message 
{
    char a[32];
} struct_message;

// Declare the function
void OnDataRecv(const esp_now_recv_info_t *recv_info, const uint8_t *data, int len);

// Create a struct_message called myData
struct_message myData;

Adafruit_8x8matrix matrix[] = {Adafruit_8x8matrix(), Adafruit_8x8matrix(), Adafruit_8x8matrix(), Adafruit_8x8matrix(), Adafruit_8x8matrix(), Adafruit_8x8matrix(), Adafruit_8x8matrix(), Adafruit_8x8matrix()};

const int JOYSTICK_X = 33;
const int JOYSTICK_Y = 35;
const int JOYSTICK_BTN = 32;
const int BUZZER = 26;

int snakeX1[64];
int snakeY1[64];
int snakeX2[64];
int snakeY2[64];
bool playField[32][16];
int length = 6; // Kígyó hossza
int dir1 = 0;    // 0: jobbra, 1: le, 2: balra, 3: fel
int dir2 = 2;    // 0: jobbra, 1: le, 2: balra, 3: fel

const int JOYSTICK_CENTER          = -150;
const int JOYSTICK_RANGE_MAX       = 4096;
const int JOYSTICK_DEADZONE_RADIUS = 300;
int x, y;
bool IsPressed = false;
bool IsPressedPrev = false;
String DominantAxis = "none";

// A játék adott állapota
// standby -> várakozás a játékosora
// game    -> a tényleges játék
// p1_w    -> az egyes játékos győz
// p2_w    -> az egyes játékos győz
// draw    -> döntetlen
String GameState = "standby";

bool IsP1Ready = false;
bool IsP2Ready = false;

unsigned int Ido;

void setup() 
{
    Serial.begin(9600);

    pinMode(JOYSTICK_X, INPUT);
    pinMode(JOYSTICK_Y, INPUT);
    pinMode(JOYSTICK_BTN, INPUT);

    // Set device as a Wi-Fi Station
    WiFi.mode(WIFI_STA);

    // Init ESP-NOW
    if (esp_now_init() != ESP_OK) {
        Serial.println("Error initializing ESP-NOW");
        return;
    }

    // Once ESPNow is successfully Init, we will register for recv CB to
    // get recv packer info
    esp_now_register_recv_cb(OnDataRecv);

    // Cserélgetsd a címeket addig amíg a megfelelő szám a megfelelő helyen nem lesz
    matrix[0].begin(0x73);
    matrix[1].begin(0x72);
    matrix[2].begin(0x71);
    matrix[3].begin(0x74);
    matrix[4].begin(0x77);
    matrix[5].begin(0x70);
    matrix[6].begin(0x75);
    matrix[7].begin(0x76);

    // Módosítsd az orientációt hogy megfelelő legyen
    matrix[0].setRotation(3);
    matrix[1].setRotation(3);
    matrix[2].setRotation(3);
    matrix[3].setRotation(3);
    matrix[4].setRotation(1);
    matrix[5].setRotation(1);
    matrix[6].setRotation(1);
    matrix[7].setRotation(1);

    clearScreen();

    Ido = millis();

    snakeX1[5] = 1;
    snakeX1[4] = 2;
    snakeX1[3] = 3;
    snakeX1[2] = 4;
    snakeX1[1] = 5;
    snakeX1[0] = 6;

    snakeY1[0] = 3;
    snakeY1[1] = 3;
    snakeY1[2] = 3;
    snakeY1[3] = 3;
    snakeY1[4] = 3;
    snakeY1[5] = 3;

    snakeX2[5] = 30;
    snakeX2[4] = 29;
    snakeX2[3] = 28;
    snakeX2[2] = 27;
    snakeX2[1] = 26;
    snakeX2[0] = 25;

    snakeY2[0] = 12;
    snakeY2[1] = 12;
    snakeY2[2] = 12;
    snakeY2[3] = 12;
    snakeY2[4] = 12;
    snakeY2[5] = 12;
}

void loop() 
{
    JoystickBemenet();
    DetermineDirection();

    if (GameState == "standby")
    {
        bool tempP1Ready = false;
        bool tempP2Ready = false;
        bool temp[32][16] = {
            {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
            {1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0},
            {1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0},
            {1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0},
            {1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0},
            {0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
            {0,1,0,0,0,0,0,1,0,0,0,0,0,0,0,0},
            {1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
            {1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0},
            {1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0},
            {1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0},
            {1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0},
            {0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
            {0,1,0,0,0,1,1,1,0,0,0,0,0,0,0,0},
            {1,0,0,0,1,0,0,1,0,0,0,0,0,0,0,0},
            {1,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0},
            {0,1,1,0,0,0,0,1,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        };

        if (IsP2Ready)
        {
            tempP2Ready = true;
            for (int i = 16; i < 32; i++)
            {
                for (int j = 0; j < 16; j++)
                {
                    temp[i][j] = !temp[i][j];
                }   
            }
        }

        if (IsP1Ready)
        {
            tempP1Ready = true;
            for (int i = 0; i < 16; i++)
            {
                for (int j = 0; j < 16; j++)
                {
                    temp[i][j] = !temp[i][j];
                }   
            }
        }

        for (int i = 0; i < 32; ++i) {
            for (int j = 0; j < 16; ++j) {
                playField[i][j] = temp[i][j];
            }
        }

        updateScreen();

        if (tempP1Ready && tempP2Ready)
        {
            IsP1Ready = false;
            IsP2Ready = false;
            GameState = "game";
            dir1 = 0;
            dir2 = 2;
            delay(1500);
        }
    }
    else if (GameState == "game")
    {
        if (millis() - Ido >= 100)
        {
            moveSnake();
            updateScreen();
            Ido = millis();
        }
    }
    else if (GameState == "draw")
    {
        bool temp[32][16] = {
            {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
            {1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0},
            {1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0},
            {1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0},
            {1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0},
            {0,1,0,0,0,0,1,0,0,0,0,0,0,0,0,0},
            {0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
            {1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0},
            {1,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0},
            {1,0,0,1,0,1,0,0,0,0,0,0,0,0,0,0},
            {1,0,0,1,0,0,1,0,0,0,0,0,0,0,0,0},
            {0,1,1,0,0,0,0,1,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0},
            {0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0},
            {1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0},
            {1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0},
            {0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
            {1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0},
            {0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0},
            {0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0},
            {0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0},
            {1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        };        

        for (int i = 0; i < 32; ++i) {
            for (int j = 0; j < 16; ++j) {
                playField[i][j] = temp[i][j];
            }
        }

        updateScreen();

        delay(2000);
        GameState = "standby";
    }
    else if (GameState == "p1_w")
    {
        bool temp[32][16] = {
            {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
            {1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0},
            {1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0},
            {1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0},
            {1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0},
            {0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
            {0,1,0,0,0,0,0,1,0,0,0,0,0,0,0,0},
            {1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
            {1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0},
            {0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0},
            {0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0},
            {0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0},
            {1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
            {1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0},
            {1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0},
            {1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
            {1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0},
            {0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
            {0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0},
            {0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0},
            {1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        };

        for (int i = 0; i < 32; ++i) {
            for (int j = 0; j < 16; ++j) {
                playField[i][j] = temp[i][j];
            }
        }

        updateScreen();
        tone(BUZZER, 1000, 300);
        delay(2000);
        GameState = "standby";
    }
    else if (GameState == "p2_w")
    {
        bool temp[32][16] = {
            {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
            {1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0},
            {1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0},
            {1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0},
            {1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0},
            {0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
            {0,1,0,0,0,1,1,1,0,0,0,0,0,0,0,0},
            {1,0,0,0,1,0,0,1,0,0,0,0,0,0,0,0},
            {1,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0},
            {0,1,1,0,0,0,0,1,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
            {1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0},
            {0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0},
            {0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0},
            {0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0},
            {1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
            {1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0},
            {1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0},
            {1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
            {1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0},
            {0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
            {0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0},
            {0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0},
            {1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        };

        for (int i = 0; i < 32; ++i) {
            for (int j = 0; j < 16; ++j) {
                playField[i][j] = temp[i][j];
            }
        }

        updateScreen();
        tone(BUZZER, 1000, 300);
        delay(2000);
        GameState = "standby";
    }
}

void moveSnake() 
{
    for (int i = length - 1; i > 0; i--) 
    {
        snakeX1[i] = snakeX1[i - 1];
        snakeY1[i] = snakeY1[i - 1];
        snakeX2[i] = snakeX2[i - 1];
        snakeY2[i] = snakeY2[i - 1];
    }

    if (dir1 == 0) snakeX1[0]++;
    if (dir1 == 1) snakeY1[0]++;
    if (dir1 == 2) snakeX1[0]--;
    if (dir1 == 3) snakeY1[0]--;

    if (dir2 == 0) snakeX2[0]++;
    if (dir2 == 1) snakeY2[0]++;
    if (dir2 == 2) snakeX2[0]--;
    if (dir2 == 3) snakeY2[0]--;

    // egyszerű ütközés
    if (snakeX1[0] < 0 || snakeX1[0] > 31 || snakeY1[0] < 0 || snakeY1[0] > 15) 
    {
        length = 6;
        snakeX1[0] = 6; snakeY1[0] = 3;
        snakeX1[1] = 5; snakeY1[1] = 3;
        snakeX1[2] = 4; snakeY1[2] = 3;
        snakeX1[3] = 3; snakeY1[3] = 3;
        snakeX1[4] = 2; snakeY1[4] = 3;
        snakeX1[5] = 1; snakeY1[5] = 3;
        dir1 = 0;
        GameState = "p2_w";
        ResetGame();
        return;
    }
    
    // Snake2 üttközés
    if (snakeX2[0] < 0 || snakeX2[0] > 31 || snakeY2[0] < 0 || snakeY2[0] > 15) 
    {
        length = 6;
        snakeX2[0] = 25; snakeY2[0] = 12;
        snakeX2[1] = 26; snakeY2[1] = 12;
        snakeX2[2] = 27; snakeY2[2] = 12;
        snakeX2[3] = 28; snakeY2[3] = 12;
        snakeX2[4] = 29; snakeY2[4] = 12;
        snakeX2[5] = 30; snakeY2[5] = 12;
        dir2 = 2;
        GameState = "p1_w";
        ResetGame();
        return;
    }

    ///////////////////////
    // Ütközés egymással //
    ///////////////////////

    // Düntetlen
    if (snakeX1[0] == snakeX2[0] && snakeY1[0] == snakeY2[0])
    {
        GameState = "draw";
        ResetGame();
        return;
    }

    // P1 vagy P2 győz
    for (int i = 1; i < length; i++)
    {
        if (snakeX1[i] == snakeX2[0] && snakeY1[i] == snakeY2[0])
        {
            GameState = "p1_w";
            ResetGame();
            return;
        }

        if (snakeX1[0] == snakeX2[i] && snakeY1[0] == snakeY2[i])
        {
            GameState = "p2_w";
            ResetGame();
            return;
        }
    }

    for (int i = 0; i < 32; i++)
    {
        for (int j = 0; j < 16; j++)
        {
            playField[i][j] = false;
        }
    }

    for (int i = 0; i < length; i++)
    {
        playField[snakeX1[i]][snakeY1[i]] = true;
        playField[snakeX2[i]][snakeY2[i]] = true;
    }
}

// callback function that will be executed when data is received
void OnDataRecv(const esp_now_recv_info_t *recv_info, const uint8_t *data, int len)
{
    memcpy(&myData, data, sizeof(myData));

    if (strcmp(myData.a, "up") == 0)
    {
        if (dir2 != 1)
            dir2 = 3; // Menjünk felfelé
    }
    else if (strcmp(myData.a, "down") == 0)
    {
        if (dir2 != 3)
            dir2 = 1;  // Menjünk lefelé
    }
    else if (strcmp(myData.a, "left") == 0)
    {
        if (dir2 != 0)
            dir2 = 2; // Menjünk balra
    }
    else if (strcmp(myData.a, "right") == 0)
    {
        if (dir2 != 2)
            dir2 = 0;  // Menjünk jobbra
    }
    else if (strcmp(myData.a, "button") == 0)
    {
        if (GameState != "standby") return;
        tone(BUZZER, 1000, 300);
        IsP2Ready = !IsP2Ready;
    }
}


void updateScreen()
{    

    for (int i = 0; i < 32; i++)
    {
        for (int j = 0; j < 16; j++)
        {
            int matrixIndex = (int)(i / 8) + 4 * (int)(j / 8);
            matrix[matrixIndex].drawPixel(i % 8, j % 8, playField[i][j] ? LED_ON : LED_OFF);
        }
    }

    for (int i = 0; i < 8; i++) matrix[i].writeDisplay();
}

void JoystickBemenet()
{
    x = analogRead(JOYSTICK_X) - (JOYSTICK_RANGE_MAX / 2);
    y = analogRead(JOYSTICK_Y) - (JOYSTICK_RANGE_MAX / 2);

    IsPressed = digitalRead(JOYSTICK_BTN) == HIGH;
    if (IsPressed && IsPressed != IsPressedPrev)
    {
        if (GameState == "standby")
        {
            tone(BUZZER, 1000, 300);
            IsP1Ready = !IsP1Ready;
            IsPressedPrev = IsPressed;
        }
    }

    if (IsPressed != IsPressedPrev)
    {
        IsPressedPrev = IsPressed;
    }
}

// Directions:
// "none"  -> In the deadzone
// "up"    -> Positive y axis is the dominant
// "down"  -> Negative y axis is the dominant
// "right" -> Positive x axis is the dominant
// "left"  -> Negative x axis is the dominant
void DetermineDirection()
{
    String Direction = "";

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

    if (strcmp(Direction.c_str(), "up") == 0)
    {
        if (dir1 != 1)
            dir1 = 3; // Menjünk felfelé
    }
    else if (strcmp(Direction.c_str(), "down") == 0)
    {
        if (dir1 != 3)
            dir1 = 1;  // Menjünk lefelé
    }
    else if (strcmp(Direction.c_str(), "left") == 0)
    {
        if (dir1 != 0)
            dir1 = 2; // Menjünk balra
    }
    else if (strcmp(Direction.c_str(), "right") == 0)
    {
        if (dir1 != 2)
            dir1 = 0;  // Menjünk jobbra
    }
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

void clearScreen()
{
  // Összes kijelző "letakarítása"
    matrix[0].clear();
    matrix[1].clear();
    matrix[2].clear();
    matrix[3].clear();
    matrix[4].clear();
    matrix[5].clear();
    matrix[6].clear();
    matrix[7].clear();
    matrix[0].writeDisplay();
    matrix[1].writeDisplay();
    matrix[2].writeDisplay();
    matrix[3].writeDisplay();
    matrix[4].writeDisplay();
    matrix[5].writeDisplay();
    matrix[6].writeDisplay();
    matrix[7].writeDisplay();
}

void ResetGame()
{
    snakeX1[5] = 1;
    snakeX1[4] = 2;
    snakeX1[3] = 3;
    snakeX1[2] = 4;
    snakeX1[1] = 5;
    snakeX1[0] = 6;

    snakeY1[0] = 3;
    snakeY1[1] = 3;
    snakeY1[2] = 3;
    snakeY1[3] = 3;
    snakeY1[4] = 3;
    snakeY1[5] = 3;

    snakeX2[5] = 30;
    snakeX2[4] = 29;
    snakeX2[3] = 28;
    snakeX2[2] = 27;
    snakeX2[1] = 26;
    snakeX2[0] = 25;

    snakeY2[0] = 12;
    snakeY2[1] = 12;
    snakeY2[2] = 12;
    snakeY2[3] = 12;
    snakeY2[4] = 12;
    snakeY2[5] = 12;

    dir1 = 0;
    dir2 = 2;
}
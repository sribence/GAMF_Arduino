// A kommentek nem mindig jelentik azt amit ír pl azt írja hogy "Set color to green" de eközben fehérre állítja

#include <TFT_eSPI.h>  // Include the library 

TFT_eSPI tft = TFT_eSPI();  // Initialize an instance of the display 

const int PULSE_SENSOR = A0;
const int TEMP_SENSOR = A1;
const int ALCOHOL_SENSOR = A2;
const int ENCODER_CLK = 4;    
const int ENCODER_DAT = 3;     
const int ENCODER_BTN = 5;

bool IsPrinting = false;

int s0=30,s1=31,s2=32,s3=35;
int led = 34;
int out=2;
int flag=0;
byte counter=0;
byte countR=0,countG=0,countB=0;
int LightState = HIGH;

int PulseValue = 0;
int AlcoholValue = 0;
int Temperature = 0;
bool IsButtonPressed = false;
bool IsButtonPressedPrev = false;
unsigned int ColorSensorTimer;
unsigned int RefreshTimer;
int elozoAllapot, allapot, segedallapotJ = 0, segedallapotB = 0, szamlalo = 0, prevSzamlalo = 0;

int currentMenu = 0;
int prevCurrentMenu = 0;

void setup()
{  
    Serial.begin(115200);

    pinMode(ENCODER_CLK, INPUT);
    pinMode(ENCODER_DAT, INPUT);
    pinMode(ENCODER_BTN, INPUT);

    pinMode(s0,OUTPUT);
    pinMode(s1,OUTPUT);
    pinMode(s2,OUTPUT);
    pinMode(s3,OUTPUT);
    pinMode(led,OUTPUT);
    digitalWrite(led, HIGH);

    tft.init();               // Initialize the display 

    tft.setRotation(1);       // Set rotation (1 = landscape) 

    tft.fillScreen(TFT_BLACK); 
    tft.setCursor(0, 80);      // Set the cursor position 

    tft.setTextColor(TFT_ORANGE);  // Set text color to white 

    tft.setTextSize(1);       // Set text size 
    tft.setTextFont(1); 

    DrawHeart();

    ColorSensorTimer = millis();
    RefreshTimer = millis();
}
void loop()
{
    // Read every data
    ReadData();
    ReadRotary();

    // Read color every 0.5s
    if (millis() - ColorSensorTimer > 500)
    {
        TCS();
        ColorSensorTimer = millis();
    }

    switch (currentMenu)
    {
        case 0: 
            PulseState();
            break;
        case 1:
            AlcoholState();
            break;
        case 2:
            TempState();
            break;
        case 3:
            BulbState();
            break;
        case 4:
            PaintState();
            break;

    }

    if (IsButtonPressedPrev != IsButtonPressed)
        IsButtonPressedPrev = IsButtonPressed;
}   

void PulseState()
{
    if (IsButtonPressed && IsButtonPressed != IsButtonPressedPrev)
    {
        IsButtonPressedPrev = IsButtonPressed;
        if (IsPrinting)
        {
            IsPrinting = false;
            DrawHeart();
        }
        else
        {
            tft.fillScreen(TFT_BLACK); 
            IsPrinting = true;
        }
    }

    if (IsPrinting && millis() - RefreshTimer > 200)
    {
        tft.setCursor(0, 100);      // Set the cursor position 

        tft.setTextColor(TFT_WHITE, TFT_BLACK);  // Set text color to white 

        tft.setTextSize(2);       // Set text size 
        tft.setTextFont(1); 
        tft.println("  Heart Rate Value");
        tft.setTextFont(2); 
        tft.print("  ");
        tft.println(PulseValue);
        RefreshTimer = millis();
        return;
    }

    if (prevCurrentMenu != currentMenu)
    {
        DrawHeart();
        prevCurrentMenu = currentMenu;
    }
}

void AlcoholState()
{
    if (IsButtonPressed && IsButtonPressed != IsButtonPressedPrev)
    {
        IsButtonPressedPrev = IsButtonPressed;
        if (IsPrinting)
        {
            IsPrinting = false;
            DrawBeer();
        }
        else
        {
            tft.fillScreen(TFT_BLACK); 
            IsPrinting = true;
        }
    }

    if (IsPrinting && millis() - RefreshTimer > 200)
    {
        tft.setCursor(0, 100);      // Set the cursor position 

        tft.setTextColor(TFT_WHITE, TFT_BLACK);  // Set text color to white 

        tft.setTextSize(2);       // Set text size 
        tft.setTextFont(1); 
        tft.println("  Alcohol Value");
        tft.setTextFont(2); 
        tft.print("  ");
        tft.println(AlcoholValue);
        RefreshTimer = millis();
        return;
    }

    if (prevCurrentMenu != currentMenu)
    {
        DrawBeer();
        prevCurrentMenu = currentMenu;
    }
}

void TempState()
{
        if (IsButtonPressed && IsButtonPressed != IsButtonPressedPrev)
    {
        IsButtonPressedPrev = IsButtonPressed;
        if (IsPrinting)
        {
            IsPrinting = false;
            DrawThermometer();
        }
        else
        {
            tft.fillScreen(TFT_BLACK); 
            IsPrinting = true;
        }
    }

    if (IsPrinting && millis() - RefreshTimer > 200)
    {
        tft.setCursor(0, 100);      // Set the cursor position 

        tft.setTextColor(TFT_WHITE, TFT_BLACK);  // Set text color to white 

        tft.setTextSize(2);       // Set text size 
        tft.setTextFont(1); 
        tft.println("  Temperature");
        tft.setTextFont(2); 
        tft.print("  ");
        tft.print(Temperature);
        tft.println("°C");
        RefreshTimer = millis();
        return;
    }

    if (prevCurrentMenu != currentMenu)
    {
        DrawThermometer();
        prevCurrentMenu = currentMenu;
    }
}

void BulbState()
{
    if (IsButtonPressed && IsButtonPressed != IsButtonPressedPrev)
    {
        IsButtonPressedPrev = IsButtonPressed;
        if (LightState == HIGH)
        {
            LightState = LOW;
            DrawBulbOff();
            digitalWrite(led, LOW);
        }
        else
        {
            LightState = HIGH;
            DrawBulbOn();
            digitalWrite(led, HIGH);
        }
    }

    if (prevCurrentMenu != currentMenu)
    {
        if (LightState == HIGH)
        {
            DrawBulbOn();
        }
        else
        {
            DrawBulbOff();
        }
        prevCurrentMenu = currentMenu;
    }
}

void PaintState()
{
    if (IsButtonPressed && IsButtonPressed != IsButtonPressedPrev)
    {
        IsButtonPressedPrev = IsButtonPressed;
        if (IsPrinting)
        {
            IsPrinting = false;
            DrawPaintBucket();
        }
        else
        {
            tft.fillScreen(TFT_BLACK); 
            IsPrinting = true;
        }
    }

    if (IsPrinting && millis() - RefreshTimer > 200)
    {
        tft.setCursor(0, 100);      // Set the cursor position 

        tft.setTextColor(TFT_WHITE, TFT_BLACK);  // Set text color to white 

        tft.setTextSize(2);       // Set text size 
        tft.setTextFont(1); 
        tft.println("  Color Value"); 
        int red = map(countR, 0, 1024, 0, 255);
        int green = map(countG, 0, 1024, 0, 255);
        int blue = map(countB, 0, 1024, 0, 255);
        tft.print("  R: ");
        tft.println(red, DEC);
        tft.print("  G: ");
        tft.println(green, DEC);
        tft.print("  B: ");
        tft.println(blue, DEC);
        RefreshTimer = millis();
        return;
    }

    if (prevCurrentMenu != currentMenu)
    {
        DrawPaintBucket();
        prevCurrentMenu = currentMenu;
    }
}

void DrawHeart()
{
    tft.fillScreen(TFT_BLACK); 
    tft.setCursor(0, 70);      // Set the cursor position 

    tft.setTextColor(TFT_RED);  // Set text color to white 

    tft.setTextSize(1);       // Set text size 
    tft.setTextFont(1); 
    tft.println("         .....           .....");
    tft.println("     ,ad8PPPP88b,     ,d88PPPP8ba,");
    tft.println("    d8P\"      \"Y8b, ,d8P\"      \"Y8b");
    tft.println("   dP'           \"8a8\"           `Yd");
    tft.println("   8(              \"              )8");
    tft.println("   I8                             8I");
    tft.println("    Yb,                         ,dP");
    tft.println("     \"8a,                     ,a8\"");
    tft.println("       \"8a,                 ,a8\"");
    tft.println("         \"Yba             adP\"   ");
    tft.println("           `Y8a         a8P'");
    tft.println("             `88,     ,88'");
    tft.println("               \"8b   d8\"");
    tft.println("                \"8b d8\"");
    tft.println("                 `888'");
    tft.println("                   \" ");
}

void DrawBeer()
{
    tft.fillScreen(TFT_BLACK); 
    tft.setCursor(0, 40);      // Set the cursor position 

    tft.setTextColor(TFT_GREEN);  // Set text color to white 

    tft.setTextSize(2);       // Set text size 
    tft.setTextFont(1); 
    tft.println("          _");
    tft.println("         {_}");
    tft.println("         |(|");
    tft.println("         |=|");
    tft.println("        /   \\");
    tft.println("        |.--|");
    tft.println("        ||  |");
    tft.println("        ||  |");
    tft.println("        |'--|");
    tft.println("        '-=-'");
}

void DrawPaintBucket()
{
    tft.setRotation(1);       // Set rotation (1 = landscape) 

    tft.fillScreen(TFT_BLACK); 
    tft.setCursor(0, 80);      // Set the cursor position 

    tft.setTextColor(TFT_ORANGE);  // Set text color to white 
    
    tft.setTextSize(1);       // Set text size 

    tft.println("            .----,");
    tft.println("           /--._(");
    tft.println("           |____|");
    tft.println("           [____] .=======.");
    tft.println("             YY   q.     .p");
    tft.println("             ||   | `---' |");
    tft.println("             []   |_______|");
}

void DrawThermometer()
{
    tft.fillScreen(TFT_BLACK); 
    tft.setCursor(0, 25);      // Set the cursor position 

    tft.setTextColor(TFT_BLUE);  // Set text color to white 

    tft.setTextSize(1);       // Set text size 
    tft.setTextFont(1); 
    tft.println("            _________________");
    tft.println("          ._)               (_.");
    tft.println("          |    'F  ,-. 'C     |");
    tft.println("          |        | |___ 40  |");
    tft.println("          | 100 ---| |        |");
    tft.println("          |        | |        |");
    tft.println("          |  90 '''| |___ 30  |");
    tft.println("          |  80 ___| |        |");
    tft.println("          |        | |        |");
    tft.println("          |  70 ---| |___ 20  |");
    tft.println("          |        |#|        |");
    tft.println("          |  60 '''|#|        |");
    tft.println("          |  50 ___|#|___ 10  |");
    tft.println("          |        |#|        |");
    tft.println("          |  40 ---|#|        |");
    tft.println("          |        |#|___ 0   |");
    tft.println("          |  30 '''|#|        |");
    tft.println("          |  20 ___|#|        |");
    tft.println("          |        |#|___-10  |");
    tft.println("          |        |#|        |");
    tft.println("          |        |#|        |");
    tft.println("          |       (###)       |");
    tft.println("          |_       `-'       _|");
    tft.println("          ' )_______________( '");
}

void DrawBulbOn()
{
    tft.fillScreen(TFT_BLACK); 
    tft.setCursor(0, 75);      // Set the cursor position 

    tft.setTextColor(TFT_YELLOW);  // Set text color to white 

    tft.setTextSize(2);       // Set text size 
    tft.setTextFont(1); 
    tft.println("         :");
    tft.println("     '.  _  .'");
    tft.println("    -=  (~)  =-   ");
    tft.print("     .'  ");
    tft.setTextColor(TFT_DARKGREY);  // Set text color to white 
    tft.print("#");
    tft.setTextColor(TFT_YELLOW);  // Set text color to white 
    tft.println("  '.");
}

void DrawBulbOff()
{
    tft.fillScreen(TFT_BLACK); 
    tft.setCursor(0, 75);      // Set the cursor position 

    tft.setTextColor(TFT_DARKGREY);  // Set text color to white 

    tft.setTextSize(2);       // Set text size 
    tft.setTextFont(1); 
    tft.println("          ");
    tft.println("         _   ");
    tft.println("        (~) ");
    tft.println("         # ");
}

// This function will read all the values from the sensors and buttons
void ReadData()
{
    // Read the values from the sensors
    PulseValue = analogRead(PULSE_SENSOR);
    AlcoholValue = analogRead(ALCOHOL_SENSOR);
    int RawTemperature = analogRead(TEMP_SENSOR);
    
    // Calculate temperature
    Temperature = (RawTemperature * 5.0 / 1024.0) * 100;
}

void ReadRotary()
{
    // Button
    IsButtonPressed = digitalRead(ENCODER_BTN) == LOW;

    if (IsPrinting) return;
    // Minden kattanás 1, a köztes rész 0 értéket ad vissza
    allapot = digitalRead(ENCODER_CLK); 

    if (allapot != elozoAllapot) // Csak egyszer hajtsuk végre állapotonként
    {
        prevSzamlalo = szamlalo;
        if (digitalRead(ENCODER_DAT) != allapot) // A DT értéke az állapothoz 
        {
            // Számláló növelése
            segedallapotJ++;
            segedallapotB = 0;
            if (segedallapotJ == 2)
            {
                szamlalo++;
                segedallapotJ = 0;
            }
        } 
        else 
        {
            // Számláló csökkentése
            segedallapotB++;
            segedallapotJ = 0;
            if (segedallapotB == 2)
            {
                szamlalo--;
                segedallapotB = 0;
            }
        }
        
        // Állapot frissítése
        elozoAllapot = allapot;
    }

    if (szamlalo < 0) szamlalo = 4;
    currentMenu = szamlalo % 5;
}

void TCS()
{
    flag=0;
    digitalWrite(s1,HIGH);
    digitalWrite(s0,HIGH);
    digitalWrite(s2,LOW);
    digitalWrite(s3,LOW);
    attachInterrupt(0, ISR_INTO, CHANGE);
    timer0_init();
}

void ISR_INTO()
{
    counter++;
}
 
void timer0_init(void)
{
    TCCR2A=0x00;
    TCCR2B=0x07;   //the clock frequency source 1024 points
    TCNT2= 100;    //10 ms overflow again
    TIMSK2 = 0x01; //allow interrupt
}

int i=0;

ISR(TIMER2_OVF_vect)//the timer 2, 10ms interrupt overflow again. Internal overflow interrupt executive function
{
    TCNT2=100;
    flag++;

    if(flag==1)
    {
        countR=counter;
        digitalWrite(s2,HIGH);
        digitalWrite(s3,HIGH);
    }
    else if(flag==2)
    {
        countG=counter;
        digitalWrite(s2,LOW);
        digitalWrite(s3,HIGH);
    }
    else if(flag==3)
    {
        countB=counter;
        digitalWrite(s2,LOW);
        digitalWrite(s3,LOW);
    }
    else if(flag==4)
    {
       flag=0;
    }
    
    counter=0;
}

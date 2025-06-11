// Includes
#include <SPI.h>
#include <WiFi101.h>
//////////////////////////////////////////////////////////
//                      Variables                       //
//////////////////////////////////////////////////////////
const int POWER_LAMP = 2;
const int RELAY = 3;
const int LIGHT_SENSOR = A0;
const int SOIL_SENSOR = A1;
const int WATER_SENSOR = A2;
const int RAIN_THRESHOLD = 100;
const int SOIL_THRESHOLD = 50;
const int LIGHT_THRESHOLD = 100;
const char SSID[] = "";
const char PASS[] = "";
//////////////////////////////////////////////////////////

// Helper variables
int SoilValue = 0;
int RainValue = 0;
int LightValue = 0;
String PumpMode = "auto";
String LampMode = "auto";
WiFiServer server(80);

// This function runs once after the Arduino is turned on
void setup()
{
    // Start serial connection at 9600 baud rate
    Serial.begin(9600);

    pinMode(RELAY, OUTPUT);
    pinMode(POWER_LAMP, OUTPUT);
    pinMode(LIGHT_SENSOR, INPUT);
    pinMode(SOIL_SENSOR, INPUT);
    pinMode(WATER_SENSOR, INPUT);

    // Attempt to connect for up to 20 seconds
    unsigned long startAttemptTime = millis();
    const unsigned long wifiTimeout = 20000; // 20 seconds timeout

    // Connect to wifi
    Serial.print("Connecting to WiFi");
    while (WiFi.status() != WL_CONNECTED && millis() - startAttemptTime < wifiTimeout) {
        Serial.print(".");
        WiFi.begin(SSID, PASS);
        delay(1000);
    }

    // Print wifi info if successful
    if (WiFi.status() == WL_CONNECTED) 
    {
        Serial.println("\nConnected to WiFi!");
        server.begin();
        Serial.print("IP Address: ");
        IPAddress ip = WiFi.localIP();
        Serial.println(ip);
    } 

    // If failed the stop the program
    else 
    {
        Serial.println("\nFailed to connect to WiFi");
        while (true);
    }
}

// This function repeats itself after the `setup()` has finished running
void loop()
{
    ReadSoil();
    ReadLight();
    ReadRain();

    WebServer();

    if (ShouldUsePump()) SetRelay("on");
    else SetRelay("off");

    if (ShouldUseLamp()) SetLamp("on");
    else SetLamp("off");
}

//////////////////////////////////////////////////////////
//                   Helper Functions                   //
//////////////////////////////////////////////////////////

// This function determines whether you should turn in the pump or not
// Usage: ShouldUsePump(); // returns a boolean
bool ShouldUsePump()
{
    if (PumpMode == "on") return true;
    if (PumpMode == "off") return false;

    if (SoilValue < SOIL_THRESHOLD && RainValue < RAIN_THRESHOLD)
    {
        return true;
    }

    return false;
}

// This function determines whether you should turn in the lamp or not
// Usage: ShouldUseLamp(); // returns a boolean
bool ShouldUseLamp()
{
    if (LampMode == "on") return true;
    if (LampMode == "off") return false;

    if (LightValue < LIGHT_THRESHOLD)
    {
        return true;
    }
    
    return false;
}

// This function changes the state of the relay
// Usage: SetRelay("on");
//        SetRelay("off");
void SetRelay(String state)
{
    digitalWrite(RELAY, state == "on" ? HIGH : LOW);
}

// This function changes the state of the relay
// Usage: SetLamp("on");
//        SetLamp("off");
void SetLamp(String state)
{
    digitalWrite(POWER_LAMP, state == "on" ? HIGH : LOW);
}

// This function reads the data from the soil sensor
// Usage ReadSoil();
void ReadSoil()
{
    SoilValue = analogRead(SOIL_SENSOR);
}

// This function reads the data from the water sensor
// Usage ReadRain();
void ReadRain()
{
    RainValue = analogRead(WATER_SENSOR);
}

// This function reads the data from the light sensor
// Usage ReadLight();
void ReadLight()
{
    LightValue = analogRead(LIGHT_SENSOR);
}

// This function hosts a website and lets you change the state of the arduino
// Usage: WebServer();
void WebServer()
{
    WiFiClient client = server.available();

    if (client) 
    {
        Serial.println("New client connected");
        String currentLine = "";
        String requestLine = ""; // <-- capture first line of the request

        bool requestCaptured = false;

        while (client.connected()) 
        {
            if (client.available()) 
            {
                char c = client.read();
                Serial.write(c); // Optional debug
        
                if (c == '\n') 
                {
                    if (currentLine.length() == 0) 
                    {
                        // Here is where we handle the request

                        // Example: Turn GPIO on/off based on URL
                        if (requestLine.indexOf("GET /lamp-on") >= 0) {
                            LampMode = "on";
                        } else if (requestLine.indexOf("GET /lamp-off") >= 0) {
                            LampMode = "off";
                        } else if (requestLine.indexOf("GET /lamp-auto") >= 0) {
                            LampMode = "auto";
                        } else if (requestLine.indexOf("GET /pump-on") >= 0) {
                            PumpMode = "on";
                        } else if (requestLine.indexOf("GET /pump-off") >= 0) {
                            PumpMode = "off";
                        } else if (requestLine.indexOf("GET /pump-auto") >= 0) {
                            PumpMode = "auto";
                        }

                        // Send HTML response
                        client.println("<!DOCTYPE html>");
                        client.println("<html lang='en'>");
                        client.println("");
                        client.println("<head>");
                        client.println("<meta charset='UTF-8'>");
                        client.println("<meta name='viewport' content='width=device-width, initial-scale=1.0'>");
                        client.println("<title>Weather Station</title>");
                        client.println("<style>");
                        client.println("body {");
                        client.println("display: flex;");
                        client.println("align-items: center;");
                        client.println("justify-content: center;");
                        client.println("color: white;");
                        client.println("font-family: monospace;");
                        client.println("background: rgb(60, 60, 60);");
                        client.println("min-height: 90vh;");
                        client.println("}");
                        client.println("");
                        client.println("h1 {");
                        client.println("text-align: center;");
                        client.println("}");
                        client.println("");
                        client.println(".container {");
                        client.println("display: flex;");
                        client.println("align-items: center;");
                        client.println("justify-content: center;");
                        client.println("flex-direction: column;");
                        client.println("}");
                        client.println("");
                        client.println(".data-container {");
                        client.println("display: grid;");
                        client.println("grid-template-columns: auto auto;");
                        client.println("}");
                        client.println("");
                        client.println(".data-card {");
                        client.println("min-width: 140px;");
                        client.println("padding: 10px;");
                        client.println("margin: 10px;");
                        client.println("border: 2px solid gray;");
                        client.println("border-radius: 5px;");
                        client.println("background-color: #1e1e1e;");
                        client.println("}");
                        client.println("");
                        client.println(".sub-container {");
                        client.println("display: flex;");
                        client.println("flex-direction: column;");
                        client.println("");
                        client.println("}");
                        client.println("");
                        client.println("button {");
                        client.println("margin: 5px;");
                        client.println("}");
                        client.println("");
                        client.println("p {");
                        client.println("width: 100%;");
                        client.println("}");
                        client.println("");
                        client.println(".data-container {");
                        client.println("display: grid;");
                        client.println("grid-template-columns: auto auto;");
                        client.println("}");
                        client.println("");
                        client.println("@media screen and (max-width: 380px) {");
                        client.println(".data-container {");
                        client.println("display: grid;");
                        client.println("grid-template-columns: auto;");
                        client.println("}");
                        client.println("}");
                        client.println("</style>");
                        client.println("</head>");
                        client.println("");
                        client.println("<body>");
                        client.println("<div class='container'>");
                        client.println("<h1>Smart Garden Station</h1>");
                        client.println("<div class='data-container'>");
                        client.println("<div class='sub-container'>");
                        client.println("<button onclick=\"location.href='/lamp-on'\">Lamp ON</button>");
                        client.println("<button onclick=\"location.href='/lamp-off'\">Lamp OFF</button>");
                        client.println("<button onclick=\"location.href='/lamp-auto'\">Lamp AUTO</button>");
                        client.println("</div>");
                        client.println("<div class='sub-container'>");
                        client.println("<button onclick=\"location.href='/pump-on'\">Pump ON</button>");
                        client.println("<button onclick=\"location.href='/pump-off'\">Pump OFF</button>");
                        client.println("<button onclick=\"location.href='/pump-auto'\">Pump AUTO</button>");
                        client.println("</div>");
                        client.println("</div>");
                        client.println("</div>");
                        client.println("</body>");
                        client.println("");
                        client.println("</html>");

                        break;
                    } 
                    else 
                    {
                        if (!requestCaptured) {
                            requestLine = currentLine;
                            requestCaptured = true;
                        }
                        currentLine = "";
                    }
                } 
                else if (c != '\r') 
                {
                    currentLine += c;
                }
            }
        }

        delay(1); // let browser receive data
        client.stop();
        Serial.println("Client disconnected");
    }
}

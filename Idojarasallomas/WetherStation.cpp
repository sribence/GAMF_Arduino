// Includes
#include <DHT.h>
#include <SPI.h>
#include <WiFiNINA.h>
#include <Servo.h>

//////////////////////////////////////////////////////////
//                      Variables                       //
//////////////////////////////////////////////////////////
const int DHT_SENSOR = 2;
const int SERVO_PIN = 5;
const int PHOTOCELL_SENSOR_1 = A2;
const int PHOTOCELL_SENSOR_2 = A1;
const int WATER_SENSOR = A0;
const int STEAM_SENSOR = A3;
const int LIGHT_SENSOR = A4;
const int SMOKE_SENSOR = A5;
const int POTMETER = A6;
const char SSID[] = "Weather Station";
const char PASSWORD[] = "********";
const int PHOTOCELL_SENSOR_TOLERANCE = 100;
//////////////////////////////////////////////////////////

// Helper variables
const int ServoLimitMin = 30;
const int ServoLimitMax = 60;
int ServoDegrees = 90;
DHT dht(DHT_SENSOR, DHT11);
unsigned int DhtTimer;
unsigned int ServoTimer;
float Humidity;
float TemperatureC;
float TemperatureF;
float HeatIndexC;
float HeatIndexF;
int WaterLevel;
int SteamLevel;
int LightLevel;
int SmokeLevel;
int PhotocellLevel1;
int PhotocellLevel2;
String WindDirection = "-";
int PotmeterValue;
int PrevPotmeterValue;
WiFiServer server(80);
Servo szervo;

// This function runs once after the Arduino is turned on
void setup()
{
    pinMode(DHT_SENSOR, INPUT);                                 // Set `DHT_SENSOR` pin to `INPUT`

    Serial.begin(9600);                                         // Connect to serial port, set baud rate at `9600`
    dht.begin();                                                // Initialize the DHT sensor

    DhtTimer = millis();                                        // Set an initial value of `DhtTimer` 
    ServoTimer = millis();                                      // Set an initial value of `ServoTimer` 

    // Start WiFi in AP mode
    Serial.println("Setting up access point...");
    int status = WiFi.beginAP(SSID, PASSWORD);

    // Connect servo and set it to a default value
    szervo.attach(SERVO_PIN);
    szervo.write(ServoDegrees);
    
    // If failed to begin the AP then enter into an infinit loop
    if (status != WL_AP_LISTENING) 
    {
        Serial.println("Failed to start Access Point");
        while (true);
    }

    // Print information about the network
    Serial.println("Access Point started");
    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());
    
    // Start the server
    server.begin();
}

// This function repeats itself after the `setup()` has finished running
void loop()
{
    // Read data
    UseDHT();
    UseWaterSensor();
    UseSteamSensor();
    UseLightSensor();
    UseSmokeSensor();
    UsePotmeter();

    // Set servos
    ReadPhotocellSensors();
    SetSolarPanel();

    // Display
    Display();
}

//////////////////////////////////////////////////////////
//                   Helper Functions                   //
//////////////////////////////////////////////////////////

// This function will use the DTH11 sensor and mesure the temperute and humidity
// Usage: UseDHT();
void UseDHT()
{
    // Use the sensor every 2 seconds (the sensor is slow)
    if (millis() - DhtTimer < 2000) return;

    float h = dht.readHumidity();           // Mesure humidity
    float t = dht.readTemperature();        // Mesure temperature (°C)
    float f = dht.readTemperature(true);    // Mesure temperature (°F)

    // Check if the sensor read the data sucessfuly
    if (isnan(h) || isnan(t) || isnan(f)) 
    {
        Serial.println("Failed to read from DHT sensor!");      // Send an error message to the serial connection
        DhtTimer = millis();                                    // Reset the timer
        return;                                                 // Exit from the function
    }

    float hif = dht.computeHeatIndex(f, h);         // Compute heat index (°F)
    float hic = dht.computeHeatIndex(t, h, false);  // Compute heat index (°C)

    // Save the data to global variables (later used for displaying the data)
    Humidity = h;
    TemperatureC = t;
    TemperatureF = f;
    HeatIndexC = hic;
    HeatIndexF = hif;

    // Reset the timer
    DhtTimer = millis();
}

// This function will read the data from the photocell sensors
// Usage: ReadPhotocellSensors();
void ReadPhotocellSensors()
{
    // Read the analog values and store it in global variables
    PhotocellLevel1 = analogRead(PHOTOCELL_SENSOR_1);
    PhotocellLevel2 = analogRead(PHOTOCELL_SENSOR_2);
}

// This function will set the rotation of the solar panel
// Usage: SetSolarPanel();
void  SetSolarPanel()
{
    // Return if the timer doesn't allow to move the servo
    if (millis() - ServoTimer <= 150)
        return;

    // Return if the light source didn't move enough to move the motor
    if (abs(PhotocellLevel1 - PhotocellLevel2) <= PHOTOCELL_SENSOR_TOLERANCE) 
        return;

    // Rotate the servo to make the solar panel face the light source
    if (PhotocellLevel1 > PhotocellLevel2)
    {
        // Subtracting 5 degrees
        ServoDegrees -= 5;

        // If it's over the limit then correct the value
        if (ServoDegrees < 90 - ServoLimitMin) ServoDegrees = 90 - ServoLimitMin;

        // Write the data to the servo
        szervo.write(ServoDegrees);
    }
    else
    {
        // Adding 5 degrees
        ServoDegrees += 5;
        
        // If it's over the limit then correct the value
        if (ServoDegrees > 90 + ServoLimitMax) ServoDegrees = 90 + ServoLimitMax;
        
        // Write the data to the servo
        szervo.write(ServoDegrees);
    }

    // Reset the servo timer
    ServoTimer = millis();
}

// This function will read the data from the water sensor
// Usage: UseWaterSensor();
void UseWaterSensor()
{
    // Read the analog value and store it in a global variable
    WaterLevel = analogRead(WATER_SENSOR);
}

// This function will read the data from the steam sensor
// Usage: UseSteamSensor();
void UseSteamSensor()
{
    // Read the analog value and store it in a global variable
    SteamLevel = analogRead(STEAM_SENSOR);
}

// This function will read the data from the light sensor
// Usage: UseLightSensor();
void UseLightSensor()
{
    // Read the analog value and store it in a global variable
    LightLevel = analogRead(LIGHT_SENSOR);
}

// This function will read the data from the smoke sensor
// Usage: UseSmokeSensor();
void UseSmokeSensor()
{
    // Read the analog value and store it in a global variable
    SmokeLevel = analogRead(SMOKE_SENSOR);
}

// This function check which direction was the potmeter rotated (wind direction)
// Usage UsePotmeter();
void UsePotmeter()
{
    // Read the data from the potmeter
    PotmeterValue = analogRead(POTMETER);

    // If the `PrevPotmeterValue` doesn't have value 
    // then exit the function and set the previous value to the current value
    if (!PrevPotmeterValue) 
    {
        PrevPotmeterValue = PotmeterValue;
        return;
    }

    // If the previous value is smaller then the wind is moving north
    if (PrevPotmeterValue < PotmeterValue)
    {
        WindDirection = "North";
    }
    
    // Otherwise the wind is moving south 
    // (still making sure if it isn't changed then don't change the wind direction)
    else if (PrevPotmeterValue > PotmeterValue)
    {
        WindDirection = "South";
    }

    // Set the previous value to the current value
    PrevPotmeterValue = PotmeterValue;
}

// This function will start a webserver and display the data
// Usage: Display();
void Display()
{
    // Listen for incoming clients
    WiFiClient client = server.available();

    if (client) 
    {
        Serial.println("New client connected");
        String currentLine = "";
    
        // Read and process client's request
        while (client.connected()) 
        {
            if (client.available()) 
            {
                char c = client.read();
                Serial.write(c);
        
                if (c == '\n') 
                {
                    // Send the response only after receiving a blank line (end of request)
                    if (currentLine.length() == 0) {
                        // Send HTML headers
                        client.println("HTTP/1.1 200 OK");
                        client.println("Content-type:text/html");
                        client.println("Connection: close");
                        client.println();

                        // HTML content to display
                        client.println("<!DOCTYPE html>");
                        client.println("<html lang='en'>");
                        client.println("<head>");
                        client.println("<meta charset='UTF-8'>");
                        client.println("<meta name='viewport' content='width=device-width, initial-scale=1.0'>");
                        client.println("<meta http-equiv='refresh' content='1'>");
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
                        client.println(".container {");
                        client.println("display: flex;");
                        client.println("align-items: center;");
                        client.println("justify-content: center;");
                        client.println("flex-direction: column;");
                        client.println("}");
                        client.println("");
                        client.println(".data-container {");
                        client.println("display: flex;");
                        client.println("align-items: center;");
                        client.println("justify-content: center;");
                        client.println("flex-direction: row;");
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
                        client.println("p {");
                        client.println("width: 100%;");
                        client.println("}");
                        client.println("");
                        client.println("@media screen and (max-width: 1496px) {");
                        client.println(".data-container {");
                        client.println("display: grid;");
                        client.println("grid-template-columns: auto auto auto auto;");
                        client.println("}");
                        client.println("}");
                        client.println("");
                        client.println("@media screen and (max-width: 760px) {");
                        client.println(".data-container {");
                        client.println("display: grid;");
                        client.println("grid-template-columns: auto auto;");
                        client.println("}");
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
                        client.println("<body>");
                        client.println("<div class='container'>");
                        client.println("<h1>Weather Station</h1>");
                        client.println("<div class='data-container'>");
                        client.println("<div class='data-card'>");
                        client.println("<h2>Water</h2>");
                        client.println("<p>" + String(WaterLevel) + "</p>");
                        client.println("</div>");
                        client.println("<div class='data-card'>");
                        client.println("<h2>Temperature</h2>");
                        client.println("<p>" + String(TemperatureC) + "°C / " + String(TemperatureF) + "°F</p>");
                        client.println("</div>");
                        client.println("<div class='data-card'>");
                        client.println("<h2>Humidity</h2>");
                        client.println("<p>" + String(Humidity) + "%</p>");
                        client.println("</div>");
                        client.println("<div class='data-card'>");
                        client.println("<h2>Heat index</h2>");
                        client.println("<p>" + String(HeatIndexC) + "°C / " + String(HeatIndexF) + "°F</p>");
                        client.println("</div>");
                        client.println("<div class='data-card'>");
                        client.println("<h2>Steam</h2>");
                        client.println("<p>" + String(SteamLevel) + "</p>");
                        client.println("</div>");
                        client.println("<div class='data-card'>");
                        client.println("<h2>Light</h2>");
                        client.println("<p>" + String(LightLevel) + "</p>");
                        client.println("</div>");
                        client.println("<div class='data-card'>");
                        client.println("<h2>Smoke</h2>");
                        client.println("<p>" + String(SmokeLevel) + "</p>");
                        client.println("</div>");
                        client.println("<div class='data-card'>");
                        client.println("<h2>Wind</h2>");
                        client.println("<p>" + WindDirection + "</p>");
                        client.println("</div>");
                        client.println("</div>");
                        client.println("</div>");
                        client.println("</body>");
                        client.println("</html>");
                        
                        break;
                    } 
                    else 
                    {
                        currentLine = "";
                    }
                } 
                else if (c != '\r') 
                {
                    currentLine += c; // Build the request line
                }
            }
        }
        // Close the connection
        client.stop();
        Serial.println("Client disconnected");
    }
}

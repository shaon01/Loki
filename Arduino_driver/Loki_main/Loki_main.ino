#include <WiFiEsp.h>
#include <WiFiEspClient.h>
#include <WiFiEspServer.h>
#include <WiFiEspUdp.h>

#include <Loki.h>
#include <ArduinoJson.h>

#define SPEED 85    
#define TURN_SPEED 90  

Loki evilLoki = Loki();

// variables for wifi driver
char ssid[] = "IP ON LAN :D IF WiFi Mad"; // replace ****** with your network SSID (name)
char pass[] = "multiple#Omits0#bear"; // replace ****** with your network password
int status = WL_IDLE_STATUS;
// use a ring buffer to increase speed and reduce memory allocation
char packetBuffer[100]; 
WiFiEspUDP Udp;
unsigned int localPort = 8888;  // local port to listen on

// for udp sendSensorData
IPAddress remoteIp(192, 168, 10, 109);  // <- EDIT!!!!
unsigned short remotePort = 8887;

void setup()
{
  Serial.begin(9600); // initialize serial for debugging
  Serial1.begin(115200);
  Serial1.write("AT+UART_DEF=9600,8,1,0,0\r\n");
  delay(200);
  Serial1.write("AT+RST\r\n");
  delay(200);
  Serial1.begin(9600); // initialize serial for ESP module
  WiFi.init(&Serial1); // initialize ESP module
  pinMode(LED_BUILTIN, OUTPUT);

  // check for the presence of the shield
  if (WiFi.status() == WL_NO_SHIELD)
  {
    Serial.println("WiFi shield not present");
    // don't continue
    while (true)
      ;
  }

  // attempt to connect to WiFi network
  while (status != WL_CONNECTED)
  {
    Serial.print("Attempting to connect to WPA SSID: ");
    Serial.println(ssid);
    // Connect to WPA/WPA2 network
    status = WiFi.begin(ssid, pass);
  }

  Serial.println("You're connected to the network");
  printWifiStatus();
  Udp.begin(localPort);
  digitalWrite(LED_BUILTIN, HIGH);
  Serial.print("Listening on port ");
  Serial.println(localPort);
}

void loop()
{
  int packetSize = Udp.parsePacket();
  if (packetSize)
  { // if you get a client,
    Serial.print("Received packet of size ");
    Serial.println(packetSize);
    int len = Udp.read(packetBuffer, 255);
    if (len > 0)
    {
      packetBuffer[len] = 0;
    }
    StaticJsonDocument<512> doc;
    DeserializationError error = deserializeJson(doc, packetBuffer);

    if (error)
    {
      Serial.print(F("deserializeJson() failed: "));
      Serial.println(error.c_str());
      return;
    }
    // char c=packetBuffer[0];
    Serial.print("Received Data :");
    Serial.println(packetBuffer);
    // checking the right vlue
    const char *Car = doc["Car"];
    unsigned int setSpeed = doc["Speed"];
    if (Car)
    {
      if (strcmp(Car, "Forward") == 0) //{"Car":"Forward"}
        {        
          Serial.println("Got Forward \n");
          if (setSpeed)
          {
            evilLoki.go_advance(setSpeed);
            Serial.print("moving with speed:");
            Serial.println(setSpeed);
          }
          else
          {
            evilLoki.go_advance();
          }
        }
      else if (strcmp(Car, "Backward") == 0) //{"Car":"Backward"}
        {
          Serial.println("Got Backward \n");
          evilLoki.go_back();
        }
      else if (strcmp(Car, "Left") == 0) //{"Car":"Left"}
        {
          Serial.println("Got Left \n");
          evilLoki.counterclockwise();
        }
      else if (strcmp(Car, "Right") == 0) //{"Car":"Right"}
      {
        Serial.println("Got Right \n");
        evilLoki.clockwise();
      }
      else if (strcmp(Car, "Stop") == 0) //{"Car":"Right"}
      {
        Serial.println("Got Right \n");
        evilLoki.stop_Stop();
      }
    }
    // sendSensorData();
  }

  
}

void printWifiStatus()
{
  // print the SSID of the network you're attached to
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your WiFi shield's IP address
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // print where to go in the browser
  Serial.println();
  Serial.print("To see this page in action, open a browser to http://");
  Serial.println(ip);
  Serial.println();
}

void sendSensorData()
{
  StaticJsonDocument<500> doc;

  // Create the "analog" array
  JsonArray analogValues = doc.createNestedArray("Distance");
  for (int pin = 0; pin < 10; pin++) {
    // Read the analog input
    int value = evilLoki.getCurrentDistance();

    // Add the value at the end of the array
    analogValues.add(value);
  }

  // Create the "digital" array
  JsonArray digitalValues = doc.createNestedArray("digital");
  for (int pin = 0; pin < 14; pin++) {
    // Read the digital input
    int value = pin;

    // Add the value at the end of the array
    digitalValues.add(value);
  }

  Udp.beginPacket(remoteIp, remotePort);
  serializeJson(doc, Udp);
  Udp.println();
  Udp.endPacket();


}
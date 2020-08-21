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
    if (Car)
    {
      if (strcmp(Car, "Forward") == 0) //{"Car":"Forward"}
        Serial.println("Got Forward \n");
      else if (strcmp(Car, "Backward") == 0) //{"Car":"Backward"}
        Serial.println("Got Backward \n");
      else if (strcmp(Car, "Left") == 0) //{"Car":"Left"}
        Serial.println("Got Left \n");
      else if (strcmp(Car, "Right") == 0) //{"Car":"Right"}
        Serial.println("Got Right \n");
    }
    // switch (c)    //serial control instructions
    // {
    //   case 'A':evilLoki.go_advance(SPEED);break;
    //   case 'L':evilLoki.left_turn(TURN_SPEED);break;
    //   case 'R':evilLoki.right_turn(TURN_SPEED);break;
    //   case 'B':evilLoki.go_back(SPEED);break;
    //   case 'E':evilLoki.stop_Stop();break;
    //   case 'F':evilLoki.left_shift(0,150,0,150);break; //left ahead
    //   case 'H':evilLoki.right_shift(180,0,150,0);break; //right ahead
    //   case 'I':evilLoki.left_shift(150,0,150,0); break;//left back
    //   case 'K':evilLoki.right_shift(0,130,0,130); break;//right back
    //   case 'O':evilLoki.left_shift(200,150,150,200); break;//left shift
    //   case 'T':evilLoki.right_shift(200,200,200,200); break;//left shift
    //   default:break;
    // }
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

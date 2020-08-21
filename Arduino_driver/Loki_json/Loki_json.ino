
#include <ArduinoJson.h>

/******templete serial command
{"Car":"Forward"}
{"Car":"Backward"}
{"Car":"Left"}
{"Car":"Right"}
******************/
void setup()
{
  // Initialize serial port
  Serial.begin(9600);
  while (!Serial)
    continue;
}

void loop()
{

  String payload;
  while (!Serial.available())
  {
  }

  if (Serial.available())
    payload = Serial.readStringUntil('\n');

  StaticJsonDocument<512> doc;
  DeserializationError error = deserializeJson(doc, payload);

  if (error)
  {
    Serial.print(F("deserializeJson() failed: "));
    Serial.println(error.c_str());
    return;
  }

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
  // delay(20);
}

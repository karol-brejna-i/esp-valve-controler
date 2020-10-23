#include <ArduinoJson.h>
#include "valves.h"

void constructValveJson(JsonObject valveJson, ValveController *valve);
void generateStatusJson(DynamicJsonDocument *doc, ValveController *mainValve, ValveController *drainValve);


struct network_info2 {
   String ssid;
   String hostname;
   String ip;
   int strength;
};

struct network_info {
  const char* ssid;
  const char* hostname;
  const char* ip;
  const int strength;
};


// void buildNetworkInfo(network_info* systemInfo);
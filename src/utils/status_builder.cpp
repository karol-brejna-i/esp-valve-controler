#include <ArduinoJson.h>
#include "status_builder.h"
#include "wifi_utils.h"

void buildNetworkInfo(network_info2 &systemInfo) {
    systemInfo.ssid = WiFi.SSID();
    systemInfo.hostname = WiFi.hostname();
    systemInfo.ip = WiFi.localIP().toString();
    systemInfo.strength = WiFi.RSSI();
}


/*
  {
      "network" : {
        "ssid": "tpl24",
        "strength": -66,
        "hostname": "ESP32xxyy",
        "ip":"192.168.0.235"
      },
      "system": {
        "ram_total":49504,
        "ram_free":33152,
        "fs_size":233681,
        "fs_free":147086,
        "uptime":261279
      }
  }
*/
void testGenerateStatusJson() {
    const size_t capacity = JSON_OBJECT_SIZE(4) + 2*JSON_OBJECT_SIZE(5) + 200;
    DynamicJsonDocument doc(capacity);
}


#include "valves.h"

//TODO now we are copying values (String(x)). There may be a way to make improve on that (either using Strigns in the function call, or sth else)
void constructNetworkJson(JsonObject jo, const char* ssid, const char* hostname, const int strength, const char* ip) {
    jo["ssid"] = String(ssid);
    jo["strength"] = strength;
    jo["hostname"] = String(hostname);
    jo["ip"] = String(ip);
}

// TODO implement obtaining system data
void constructSystemJson(JsonObject jo) {
    jo["ram_total"] = -1;
    jo["ram_free"] = -1;
    jo["uptime"] = -1;
    // jo["fs_size"] =233681;
    // jo["fs_free"] =147086;
    // XXX TODO https://community.mydevices.com/t/system-uptime-millis-to-dd-hh-mm-code-optimization-question-esp8266/4434/5
    jo["uptime"] = -1;

}


// TODO consider adding gpioOn, gpioOff as fields
void constructValveJson(JsonObject valveJson, ValveController *valve) {
    valveJson["name"] = valve->getName();
    valveJson["state"] = VALVE_STATE_STRING[valve->state];
    valveJson["lastAction"] = valve->lastAction;
    valveJson["lastActionTimestamp"] = valve->lastActionTimestamp;
    valveJson["previousState"] = VALVE_STATE_STRING[valve->previousState];
}

void generateStatusJson(DynamicJsonDocument *doc, ValveController *mainValve, ValveController *drainValve) {
    String output = "";
    serializeJson(*doc, output);

    JsonObject systemJson = doc->createNestedObject("system");
    constructSystemJson(systemJson);

    JsonObject networkJson = doc->createNestedObject("network");

    network_info2 ni;
    buildNetworkInfo(ni);
    constructNetworkJson(networkJson, ni.ssid.c_str(), ni.hostname.c_str(), ni.strength, ni.ip.c_str());

    JsonArray valves = doc->createNestedArray("valves");
    JsonObject mainValveJson = valves.createNestedObject();
    JsonObject drainValveJson = valves.createNestedObject();

    constructValveJson(mainValveJson, mainValve);
    constructValveJson(drainValveJson, drainValve);
}

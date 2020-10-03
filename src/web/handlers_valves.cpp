#include "handlers_valves.h"
#include "utils/debug_utils.h"
#include "valves.h"


/**
 * valve = 1 --> main valve
 * valve = 2 --> drain valve
 */
ValveController* whichValve(int valve) {
    debugD("whichValve %d", valve);
    ValveController* result = NULL;

    switch (valve)
    {
        case 1:
            result = mainValve;
            break;
        case 2:
            result = drainValve;
            break;
        default:
            debugW("Unknown valve");
            break;
    }
    return result;
}

ValveController* startOpening(int valveNo) {
    debugD("startOpening valveNo %d", valveNo);
    ValveController* valve = whichValve(valveNo);
    valve->startOpening();
    return valve;
}

ValveController* startClosing(int valveNo) {
    debugD("startClosing valveNo %d", valveNo);
    ValveController* valve = whichValve(valveNo);
    valve->startClosing();
    return valve;
}

void handleMainValveOn(AsyncWebServerRequest *request)
{
    debugI("handleMainValve open");
    ValveController* valve = startOpening(1);
    request->send(200, "text/plain", valve->toString());
}

void handleDrainValveOn(AsyncWebServerRequest *request)
{
    debugI("handleDrainValveOn open");
    ValveController* valve = startOpening(2);
    request->send(200, "text/plain", valve->toString());
}


void handleMainValveOff(AsyncWebServerRequest *request)
{
    debugI("handleMainValve off");
    ValveController* valve = startClosing(1);
    request->send(200, "text/plain", valve->toString());
}

void handleDrainValveOff(AsyncWebServerRequest *request)
{
    debugI("handleDrainValveOff");
    ValveController* valve = startClosing(2);
    request->send(200, "text/plain", valve->toString());
}

/**
 * valve = 1 --> main valve
 * valve = 2 --> drain valve
 */
void getValveState(String &result, int valve) {
    debugD("getValveState");
    result = "unknown";

    switch (valve)
    {
        case 1:
            result = mainValve->toString();
            break;
        case 2:
            result = drainValve->toString();
            break;
        default:
            debugW("Unknown valve");
            break;
    }
}

void handleMainValveGetState(AsyncWebServerRequest *request)
{
    debugI("handleMainValveGetState");
    String valveState = "";
    getValveState(valveState, 1); // XXX TODO add constant
    request->send(200, "application/json", valveState);
}

void handleDrainValveGetState(AsyncWebServerRequest *request)
{
    debugI("handleDrainValveGetState");
    String valveState = "";
    getValveState(valveState, 2);
    request->send(200, "application/json", valveState);
}

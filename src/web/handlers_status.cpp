#include "handlers_status.h"
#include "utils/debug_utils.h"
#include "blink_task.h"
#include "valves.h"
#include "build.h"

#include "utils/gpio_utils.h"

void handleVersion(AsyncWebServerRequest *request)
{
    debugD("handleVersion");
    request->send(200, "application/json", VERSION_JSON);
}

BlinkTask* statusBlink = NULL;

#include "utils/status_builder.h"

void handleStatus(AsyncWebServerRequest *request)
{
    debugI("handleStatus");
    String hostname = WiFi.hostname();
    int strength = WiFi.RSSI();

    if (statusBlink == NULL) {
        debugV("creatubg blinkTask instance");
        statusBlink = new BlinkTask(&runner);
        statusBlink->disable();
    }

    if (statusBlink->isEnabled()) {
        statusBlink->disable();
    } else {
        statusBlink->setIterations(10);
        statusBlink->enable();
    }


    const size_t capacity = JSON_ARRAY_SIZE(2) + JSON_OBJECT_SIZE(3) + JSON_OBJECT_SIZE(4) + 3*JSON_OBJECT_SIZE(5)+ 172;
    DynamicJsonDocument doc(capacity);

    String output = "";
    generateStatusJson(&doc, mainValve, drainValve);
    serializeJson(doc, output);
    debugI("Serialized to String %s", output.c_str());

    debugD("<---------------------------------------------------------------");
    debugD("%s\nTaskID: %u; interval: %lu; isEnabled: %d; runCounter: %lu; iterations: %ld; %lu;\n",
            "main valve:", mainValve->getId(), mainValve->getInterval(), mainValve->isEnabled(), mainValve->getRunCounter(), mainValve->getIterations(), millis());
    debugD("%s\nTaskID: %u; interval: %lu; isEnabled: %d; runCounter: %lu; iterations: %ld; %lu;\n",
            "drain valve:", drainValve->getId(), drainValve->getInterval(), drainValve->isEnabled(), drainValve->getRunCounter(), drainValve->getIterations(), millis());
    debugD(">---------------------------------------------------------------");

    displayPinModes();

    debugI("status response: %s", output.c_str());
    request->send(200, "text/html", output);
}

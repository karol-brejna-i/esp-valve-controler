#include <Arduino.h>

#include "build.h"
#include "utils/debug_utils.h"
#include "utils/serial_utils.h"
#include "utils/gpio_utils.h"
#include "utils/wifi_utils.h"
#include "web_utils.h"
#include "ts.hpp"

#ifndef WIFI_SSID
#error wifi not defined
#endif

#ifndef WIFI_SSID
#define WIFI_SSID "My ssid name"
#define WIFI_PASS "My password"
#endif

#ifndef DEBUGGER_ENABLED
error "debuger enabled"
#endif

RemoteDebug Debug;

Scheduler runner;
// debug task;
#include "hourglass_task.h"
HourGlassTask *hourglassTask = new HourGlassTask(&runner);

#include "valves.h"
ValveController *mainValve = new ValveController(&runner, "main", MAIN_VALVE_OPEN, MAIN_VALVE_CLOSE, DEFAULT_AUTOSWTICH_INTERVAL, DEFAULT_AUTOSWTICH_INTERVAL);
ValveController *drainValve = new ValveController(&runner, "drain", DRAIN_VALVE_OPEN, DRAIN_VALVE_CLOSE, DEFAULT_AUTOSWTICH_INTERVAL, DEFAULT_AUTOSWTICH_INTERVAL);

void setup()
{
    setupSerial();
    Serial.println("starting the setup process");
#ifdef DEBUG_ON
    Serial.print("Starting..........");
    Serial.println(VERSION_JSON);
#endif

    setupGPIOs();
    setupWiFi(WIFI_SSID, WIFI_PASS);
    setupWebServer();

    String hostname = WiFi.hostname();
    setupDebugger(hostname);

    Serial.println("Setup process finished...");
}

void loop()
{
    runner.execute();
    // delay(10);

    Debug.handle();
    yield();
}
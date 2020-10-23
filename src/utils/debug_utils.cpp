#include "debug_utils.h"
#include "gpio_utils.h"

void setupDebugger(String hostname)
{
    Debug.setResetCmdEnabled(true);
    // Debug.showProfiler(true);
    // Debug.setSerialEnabled(true); // XXX TODO I suspect, that if the serial is on and no device is connected, remotedebug hangs
    Debug.showColors(true);
    Debug.showTime(true);

    Debug.begin(hostname, Debug.INFO);

    String helpCmd = "inputX -- where X is GPIO number (i.e.1, 2, 6, 9, 20) -- set given GPIO to INPUT mode\n";
    helpCmd.concat("outputX -- where X is GPIO number (i.e.1, 2, 6, 9, 20) -- set given GPIO to OUTPUT mode\n");
    helpCmd.concat("setX -- set GPIO's X state to high\n");
    helpCmd.concat("unsetX -- unset GPIO's X state to low\n");
    helpCmd.concat("status -- dump status\n");

    Debug.setHelpProjectsCmds(helpCmd);
    Debug.setCallBackProjectCmds(&processCmdRemoteDebug);
}

void setMode(int pinNo, uint8_t mode)
{
    if (mode != 255)
    {
        debugI("changing pin %d state...", pinNo);
        pinMode(pinNo, mode);
    }
}

#include "status_builder.h"
#include "valves.h"
void processCmdRemoteDebug()
{

    String lastCmd = Debug.getLastCommand();
    debugI("debug command %s", lastCmd.c_str());

    uint8_t mode = 255;
    String pin;
    if (lastCmd.startsWith("input"))
    {
        pin = lastCmd.substring(5);
        int pinNo = pin.toInt();
        mode = INPUT;
        setMode(pinNo, mode);
    }
    else if (lastCmd.startsWith("output"))
    {
        pin = lastCmd.substring(6);
        int pinNo = pin.toInt();
        mode = OUTPUT;
        setMode(pinNo, mode);
    }
    else if (lastCmd.startsWith("set"))
    {
        pin = lastCmd.substring(3);
        int pinNo = pin.toInt();
        digitalWrite(pinNo, HIGH);
    }
    else if (lastCmd.startsWith("unset"))
    {
        pin = lastCmd.substring(5);
        int pinNo = pin.toInt();
        digitalWrite(pinNo, LOW);
    }
    else if (lastCmd.equals("status"))
    {
        debugI("status");
        const size_t capacity = JSON_ARRAY_SIZE(2) + JSON_OBJECT_SIZE(3) + JSON_OBJECT_SIZE(4) + 3*JSON_OBJECT_SIZE(5) + 172;
        DynamicJsonDocument doc(capacity);

        String output = "";
        generateStatusJson(&doc, mainValve, drainValve);
        serializeJson(doc, output);
        debugI("Status: %s", output.c_str());
    }
    else
    {
        debugW("Unrecognized command.");
    }

    debugI("pin %s, mode %u", pin.c_str(), mode);

    displayPinModes();
}

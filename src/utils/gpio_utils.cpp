#include "constants.h"
#include "gpio_utils.h"

#include "utils/debug_utils.h"

void setupGPIOs()
{
    // declare GIOs function
    pinMode(SIGNAL_LED, OUTPUT);

    pinMode(MAIN_VALVE_OPEN,   OUTPUT);
    pinMode(MAIN_VALVE_CLOSE,  OUTPUT);
    pinMode(DRAIN_VALVE_OPEN,  OUTPUT);
    pinMode(DRAIN_VALVE_CLOSE, OUTPUT);


    // set initial state
    digitalWrite(SIGNAL_LED, HIGH);

    digitalWrite(MAIN_VALVE_OPEN,   !VALUE_FOR_ON);
    digitalWrite(MAIN_VALVE_CLOSE,  !VALUE_FOR_ON);
    digitalWrite(DRAIN_VALVE_OPEN,  !VALUE_FOR_ON);
    digitalWrite(DRAIN_VALVE_CLOSE, !VALUE_FOR_ON);
}

void ledOn()
{
    debugD("LEDON");
    digitalWrite(SIGNAL_LED, LOW);
}

void ledOff()
{
    debugD("LEDOFF");
    digitalWrite(SIGNAL_LED, HIGH);
}

void displayPinModes()
{
    debugD("Display pin modes");
    int cnt = 0;
    for (unsigned int pin = 0; pin < 32; pin++)
    {
        uint8_t pinomode = getPinMode((uint8_t)pin);
        if (pinomode == 1)
        {
            debugI("Mode of pin %d is %u", pin, pinomode);
            cnt++;
        }
        int pinmode2 = getPinMode2(pin);
        debugI("Mode2 of pin %d is %d", pin, pinmode2);
    }
    debugI("Output pins cnt %d", cnt);
}

#include <pins_arduino.h>
#define UNKNOWN_PIN 0xFF


int getPinMode2(uint8_t pin)
{
    uint8_t bit = digitalPinToBitMask(pin);
    uint8_t port = digitalPinToPort(pin);
    volatile uint32_t  *reg = portModeRegister(port);

    if (*reg & bit) {
        return OUTPUT;
    } else {
        return INPUT;
    }
}

uint8_t getPinMode(uint8_t pin)
{
    uint8_t bit = digitalPinToBitMask(pin);
    uint8_t port = digitalPinToPort(pin);

    // I don't see an option for mega to return this, but whatever...
    if (NOT_A_PIN == port)
        return UNKNOWN_PIN;

    // Is there a bit we can check?
    if (0 == bit)
        return UNKNOWN_PIN;

    // Is there only a single bit set?
    if (bit & (bit - 1))
        return UNKNOWN_PIN;

    volatile uint32_t *reg, *out;
    reg = portModeRegister(port);
    out = portOutputRegister(port);

    if (*reg & bit)
        return OUTPUT;
    else if (*out & bit)
        return INPUT_PULLUP;
    else
        return INPUT;
}
#define SIGNAL_LED LED_BUILTIN
#define PRESS_DELAY 4000
#define FLASH_DELAY 100

#define MAIN_VALVE_OPEN     D1
#define MAIN_VALVE_CLOSE    D2
#define DRAIN_VALVE_OPEN    D6 //1 //GPIO01 //Tx
#define DRAIN_VALVE_CLOSE   D7 //3 //GPIO03 //Rx

void setupGPIOs();

void blink(int blinkDelay = FLASH_DELAY);

void ledOn();
void ledOff();

#include  <stdint.h>

uint8_t getPinMode(uint8_t pin);
void displayPinModes();
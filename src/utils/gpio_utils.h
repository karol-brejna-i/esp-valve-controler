#define SIGNAL_LED LED_BUILTIN

void setupGPIOs();

void ledOn();
void ledOff();

#include  <stdint.h>

uint8_t getPinMode(uint8_t pin);
int  getPinMode2(uint8_t pin);
void displayPinModes();
#include <msp430.h>
#include "led.h"

void led_init()
{
  P1DIR |= LEDS;		// bits attached to leds are output
  P1OUT &= ~LEDS;               // leds initially off
}

#include <msp430.h>
#include "switches.h"
#include "led.h"


void
__interrupt_vec(WDT_VECTOR) WDT()       /* 250 interrupts/sec */
{
  static int blinkCount = 0;
  blinkCount++;
  switch(counter){
  case 0:
      P1OUT &= ~LED_GREEN;
      P1OUT &= ~LED_RED;
    break;
  case 1:
    if(blinkCount >= 200){
      blinkCount = 0;
      P1OUT ^= LED_GREEN;
      P1OUT &= ~LED_RED;
    }
    break;
  case 2:
    if(blinkCount >= 300){
      blinkCount = 0;
      P1OUT &= ~LED_GREEN;
      P1OUT ^= LED_RED;
    }
    break;
  case 3:
    P1OUT &= ~LEDS;
    if(blinkCount >= 100){
      blinkCount = 0;
      P1OUT ^= LEDS;
    }
  }
}

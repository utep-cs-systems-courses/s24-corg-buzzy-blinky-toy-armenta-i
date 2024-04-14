#include <msp430.h>
#include "switches.h"
#include "led.h"
#include "buzzer.h"

void
__interrupt_vec(WDT_VECTOR) WDT()       /* 250 interrupts/sec */
{
  static char blinkCount = 0;
  if(++blinkCount >= 250){
    state_advance();
    //Do something to know time interrupt happened
  }
}

#include <msp430.h>
#include "libTimer.h"
#include "led.h"
#include "switches.h"
#include "buzzer.h"

void main(void) 
{  
  switch_init();
  led_init();
  configureClocks();            /* setup master oscillator, CPU & peripheral clocks */
  enableWDTInterrupts();        /* enable periodic interrupt */
  buzzer_init();
  // hard coded led call to let the user know it can be used
  flash_both(2);
  
  or_sr(0x18);  // CPU off, GIE on
}


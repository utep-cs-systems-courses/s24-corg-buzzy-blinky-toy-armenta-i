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
  green_on();
  
  or_sr(0x18);  // CPU off, GIE on
}


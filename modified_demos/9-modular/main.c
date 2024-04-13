#include <msp430.h>
#include "libTimer.h"
#include "led.h"
#include "switches.h"

void main(void) 
{  
  switch_init();
  led_init();
  configureClocks();            /* setup master oscillator, CPU & peripheral clocks */
  enableWDTInterrupts();        /* enable periodic interrupt */
    
  or_sr(0x18);  // CPU off, GIE on
}

/* p1_interrupt_handler goes here*/

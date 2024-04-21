#include <msp430.h>
#include "switches.h"
#include "led.h"

int buttonDown, counter;

void switch_init()               /* setup switch*/
{  
  P1REN |= SWITCHES;		/* enables resistors for switches */
  P1IE |= SWITCHES;		/* enable interrupts from switches */
  P1OUT |= SWITCHES;		/* pull-ups for switches */
  P1DIR &= ~SWITCHES;		/* set switches' bits for input */
}

void
switch_interrupt_handler()
{
  char p1val = P1IN;            /* switch is in P1 */

/* update switch interrupt sense to detect changes from current buttons */
  P1IES |= (p1val & SWITCHES);  /* if switch up, sense down */
  P1IES &= (p1val | ~SWITCHES); /* if switch down, sense up */

  if (p1val & SW1) {            /* button up */
    buttonDown = 0;
  } else {                      /* button down */
    buttonDown = 1;
    counter++;
  }

  if(counter > 3){
    counter = 0;
  }
}

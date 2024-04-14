#include <msp430.h>
#include "switches.h"
#include "led.h"
#include "stateMachine.h"

int buttonDown, counter;

void switch_init()               /* setup switches */
{ 
  P1REN |= SW0;		/* enables resistors for SW0 */
  P1IE |= SW0;		/* enable interrupts from SW0 */
  P1OUT |= SW0;		/* pull-ups for SW0 */
  P1DIR &= ~SW0;	/* set SW0 bits for input */

  // Setting up switches for green board
  P2REN |= SWITCHES;    // enables resistors for switches  
  P2IE |= SWITCHES;     // enable interrupts from switches
  P2OUT |= SWITCHES;    // pull-ups for switches
  P2DIR &= ~SWITCHES;   // set switches bits for input
}

char 
switch_zero_update_interrupt_sense()
{
  char p1val = P1IN;
  /* update switch interrupt to detect changes from current buttons */
  P1IES |= (p1val & SW0);	/* if switch up, sense down */
  P1IES &= (p1val | ~SW0);	/* if switch down, sense up */
  return p1val;
}

char 
switch_update_interrupt_sense()
{
  char p2val = P2IN;
  /* update switch interrupt to detect changes from current buttons */
  P2IES |= (p2val & SWITCHES);	/* if switch up, sense down */
  P2IES &= (p2val | ~SWITCHES);	/* if switch down, sense up */
  return p2val;
}

void
switch_interrupt_handler()
{
  char p1val = switch_zero_update_interrupt_sense();            /* switch is in P1 */
  char p2val = switch_update_interrupt_sense();
  

  char sw_zero = (p1val & SW0) ? 0 : SW0;
  char sw_one = (p2val	& SW1) ? 0 : SW1;
  char sw_two = (p2val	& SW2) ? 0 : SW2;
  char sw_three = (p2val & SW3) ? 0 : SW3;
  char sw_four = (p2val	& SW4) ? 0 : SW4;

  if(sw_zero){
    state_advance(1);
  }
  else if(sw_one){
    state_advance(2);
  }
  else if(sw_two){
    state_advance(3);
  }
  else if(sw_three){
    state_advance(4);
  }
  else if(sw_four){
    state_advance(5);
  }
  else{
    state_advance(5);
  }
}

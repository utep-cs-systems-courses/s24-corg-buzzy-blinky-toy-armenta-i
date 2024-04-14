#include <msp430.h>
#include "switches.h"

/* Switches on greenBoard */
void
__interrupt_vec(PORT2_VECTOR) Por_2(){
  if(P2IFG & SWITCHES) {     /* button interrupt? */
    P2IFG &= ~SWITCHES;     /* clear pending sw interrupts*/
  switch_interrupt_handler(); /* single hanler for all switches*/
  }
}

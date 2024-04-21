#include <msp430.h>
#include "stateMachines.h"

void
__interrupt_vec(WDT_VECTOR) WDT(){	/* 250 interrupts/sec */
  static int secondCount = 0;
  secondCount ++;
  if (secondCount >= 250) { 	/* once each sec... */
    secondCount = 0;		/* reset count */
    P1OUT ^= LED_GREEN;		/* toggle green LED */
  }
}

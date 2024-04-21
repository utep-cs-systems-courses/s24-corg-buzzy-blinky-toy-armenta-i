//Alternate LEDs from Off, Green, and Red
#include <msp430.h>
#include "libTimer.h"
#include "led.h"

int main(void) {
  P1DIR |= LEDS;
  P1OUT &= ~LED_GREEN;
  P1OUT |= LED_RED;

  configureClocks();		/* setup master oscillator, CPU & peripheral clocks */
  enableWDTInterrupts();	/* enable periodic interrupt */
  
  or_sr(0x18);		/* CPU off, GIE on */
}

int fstcounter, sndcounter;

void
__interrupt_vec(WDT_VECTOR) WDT()	/* 250 interrupts/sec */
{
  fstcounter++;
  sndcounter++;
  if(fstcounter > 20){
    fstcounter = 0;
    P1OUT ^= LED_GREEN;
  }
  if(sndcounter > 19){
    sndcounter = 0;
    P1OUT ^= LED_RED;
  }
  
} 


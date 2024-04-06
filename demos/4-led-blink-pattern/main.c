//Alternate LEDs from Off, Green, and Red
#include <msp430.h>
#include "libTimer.h"
#include "led.h"

int main(void) {
  P1DIR |= LEDS;
  P1OUT |= LED_GREEN;
  P1OUT |= LED_RED;

  configureClocks();		/* setup master oscillator, CPU & peripheral clocks */
  enableWDTInterrupts();	/* enable periodic interrupt */
  
  or_sr(0x18);			/* CPU off, GIE on */
}

// global state vars that control blinking
int blinkLimit = 10;  // duty cycle = 1/blinkLimit
int blinkCount = 0;  // cycles 0...blinkLimit-1
int secondCount = 0; // state var representing repeating time 0…1s
int thirdCount = 0;
int secondLimit = 10;
int redBright = 0; //To manage brightness of red LED
int greenBright = 0; //To manage brightness of green LED
/*The blink limits such as secondLimit or blinkLimit are the ones that control blinking
  pattern because it increases the duration for which the LED remains on during each cycle.
  Increasing the number makes the blinking slower and likewise.

*/
void
__interrupt_vec(WDT_VECTOR) WDT()	/* 250 interrupts/sec */
{

  // handle blinking 
  blinkCount ++;
  thirdCount ++;
  if (blinkCount >= blinkLimit) { // on for 1 interrupt period
    blinkCount = 0;
    P1OUT |= LED_GREEN;
    
  } else{		          // off for blinkLimit - 1 interrupt periods
    P1OUT &= ~LED_GREEN;
  }

  if (thirdCount >= secondLimit){ //How long it takes until it start to go brighter or dimmer
    thirdCount = 0;
    P1OUT |= LED_RED;
  } else{
    P1OUT &= ~LED_RED;
  }

  // measure a second
  secondCount ++;
  greenBright ++;
  //secound count is in charge of how long it takes for the led to change states and go from dim to bright
  if (greenBright >= 400) {  // once each second
    secondCount = 0;
    greenBright = 0;
    blinkLimit --;           // reduce duty cycle
    
    if (blinkLimit <= 0){     // but don't let duty cycle go below 1/7.
      blinkLimit = 10;
    }
  }

  redBright++;
  if(redBright >= 400){
    redBright = 0;
    secondLimit --;

    if (secondLimit <= 0)
      secondLimit = 10; //The blinking pattern because it increases the duration for which the LED remains on during each cycle.
  }

  secondCount++;
  greenBright++;
  redBright++;
  if(secondCount >= 110){
    secondCount = 0;
    blinkLimit--;

    if (blinkLimit <= 0){     // but don't let duty cycle go below 1/7.                                                                        
      blinkLimit = 10;
    }

    if (secondLimit <= 0){
      secondLimit = 10;
    }
  }
} 


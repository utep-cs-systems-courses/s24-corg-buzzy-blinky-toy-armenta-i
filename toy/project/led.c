#include <msp430.h>
#include "led.h"

void led_init()
{
  P1DIR |= LEDS;		// bits attached to leds are output
  P1OUT &= ~LEDS;               // leds initially off
}

void green_on(){
  P1OUT |= LED_GREEN;
  P1OUT &= ~LED_RED;
}

void turn_red() {
  P1OUT &= ~LED_GREEN;
  for(int i = 0; i < 50; i ++){
    if((i % 2) == 0){
      P1OUT |= LED_RED;
    }
    else{
      P1OUT &= ~LED_RED;
    }
    __delay_cycles(200000);
  }
}

void turn_green() {
  P1OUT	&= ~LED_RED;
  for(int i = 0; i < 50; i ++){
    if((i % 2) == 0){
      P1OUT |= LED_GREEN;
    }
    else{
      P1OUT &= ~LED_GREEN;
    }
  }
}

void turn_both() {
  P1OUT |= LED_GREEN;
  P1OUT |= LED_RED;
}

void turn_both_off(){
  P1OUT &= ~LEDS;
}

void flash_both(){
  P1OUT ^= LEDS;
}


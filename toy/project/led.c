#include <msp430.h>
#include "led.h"

void led_init(){
  P1DIR |= LEDS;		// bits attached to leds are output
  P1OUT &= ~LED_GREEN;               // leds initially off
  P1OUT &= ~LED_RED;
}

//Turns on green led
void green_on(){
  P1OUT ^= LED_GREEN;
  P1OUT &= ~LED_RED;
  __delay_cycles(5000);
}

void red_on(){
  P1OUT ^= LED_RED;
  P1OUT &= ~LED_GREEN;
}

//Flashes red led
void turn_red() {
  for(int i = 0; i < 50; i ++){
    red_on();
    __delay_cycles(500000);
    red_off();
    __delay_cycles(500000);
  }
}

//Flashed green led
void turn_green() {
  P1OUT	&= ~LED_RED;
  for(int i = 0; i < 50; i ++){
    green_on();
    __delay_cycles(500000);
    green_off();
    __delay_cycles(500000);
  }
}

//Turns on both leds
void turn_both() {
  P1OUT |= LED_GREEN;
  P1OUT |= LED_RED;
  __delay_cycles(5000);
}

//Turns both leds off
void turn_both_off(){
  P1OUT &= ~LEDS;
}

void red_off(){
  P1OUT &= ~LED_RED;
}

void green_off(){
  P1OUT &= ~LED_GREEN;
}

//Flashes both on & off
void flash_both(int flashes){
  for(int i = 0; i < flashes; i ++){
    green_on();
    red_on();
    __delay_cycles(500000);
    green_off();
    red_off();
    __delay_cycles(500000);
  }
}

// flashes green then red
void flash_green_red(){
  // green flashes
  for(int i = 0; i < 50; i ++){
    green_on();
    __delay_cycles(500000);
    green_off();
    __delay_cycles(500000);
  }
  //red flashes
  for(int i = 0; i < 50; i ++){
    red_on();
    __delay_cycles(500000);
    red_off();
    __delay_cycles(500000);
  }
}

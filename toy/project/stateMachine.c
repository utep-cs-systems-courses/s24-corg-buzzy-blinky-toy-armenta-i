#include <msp430.h>
#include "switches.h"
#include "led.h"
#include "buzzer.h"
#include "stateMachine.h"

int state_flag = 0;

void state_advance(int state){

  switch(state){
  case 1:
    // flashes green then turns red on
    turn_green();
    __delay_cycles(50000);
    red_on();
    __delay_cycles(5000);
    ode_to_joy();
    turn_both_off();
    __delay_cycles(5000);
    break;
  case 2:
    // flashes both leds
    //flash_both(30);
    
    jingle_bells();
    turn_both_off();
    __delay_cycles(5000);
    break;
  case 3:
    //flashes red led
    turn_red();
    row_your_boat();
    turn_both_off();
    __delay_cycles(5000);
    break;
  case 4:
    // no leds
    runaway();
    __delay_cycles(5000);
    break;
  case 5:
    // flashes green then red then no leds
    flash_green_red();
    twinkle_twinkle();
    __delay_cycles(5000);
    break;
  default:
    green_on();
    break;
  }
}

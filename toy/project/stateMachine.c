#include <msp430.h>
#include "switches.h"
#include "led.h"
#include "buzzer.h"
#include "stateMachine.h"

void state_advance(int state){

  switch(state){
  case 1:
    ode_to_joy();
    turn_green();
    break;
  case 2:
    jingle_bells();
    turn_red();
    break;
  case 3:
    row_your_boat();
    turn_both();
    break;
  case 4:
    old_mc_donald();
    flash_both();
    break;
  case 5:
    twinkle_twinkle();
    turn_both_off();
    break;
  }
}

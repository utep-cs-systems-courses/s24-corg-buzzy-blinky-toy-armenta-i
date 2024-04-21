#include <msp430.h>
#include "stateMachines.h"
#include "led.h"

char toggle_red()		/* always toggle! */
{
  static char state = 0;

  switch (state) {
  case 0:
    red_on = 1;
    state = 1;
    break;
  case 1:
    red_on = 0;
    state = 0;
    break;
  }
  return 1;			/* always changes an led */
}

char toggle_green()	/* only toggle green if red is on!  */
{
  char changed = 0;
  if (!red_on) {
    green_on ^= 1;
    changed = 1;
  }
  return changed;
}

void state_advance()		/* alternate between toggling red & green */
{  

  static enum {GREEN=0, RED=1, BOTH=2, CLEAR=3} state = RED;
  switch (state) {
  case GREEN:
    red_on ^= 0;
    green_on = 1;
    state = RED;
    break;
  case RED:
    red_on = 1;
    green_on = 0;
    state = BOTH;
    break;
  case BOTH:
    red_on = 1;
    green_on = 1;
    state = CLEAR;
    break;
  case CLEAR:
    red_on = 0;
    green_on = 0;
    state = GREEN;
    break;
  }

  led_changed = 1;
  led_update();
}






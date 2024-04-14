#ifndef led_included
#define  led_included

#include <msp430.h>

#define LED_RED BIT0               // P1.0
#define LED_GREEN BIT6             // P1.6
#define LEDS (LED_RED | LED_GREEN)

void led_init();		/* initialize LEDs */
void turn_red();
void turn_green();
void turn_both();
void turn_both_off();
void flash_both();
void green_on();

#endif

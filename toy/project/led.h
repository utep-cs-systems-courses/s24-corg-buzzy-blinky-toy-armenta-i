#ifndef led_included
#define  led_included

#include <msp430.h>

#define LED_RED BIT6               // P1.0
#define LED_GREEN BIT0             // P1.6
#define LEDS (LED_RED | LED_GREEN)

void led_init();		/* initialize LEDs */
void turn_red();
void turn_green();
void turn_both();
void turn_both_off();
void flash_both(int flashes);
void green_on();
void red_on();
void red_off();
void green_off();
void flash_green_red();
void on_ready();

#endif

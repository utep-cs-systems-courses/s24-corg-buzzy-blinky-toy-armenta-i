#ifndef switches_included
#define switches_included


#define SW0 BIT3		// button0 connected to P1 bit 3 
#define SW1 BIT0		// button1 connected to P2 bit 0
#define SW2 BIT1                // button2 connected to P2 bit 1
#define SW3 BIT2                // button3 connected to P2 bit 3
#define SW4 BIT3                // button4 connected to P2 bit 4

#define SWITCHES (SW1 | SW2 | SW3 | SW4)

void switch_init();
void switch_interrupt_handler();

#endif // included

#include <msp430.h>
#include "libTimer.h"
#include "buzzer.h"
#include "musical_notes.h"
#include "led.h"

void buzzer_init()
{
    /* 
       Direct timer A output "TA0.1" to P2.6.  
        According to table 21 from data sheet:
          P2SEL2.6, P2SEL2.7, anmd P2SEL.7 must be zero
          P2SEL.6 must be 1
        Also: P2.6 direction must be output
    */
    timerAUpmode();		/* used to drive speaker */
    P2SEL2 &= ~(BIT6 | BIT7);
    P2SEL &= ~BIT7; 
    P2SEL |= BIT6;
    P2DIR = BIT6;		/* enable output to speaker (P2.6) */
}

void buzzer_set_period(short cycles) /* buzzer clock = 2MHz.  (period of 1k results in 2kHz tone) */
{
  CCR0 = cycles; 
  CCR1 = cycles >> 1;		/* one half cycle */
}

void play_song(int *notes, int *lengths, int num_notes) {
    for (int i = 0; i < num_notes; i++) {
        buzzer_set_period(1000000 / notes[i]);  // Set frequency using clock cycles
	int ms = lengths[i];
	while(ms--){
	  __delay_cycles(10000);
	}
    }
    buzzer_set_period(0);  // Turn off buzzer after song is finished
}

void jingle_bells(){
  int jingle_bells[] =   {E4, E4, E4, ZR, E4, E4, E4, ZR, E4, G4, C4, D4, E4, ZR, F4, F4, F4, F4, F4, ZR, E4, E4, E4, E4, E4, ZR, D4, D4, E4, D4, G4};
  int length_of_note[] = {250, 250, 500, 100, 250, 250, 500, 100, 250, 250, 250, 250, 500, 100,  250, 250, 250, 250, 500, 100, 250, 250, 250, 250, 500, 100, 250, 250, 500, 500, 1000};  // Durations in milliseconds

  // Getting all notes which buzzer will play
  int total_notes = sizeof(jingle_bells) / sizeof(jingle_bells[0]);
  play_song(jingle_bells, length_of_note, total_notes);
  buzzer_set_period(0);
}

void ode_to_joy(){
  int ode_to_joy[] = {E4, E4, F4, G4, G4, F4, E4, D4, C4, C4, D4, E4, E4, D4, D4, E4, E4, F4, G4, G4, F4, E4, D4, C4, C4, D4, E4, D4, C4, C4};
  int length_of_note[] = {500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 1000, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 1000};
  
  int total_notes = sizeof(ode_to_joy) / sizeof(ode_to_joy[0]);
  play_song(ode_to_joy, length_of_note, total_notes);
  
  buzzer_set_period(0);
}

void twinkle_twinkle(){
  int twinkle_twinkle[] = {C4, C4, G4, G4, A4, A4, G4, F4, F4, E4, E4, D4, D4, C4};
  int length_of_note[] = {500, 500, 500, 500, 500, 500, 1000, 500, 500, 500, 500, 500, 500, 1000};

  int total_notes = sizeof(twinkle_twinkle) / sizeof(twinkle_twinkle[0]);
  play_song(twinkle_twinkle, length_of_note, total_notes);
  buzzer_set_period(0);
}

void row_your_boat(){
  int row_your_boat[] = {C4, C4, C4, D4, E4, E4, D4, E4, F4, G4, C5, C5, C5, G4, G4, G4, E4, E4, E4, C4, C4, C4, G4, F4, E4, D4, C4};
  int length_of_note[] = {500, 500, 500, 500, 500, 500, 500, 500, 500, 1000, 500, 500, 1000, 500, 500, 1000, 500, 500, 1000, 500, 500, 1000, 500, 500, 500, 500, 1000};
  
  int total_notes = sizeof(row_your_boat) / sizeof(row_your_boat[0]);
  play_song(row_your_boat, length_of_note, total_notes);
  buzzer_set_period(0);
}

void old_mc_donald(){
  //int old_macdonald[] = {C4, C4, C4, G4, A4, A4, G4, E4, E4, D4, D4, C4};
  int old_macdonald[] = {G4, G4, G4, D4, E4, E4, D4, B4, B4, A4, A4, G4, D4, G4, G4, G4, D4, G4, G4, G4};
  
  int length_of_note[] = {500, 500, 500, 500, 500, 500, 1000, 500, 500, 500, 500, 1000, 500, 500, 500, 500, 500, 500, 500, 1000};
  int total_notes = sizeof(old_macdonald) / sizeof(old_macdonald[0]);
  play_song(old_macdonald, length_of_note, total_notes);
  buzzer_set_period(0);
}

void runaway() {
    // Notes of the melody (simplified, in pseudocode format)
    int runaway_melody[] = {E4, E4, E4, E4, G4, E4, D4, D4, D4, D4, B4, D4, C4, C4, C4, C4, E4, D4};
    int length_of_note[] = {500, 500, 500, 500, 1000, 500, 500, 500, 500, 500, 1000, 500, 500, 500, 500, 500, 1000, 500};

    // Getting all notes which buzzer will play
    int total_notes = sizeof(runaway_melody) / sizeof(runaway_melody[0]);
    play_song(runaway_melody, length_of_note, total_notes);
    buzzer_set_period(0); // Turn off buzzer at the end
}

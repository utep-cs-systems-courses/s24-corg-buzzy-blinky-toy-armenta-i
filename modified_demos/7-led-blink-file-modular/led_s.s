.arch msp430g2553
	.data

red_on:		.byte 0		;red_on = 0
green_on:	.byte 0		;green_on = 0
led_changed:	.byte 0 	;led_changed = 0
redVal:		.byte 0		;redVal = {0, LED_RED}
		.byte LED_RED
greenVal:	.byte 0		;greenVal = {0, LED_GREEN}
		.byte LED_GREEN
	
	
	.text

	.global led_init		; function
	.global led_update		; function
	.global changed
	.extern P1DIR
	.extern P1OUT
	.extern LED_RED
	.extern LED_GREEN

led_init:				;led_init function

	bis &LEDS, &P1DIR		;#64 as LED_GREEN is on bit 6
	mov #1, led_changed		;led_changed = 1
	call led_update			;led_update()
	pop r0
	
led_update:				;led_update function

	ledFlags:	.byte 0 	;ledFlags = 0
	cmp #0, &led_changed		;if(!led_changed)
	jz out
	mov &redVal, r12		;Char* r12 = &redVal
	add &red_on, r12		;r12 += red_on
	mov &greenVal, r13		;Char* r13 = &greenVal
	add &green_on, r13		;r13 += green_on
	bis r13, r12			;r12 |= r13
	mov r12, &ledFlags		;ledFlags = r12

	mov #0xff, r12 			;r12 = 0xff
	xor &LEDS, r12			;r13 ^= LEDS
	bis &ledFlags, r12 		;r12 |= ledFlags
	and r12, &P1OUT			;P1OUT &= r12
	bis &ledFlags, &P1OUT		;P1OUT |= ledFlags
	mov #0, led_changed		;led_changed = 0

out:	
	pop r0				;return

	.arch msp430g2553
	.p2align 1,0
	.text

	.global oncePerSecond
	.global blinkLimit
	.extern P1OUT

blinkLimit:
	.long blinkLimit

oncePerSecond:
	ldr r0, blinkLimit                 //Loading adress of blinkLimit to r0
	ldr r0, [r0]                        //Loading value of blinkLimit into r0 using
	                                    //the adress stored in r0

	add #1, r0 ; blinkLimit++           // reduce duty cycle
	cmp #8, r0 ; if (blinkLimit >= 8)
	jnc nothing ; blinkLimit < 8        // get out of function
	mov #0, r0 ; blinkLimit = 0
	pop r0
	
nothing:
	pop r0
	
	
	

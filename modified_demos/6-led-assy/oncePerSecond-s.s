	.arch msp430g2553
	.p2align 1,0

	.text

	.global oncePerSecond
	.extern blinkLimit	;blinkLimit is an external
	.extern P1OUT

	
oncePerSecond:	
	add #1, &blinkLimit
	cmp #8, &blinkLimit
	jl end 		; if (blinkLimit <= 8)
	mov #0, &blinkLimit	;blinkLimit = 0
	
end:
	pop r0

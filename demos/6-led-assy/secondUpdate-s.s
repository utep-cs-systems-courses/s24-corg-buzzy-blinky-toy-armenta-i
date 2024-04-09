	.arch msp430g2553
	.data
	
	.p2align 1,0
	.text

	.extern @oncePerSecond	;declare oncePerSecond as external function
		;use extern to declare variables declared in other files 

	.global secondUpdate
	.extern @secondCount
	.extern P1OUT

secondUpdate:
	add #1, &secondCount	;secondCount++
	cmp #250, &secondCount	;secondCount >= 250
	jge reset		;if secondCount >= 250

	jmp end			;if secondCount < 250
	
reset:
	mov #0, &secondCount    ;secondCount = 0
	call oncePerSecond      ;oncePerSecond function call
        jmp end
end:
	pop r0

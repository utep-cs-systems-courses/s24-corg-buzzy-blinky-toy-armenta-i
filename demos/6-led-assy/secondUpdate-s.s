	.arch msp430g2553
	.data
	
	.p2align 1,0
	.text

	.extern @oncePerSecond	;declare oncePerSecond as external function
		;use extern to declare variables declared in other files 

	.global secondUpdate
	.extern P1OUT

secondUpdate:
	mov #0, &secondCount
	add #1, &secondCount	;secondCount++
	cmp #250, &secondCount	;secondCount >= 250
	jge reset
	jmp end
	
reset:
	mov #0, &secondCount    ;secondCount = 0
	call oncePerSecond      ;oncePerSecond function call

end:
	ret

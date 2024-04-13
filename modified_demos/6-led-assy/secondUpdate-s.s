	.arch msp430g2553
	.data
	
	.p2align 1,0
	.text

	.extern @oncePerSecond	;declare oncePerSecond as external function
		;use extern to declare variables declared in other files 

	.global secondUpdate
	.extern secondCount

secondUpdate:
	add #1, &secondCount	;secondCount++
	cmp #250, &secondCount	;secondCount >= 250
	jl end		;if secondCount >= 250
	
	mov #0, &secondCount    ;secondCount = 0
	call #oncePerSecond      ;oncePerSecond function call, mov #oncepersecond, r0
end:
	pop r0

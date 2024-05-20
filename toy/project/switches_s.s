	.arch msp430g2553
	.p2align 1,0		        ; set memory boundary of 2 bytes with padding of zeroes
	.text				; code

	.extern state_advance	; func used in stateMachine to change states
	.extern state_flag
	.extern P1IN
	.extern P1REN		; enabling necessary stuff for SW0
	.extern P1IE
	.extern P1OUT
	.extern P1DIR
	.extern P2IN
	.extern	P2REN		; enabling necessary stuff for rest of switches
        .extern	P2IE
        .extern	P2OUT
        .extern	P2DIR
	.global switch_init	; functions
	.global switch_zero_update_interrupt_sense
	.global switch_update_interrupt_sense
	.global switch_interrupt_handler
	

switch_init:			; setup switches
	bis.b #8, &P1REN	; P1REN |= SW0
	bis.b #8, &P1IE		; P1IE |= SW0
	bis.b #8, &P1OUT	; P1OUT |= SW0
	bis.b #8, &P1DIR 	; P1DIR &= ~SW0
	
	bis.b #15, &P2REN	; P1REN |= SWITCHES(Green board)
	bis.b #15, &P2IE	; P2IE |= SWITCHES
	bis.b #15, &P2OUT 	; P2OUT |= SWITCHES
	bic.b #15, &P2DIR	; P2DIR &= ~SWITCHES
	pop r0

switch_zero_update_interrupt_sense:
	sub.b #1, r1		; making space for p1val on stack as its local var
	mov.b &P1IN, 0(r1)	; p1val = P1IN
	and.b #8, 0(r1)		; p1val & SW0
	bis.b 0(r1), &P1IES	; P1IES |= p1val
	mov.b &P1IN, 0(r1)	; p1val = P1IN for second P1IES
	bis.b #~8, 0(r1)	; p1val | ~SW0
	and.b 0(r1), &P1IES	; P1IES &= p1val
	mov.b 0(r1), r12	; to return p1val
	call return_var		; have to get rid of space made on stack and return p1val

switch_update_interrupt_sense:
	sub.b #1, r1		; making space for local var p2val(index 0 of stack(r0))
	mov.b &P2IN, 0(r1)	; p2val = P2IN
	and.b #15, 0(r1)	; p2val & SWITCHES
	bis.b 0(r1), &P2IES	; P2IES |= p2val
	mov.b &P2IN, 0(r1)	; p2val = P2IN again to reset it for second P2IES
	bis.b #~15, 0(r1)	; p2val | ~SWITCHES
	and.b 0(r1), &P2IES 	; P2IES &= p2val
	mov 0(r1), r12		; return p2val which means to put it in register for access
	call return_var 	; have to return p2val and get rid of space made in stack for p2val
	
return_var:
	add #1, r1		; getting rid of space made for local var, moving stack up 1
	jmp end			; return val once everything is finished

switch_interrupt_handler:
	push #get_p1val 				; going to get_p1val after function is finished
	mov #switch_zero_update_interrupt_sense, r0	; putting function into stack to call it
	
get_p1val:
	mov r12, r6					; (variable) temp = p1val
	push #get_p2val					; going to geet_p2val after this func
	mov #switch_update_interrupt_sense, r0 		; putting function into stack to be called 
	
get_p2val:			; will call to get p2val and setup switches
	sub.b #30, r1		; making space on stack for any vars
	mov.b r12, r7		; temp = p2val
	mov r6, 0(r1)		; moving p1val into stack
	mov r7, 2(r1)		; p2val into stack
	jmp all_switches 	; jump to all_switches function

all_switches:
	mov.b 2(r1), r6		; temp = p2val
	and.b #1, r6		; p2val & 1 (1 because switch 1 is bit 0)
	cmp.b #0, r6 		; temp - 0
	jz sw_one		; if temp == 0, button sw_one was pressed goto sw_one
	mov #0, 4(r1) 		; sw_one not pressed(button = 0)
	mov.b 2(r1), r6		; temp = p2val (to restore temp to use it again)
	and.b #2, r6		; p2val & 2(switch 2 which is bit 2)
	cmp.b #0, r6		; temp - 0
	jz sw_two		; if temp == 0, sw_two was pressed
	mov #0, 6(r1)		; sw_two was not pressed (button = 0)
	mov.b 2(r1), r6		; temp = p2val
	and.b #4, r6 		; p2val & 4 (switch 3 is bit 4)
	cmp.b #0, r6		; temp - 0
	jz sw_three		; if temp == 0 button was pressed goto sw_three
	mov #0, 8(r1)		; sw_three was not pressed (button = 0)
	mov.b 2(r1), r6		; temp = p2val
	and.b #8, r6		; p2val & 8 (switch 4 is bit 8)
	cmp.b #0, r6		; temp - 0
	jz sw_four		; if temp == 0 sw_three was pressed goto sw_three
	mov #0, 10(r1)		; sw_four was not pressed (button = 0)
	jmp no_button_handling	; if none of the buttons on green board pressed goto no_button_handling
	jmp restore_switch_stack ; fix stack after using it

sw_one:
	mov.b #2, &state_flag 	; state_flag = 1
	
sw_two:
	mov.b #3, &state_flag
	
sw_three:
	mov.b #4, &state_flag
	
sw_four:
	mov.b #5, &state_flag
	
no_button_handling:
	mov 0(r1), r6 		; temp = p1val
	and.b #0, r6		; temp = p1val & sw0
	cmp.b #0, r5		; temp - 0
	jz sw_zero		; switch on red board pressed

sw_zero:			; switch on red board
	mov.b #1, r12 		; state 1
	call #state_advance 	; state_advance(1)

restore_switch_stack:		; restore space on stack used for all_switches
	add #30, r1		; go back up stack
	jmp end			; jump to end once restored
	
end:
	pop r0
	
	
	


























	









	

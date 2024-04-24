# makfile configuration
COMMON_OBJECTS  = main.o
CPU             = msp430g2553
CFLAGS          = -mmcu=${CPU} -I../h
LDFLAGS		= -L/opt/ti/msp430_gcc/include

#switch the compiler (for the internal make rules)
CC              = msp430-elf-gcc
AS              = msp430-elf-as

all: button.elf project-s.elf

#additional rules for files
button.elf: ${COMMON_OBJECTS} led.o switches.o p1_interrupt_handler.o timer_handler.o buzzer.o stateMachine.o p2_interrupt_handler.o ../lib/libTimer.a
	${CC} ${CFLAGS} ${LDFLAGS} -o $@ $^

project-s.elf: ${COMMON_OBJECTS} switches_s.o 
	${AS} ${CFLAGS} ${LDFLAGS} -o $@ $^ ../lib/libTimer.a

load-c: button.elf 
	msp430loader.sh $^

load-s: project-s.elf
	msp430loader.sh $^

clean:
	rm -f *.o *.elf *.c~ *.h~ *~

main.o: led.h switches.h buzzer.h

switch_handler_s.o: led.h switches.h buzzer.h


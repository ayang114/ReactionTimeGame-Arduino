#include "timer_isr.h"

// custom defines
#define true 1
#define TOTAL_TASKS 3
#define PERIOD_GCD 1000
#define PERIOD_threeLED 1000
#define PERIOD_blinkingLED 1000
#define PERIOD_combineLED PERIOD_GCD


// Timer Flag
unsigned char timerFlag = false;

// task structure
struct task {
 
	unsigned short period;
	unsigned short timeElapsed;

	void ( *tick ) ( void );

};

// global variables
static unsigned char gThreeLED;
static unsigned char gBlinkingLED;
static struct task gTaskSet[ TOTAL_TASKS ];

// all possible states for each state machine
enum States_threeLED { START_threeLED, SHIFT };
enum States_blinkingLED { START_blinkingLED, ON, OFF };
enum States_combineLED { START_combineLED, DISPLAY };

// task function declarations
void tick_threeLED ( void );
void tick_blinkingLED ( void );
void tick_combineLED ( void );
void initializeTasks ( void );
void TimerISR ( void );


//================================================================
int main(void) {
	/* Insert DDR and PORT initializations */
	DDRB = 0xFF; PORTB = 0x00;

	// initialize tasks;
	initializeTasks();

	// initialize timer
	TimerSet( PERIOD_GCD );
	TimerOn();

	// never reach the return statement
    while (1) {
        /* Update inputs vars here (e.g. buttons, potentimeter readings, etc.)*/
        while (!timerFlag);
        timerFlag = 0;
        scheduleTasks();
    }

	return 1;
}


void initializeTasks ( void ) {
	
	// initialize task[0] to threeLEDs task
	gTaskSet[0].period = PERIOD_threeLED;
	gTaskSet[0].timeElapsed = 0;
	gTaskSet[0].tick = tick_threeLED;

	// initialize task[1] to blinkingLED
	gTaskSet[1].period = PERIOD_blinkingLED;
	gTaskSet[1].timeElapsed = 0;
	gTaskSet[1].tick = tick_blinkingLED;

	// initialize task[2] to combineLED
	gTaskSet[2].period = PERIOD_combineLED;
	gTaskSet[2].timeElapsed = 0;
	gTaskSet[2].tick = tick_combineLED;

	return;

}





void tick_threeLED ( void ) {
	static enum States_threeLED state_threeLED = START_threeLED;

	// transitions between states
	switch ( state_threeLED ) { }

	// behavior of each state
	switch ( state_threeLED ) { }

	return;
}


void tick_blinkingLED ( void ) {

    static enum States_blinkingLED state_blinkingLED = START_blinkingLED;

	// transitions between states
	switch ( state_blinkingLED ) { }


	// behavior of each state
	switch ( state_blinkingLED ) { }

	return;
}


void tick_combineLED ( void ) {

	static enum States_combineLED state_combineLED = START_combineLED;

	// transitions between states
	switch ( state_combineLED ) { }

	//behaviors of each state
	switch ( state_combineLED ) { }


	return;
}

void scheduleTasks() {

    for ( int i = 0;  i < TOTAL_TASKS; i++ ) {

		gTaskSet[i].timeElapsed += PERIOD_GCD;
		
		if( gTaskSet[i].timeElapsed >= gTaskSet[i].period ) {
			gTaskSet[i].tick();
			gTaskSet[i].timeElapsed = 0;
		}
	}

	return;

}

void TimerISR ( void ) {

    timerFlag != timerFlag;

}


ISR ( TIMER1_COMPA_vect ) {
	_avr_timer_cntcurr--;
	if ( _avr_timer_cntcurr == 0 ) {
		TimerISR();
		_avr_timer_cntcurr = _avr_timer_M;
	}
}




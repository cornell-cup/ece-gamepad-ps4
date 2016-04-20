#include <stdint.h>

// Add pthread to linker (gcc manual compilation) or library (eclipse)

#define MAX_CONNECTION_ATTEMPTS	10

#define GAMEPAD_EVENT_FILENAME "/dev/input/event2"

// Event structure
typedef struct
{
	int type;
	int value;
	uint64_t count;
} event_t;

int gp_init(void);
void gp_quit(void);
void* gp_getEvent(void* args);

volatile event_t gp_event;

//===================================================================
// 	BUTTON PRESS DEFINITIONS
//===================================================================
// Do not change the definitions below for a PS4 controller
//===================================================================
#define GP_BTN			1
#define GP_ABS			3


// event codes for button press
#define BTN_SQUARE 		0x130
#define BTN_CROSS 		0x131
#define BTN_CIRCLE 		0x132
#define BTN_TRIANGLE 	0x133
#define BTN_LB 			0x134
#define BTN_RB 			0x135
#define BTN_LT 			0x136
#define BTN_RT 			0x137
#define BTN_SHARE 		0x138
#define BTN_OPTIONS 	0x139
#define BTN_LSTICK 		0x13a
#define BTN_RSTICK 		0x13b
#define BTN_PS 			0x13c
#define BTN_TOUCHPAD 	0x13d

// event codes for absolute axes
#define LEFT_ANALOG_X	0
#define LEFT_ANALOG_Y	1
#define RIGHT_ANALOG_X	2
#define RIGHT_ANALOG_Y	5
#define LEFT_BUMPER		3
#define RIGHT_BUMPER	4
#define DIGITAL_X		16
#define DIGITAL_Y		17
//===================================================================

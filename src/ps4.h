#include "mraa.h"

typedef enum {false, true} boolean;

typedef unsigned char byte;
#define MAXCHAR ((char)0x7f)
#define MAXSHORT ((short)0x7fff)
// Max pos 32-bit int.
#define MAXINT ((int)0x7fffffff)
#define MAXLONG ((long)0x7fffffff)
#define MINCHAR ((char)0x80)
#define MINSHORT ((short)0x8000)

// Max negative 32-bit integer.
#define MININT ((int)0x80000000)
#define MINLONG ((long)0x80000000)

#define GP_BTN			1
#define GP_ABS			3

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
#define MAXEVENTS 		64

#define LEFT_ANALOG_X	0
#define LEFT_ANALOG_Y	1
#define RIGHT_ANALOG_X	2
#define RIGHT_ANALOG_Y	5
#define LEFT_BUMPER		3
#define RIGHT_BUMPER	4

// Event structure
typedef struct
{
	int type;
	int value;
} event_t;

int gp_init(void);
void gp_quit(void);
void* gp_getEvent(void* args);

volatile event_t gp_event;


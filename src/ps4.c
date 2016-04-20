#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <sys/time.h>
#include <unistd.h>
#include <fcntl.h>
#include <linux/input.h> // SUPER IMPORTANT - FOR EVENTS
#include "ps4.h"

#include <pthread.h>

const char* gamepadName = "/dev/input/event2";
volatile int gamepad = -1;

int gp_init(void)
{
	fprintf(stdout, "Attempting to connect to gamepad!\n");
	do {
		gamepad = open(gamepadName, O_RDONLY | O_NONBLOCK);
		//if (gamepad < 0)
		//fprintf(stderr, "Cannot access gamepad at %s\n", gamepadName);
	} while (gamepad < 0);

	fprintf(stdout, "Connection to gamepad successful!\n");

	fprintf(stdout, "Attempting to setup gamepad event handler\n");

	pthread_t gp_thread;
	if (pthread_create(&gp_thread, NULL, gp_getEvent, NULL)){
		fprintf(stdout, "Couldn't set up pthread\n");
		return -1;
	}
	else{
		fprintf(stdout, "Set up pthread!\n");
		return 0;
	}
}

void gp_quit(void)
{
	if (gamepad >= 0)
		close(gamepad);
}

void* gp_getEvent(void* args)
{
	struct input_event event;
	int ev_size = sizeof(ev_size);
	while (1){
		if (read(gamepad, &event, ev_size) < ev_size) 	continue;

		// Only care about 2 types of events: button press and axis absolute change
		gp_event.type = event.code;
		if (event.type == GP_BTN){
			gp_event.value = 1;
		}
		else if (event.type == GP_ABS){
			gp_event.value = event.value;
		}

	}
}

/* HAT0X -> DIGITAL L/R
 * HAT0Y -> DIGITAL U/D
 * ABS_RX -> L2 (3)
 * ABS_RY -> R2 (4)
 * ABS_RZ -> RIGHT ANALOG -> 0 AT TOP, 255 AT BOTTOM, SAME VALUE GOING CW/CCW FROM TOP TO BOTTOM
 * 		THIS MEANS THAT ABS_RZ IS THE Y OF THE RIGHT ANALOG STICK (5)
 * ABS_X -> LEFT ANALOG -> 0 AT LEFT, 255 AT RIGHT, SAME VALUE GOING CW/CCW FROM LEFT TO RIGHT
 * 		THIS MEANS THAT ABS_X IS THE X OF THE LEFT ANALOG STICK (0)
 * ABS_Y -> LEFT ANALOG -> 0 AT TOP, 255 AT BOTTOM, SAME VALUE GOING CW/CCW FROM TOP TO BOTTOM
 * 		THIS MEANS THAT ABS_Y IS THE Y OF THE LEFT ANALOG STICK (1)
 * ABS_Z -> RIGHT ANALOG -> 0 AT LEFT, 255 AT RIGHT, SAME VALUE GOING CW/CCW FROM LEFT TO RIGHT
 * 		THIS MEANS THAT ABS_Z IS THE X OF THE RIGHT ANALOG STICK (2)
 *
 */

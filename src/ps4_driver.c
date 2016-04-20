#include "ps4_driver.h"

#include <fcntl.h>
#include <linux/input.h> // SUPER IMPORTANT - FOR EVENTS
#include "mraa.h"
#include <pthread.h>
#include <unistd.h>

const char* gamepadName = GAMEPAD_EVENT_FILENAME;
volatile int gamepad = -1;

uint64_t gp_counter = 0;

int gp_init(void)
{
	int num_attempts = 0;
	do {
		gamepad = open(gamepadName, O_RDONLY | O_NONBLOCK);
		num_attempts++;
		usleep(500000); // 500ms retry delay
	} while (gamepad < 0 && num_attempts < MAX_CONNECTION_ATTEMPTS);

	if (num_attempts >= MAX_CONNECTION_ATTEMPTS){
		fprintf(stderr, "Couldn't connect to gamepad - check bluetooth connection!\n");
		return -2;
	}

	pthread_t gp_thread;
	if (pthread_create(&gp_thread, NULL, gp_getEvent, NULL)){
		fprintf(stderr, "Couldn't set up pthread\n");
		return -1;
	}

	return 0;
}

void gp_quit(void)
{
	if (gamepad >= 0)
		close(gamepad);
}

void* gp_getEvent(void* args)
{
	struct input_event event;
	int ev_size;
	ev_size = sizeof(event);
	while (1){
		// Should read ev_size bytes. If not, incorrect read and try again.
		if (read(gamepad, &event, ev_size) < ev_size) 	continue;

		// Only care about 2 types of events: button press and axis absolute change
		if (event.type != GP_BTN && event.type != GP_ABS) 	continue;

		gp_event.type = event.code;
		gp_event.count = gp_counter++;

		if (event.type == GP_BTN){
			gp_event.value = 1;
		}
		else if (event.type == GP_ABS){
			int ecode = event.code;
			if (ecode == LEFT_ANALOG_X || ecode == RIGHT_ANALOG_X)
				gp_event.value = event.value - 128; // center on 0, -ve to left, +ve to right
			else if (ecode == LEFT_ANALOG_Y || ecode == RIGHT_ANALOG_Y)
				gp_event.value = 128 - event.value; // center on 0, -ve to bottom, +ve to top
			else if (ecode == DIGITAL_Y)
				gp_event.value = -event.value;
			else
				gp_event.value = event.value;
		}

	}
}


/* ABS_HAT0X -> DIGITAL L/R
 * ABS_HAT0Y -> DIGITAL U/D
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

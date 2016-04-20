/*
  * Author: Syed Tahmid Mahbub <sm893@cornell.edu>
 */

#include "mraa.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "ps4.h"

int main()
{

	system("rfkill unblock all\n");

	// Hold SHARE and PS buttons together for 3-5 seconds until white light strobes to enter pairing mode
	// Then use bluetoothctl to pair, trust and connect

	// Assume that PS4 controller is already paired and connected
	if (gp_init()){ // Initialize gamepad control
		fprintf(stderr, "Error ... exiting program!\n");
		return -1;
	}

	uint64_t oldcount = 0;
	while (1)
	{
		if (oldcount != gp_event.count){
			printf("code = %d, value = %d\n", gp_event.type, gp_event.value);
			oldcount = gp_event.count;
		}
	}

	gp_quit();

	return MRAA_SUCCESS;
}

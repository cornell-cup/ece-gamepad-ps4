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

	// Assume that PS4 controller is already paired and connected
	if (gp_init()){ // Initialize gamepad control
		return -1;
	}

	while (1)
	{

	}

	gp_quit();


	pthread_exit(NULL);
	return MRAA_SUCCESS;
}

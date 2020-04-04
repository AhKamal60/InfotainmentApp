/*
 * app.c
 *
 *  Created on: Jan 7, 2020
 *      Author: H
 */
#include "Game.h"


int main (void)
{
	SOS_Init(5);
	SOS_Create(1,TASK_FUNCTIONALITY_PERIODIC,&GameRoll,0);
	while(1)
	{
		SOS_Schedular();
	}
}


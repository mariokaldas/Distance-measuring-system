/*
 * ultraSonic.c
 *
 *  Created on: Oct 15, 2023
 *      Author: mario
 */

#include"ultraSonic.h"
#include"MCAL/ICU.h"
#include"MCAL/gpio.h"
#include<util/delay.h>

/****************************************************************************
 *                           Global variables
 * *************************************************************************/

ICU_configType ICU_configrations = {FACTOR8,RISING};

uint8 volatile static g_edgeCount=0;
uint16 volatile static g_widthOfEcho;

/****************************************************************************
 *                         Function definition
 * *************************************************************************/

void ULTRASONIC_init(void){

	ICU_init(&ICU_configrations);/* Initializing ICU witch adjusted configurations */
	ICU_setCallBack(ULTRASONIC_edgeProcessing);/* Determining call back function */
	GPIO_setupPinDirection(ULTRASONIC_TRIGGER_PORT,ULTRASONIC_TRIGGER_PIN,PIN_OUTPUT); /* Make trigger pin output */

}

void ULTRASONIC_trigger(void){

	/* Generate Pulse 10us  and wait for echo*/
	GPIO_writePin(ULTRASONIC_TRIGGER_PORT,ULTRASONIC_TRIGGER_PIN,HIGH);
	_delay_us(10);
	GPIO_writePin(ULTRASONIC_TRIGGER_PORT,ULTRASONIC_TRIGGER_PIN,LOW);
}

uint16 ULTRASONIC_readDistance(void){

	uint16 distance;

	ULTRASONIC_trigger();

	/*
	 * Distance = Time * speed ( sonic speed )
	 *          = Time * 34000(cm/s) / 2
	 *
	 *          = 1*10^-6 * 17000 * value of ICU
	 *
	 *          = 0.017 * value of ICU
	 */

	distance = (uint16)( (float)0.017 * g_widthOfEcho);
	return distance;
}

void ULTRASONIC_edgeProcessing(void){

	g_edgeCount++;

	if(g_edgeCount == 1){

		/* to start counting with known value */
		ICU_clearTimer();
		/* Detect falling edge to determine echo width */
		ICU_setEdgeDetectionType(FALLING);
	}
	else if(g_edgeCount == 2){

		/* Got width of echo ( Time ) */
		g_widthOfEcho=ICU_getInputCaptureValue();

		/* To begin again */
		g_edgeCount = 0;
		ICU_setEdgeDetectionType(RISING);
	}
}

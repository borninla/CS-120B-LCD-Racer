/*
 * joystick.c
 *
 * Created: 8/27/2018 12:39:13 PM
 *  Author: Andrew
 */

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include "joystick.h"
#include "io.h"

void ADC_init() {
	ADCSRA |= (1 << ADEN) | (1 << ADSC) | (1 << ADATE);
	// ADEN: setting this bit enables analog-to-digital conversion.
	// ADSC: setting this bit starts the first conversion.
	// ADATE: setting this bit enables auto-triggering. Since we are
	// in Free Running Mode, a new conversion will trigger whenever
	// the previous conversion completes.
}

void wait(long numOP) {
	for( long i = 0; i < numOP; i++){
		asm("nop");
	}
}

void joystickTest() {
	unsigned char temp_array[100];
	
	LCD_DisplayString(1, "X:");
	LCD_DisplayString_NoClear(3, LCD_To_String(coords[0], temp_array, 5));
	LCD_DisplayString_NoClear(17, "Y:");
	LCD_DisplayString_NoClear(19, LCD_To_String(coords[1], temp_array, 5));
}

void fetchAnalogStick() {
	unsigned short val1;
	unsigned short val2;
	
	ADMUX = REF_AVCC | 0x00;
	wait(300);
	val1 = ADC;
	ADMUX = REF_AVCC | 0x01;
	wait(300);
	val2 = ADC;
	
	coords[0] = val1;
	coords[1] = val2;
}
/*
 * main.c
 */

#include <stdbool.h>
#include <stdint.h>

#include "datetime/datetime.h"

#include "driverlib/sysctl.h"
#include "driverlib/systick.h"

uint64_t millis;

uint32_t _year, _month, _day, _hour, _minute, _second;

void SysTickIntHandler()
{
	millis++;
}

void SysTickBegin()
{
    //
    // Set up the period for the SysTick timer.  The SysTick timer period will
    // be equal to the system clock / 10, resulting in a period of 100 ms.
    //
    SysTickPeriodSet(SysCtlClockGet() / 1000);

    //
    // Enable the SysTick Interrupt.
    //
    SysTickIntEnable();

    //
    // Enable SysTick.
    //
    SysTickEnable();
}

void main(void) {
	
	//
	// Set the clocking to run from the PLL at 80MHz
	//
	SysCtlClockSet(SYSCTL_SYSDIV_2_5 | SYSCTL_USE_PLL | SYSCTL_OSC_MAIN |
			SYSCTL_XTAL_16MHZ);

	SysTickBegin();

	setTimeFromParts(2016,5,17,21,13,30);

	while(1)
	{
		 _year = yearNow();
		 _month = monthNow();
		 _day = dayNow();
		 _hour = hourNow();
		 _minute = minuteNow();
		 _second = secondNow();
	}
}

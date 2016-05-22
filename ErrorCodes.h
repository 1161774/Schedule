/*
 * ErrorCodes.h
 *
 *  Created on: 20 May 2016
 *      Author: Bowmer
 */

#ifndef ERRORCODES_H_
#define ERRORCODES_H_

/*sInitDay id, sInitRelative ir, sInitWeekday iw, sInitMonth im, uint8_t hour, uint8_t minute, sAmpm ap, uint16_t freq, sRepeatFreq rf*/
//	1				2					3				4			5				6				7			8			9

#define INVALID_THIS		200
#define	INVALID_HOUR		500
#define	INVALID_MINUTE		600
#define HOUR_AMPM_MISMATCH	700
#define	INVALID_RF_FREQ		900

#endif /* ERRORCODES_H_ */

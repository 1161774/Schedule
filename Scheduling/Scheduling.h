/*
 * Scheduling.h
 *
 *  Created on: 18 May 2016
 *      Author: Bowmer
 */

#ifndef SCHEDULING_SCHEDULING_H_
#define SCHEDULING_SCHEDULING_H_

#include <stdbool.h>
#include <stdint.h>
#include "../datetime/datetime.h"

#endif /* SCHEDULING_SCHEDULING_H_ */


typedef enum
{
	oneShot,
	immediate,
	calendar
} repeatStyle;


typedef struct
{
	time_t		StartTime;
	time_t		EndTime;
	uint16_t	DurationElapsed;
	bool		IsPeriodic;
	time_t		RepeatFrequency;
	repeatStyle	RepeatStyle;
} Schedule;

extern	void createSchedule(Schedule *s, time_t startTime, time_t endTime, time_t isPeriodic, time_t frequency);

extern	void setStartTime(Schedule *s, time_t t, bool isPeriodic);
extern	void setStartTimeFromParts(Schedule *s, uint32_t year, uint32_t month, uint32_t day, uint32_t hour, uint32_t minute, uint32_t second);
extern	void setStartTimeFromNow(Schedule *s, int32_t t);
extern	void setStartTimeNow(Schedule *s);

extern	void setEndTime(Schedule *s, time_t t);
extern	void setEndTimeFromParts(Schedule *s, uint32_t year, uint32_t month, uint32_t day, uint32_t hour, uint32_t minute, uint32_t second);
extern	void setEndTimeFromNow(Schedule *s, int32_t t);
extern	void setEndTimeNow(Schedule *s);

extern	void setPeriodic(Schedule *s, bool isPeriodic);
extern	uint16_t updateElapsedTime(Schedule *s);

extern	void ackSchedule(Schedule *s);

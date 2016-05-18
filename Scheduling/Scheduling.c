/*
 * Header.c
 *
 *  Created on: 18 May 2016
 *      Author: Bowmer
 */


#include "scheduling.h"

void createSchedule(Schedule *s, time_t startTime, time_t endTime, time_t isPeriodic, time_t frequency)
{
	setStartTime(s, startTime, isPeriodic);
	setEndTime(s, endTime);
}

void setStartTime(Schedule *s, time_t t, bool isPeriodic)
{
	s->StartTime = t;
	s->IsPeriodic = isPeriodic;
	if(s->EndTime > 0)
	{
		s->DurationElapsed = updateElapsedTime(s);
	}
	else
	{
		s->DurationElapsed = 0;
	}
}

void setStartTimeFromParts(Schedule *s, uint32_t year, uint32_t month, uint32_t day, uint32_t hour, uint32_t minute, uint32_t second)
{
	setStartTime(s, getTimeFromParts(year, month, day, hour, minute, second), s->IsPeriodic);
}

void setStartTimeFromNow(Schedule *s, int32_t t)
{
	setStartTime(s, now() + t, s->IsPeriodic);
}

void setStartTimeNow(Schedule *s)
{
	setStartTime(s, now(), s->IsPeriodic);
}



void setEndTime(Schedule *s, time_t t)
{
	s->EndTime = t;
	if(s->StartTime > 0)
	{
		s->DurationElapsed = updateElapsedTime(s);
	}
	else
	{
		s->DurationElapsed = 0;
	}
}

void setEndTimeFromParts(Schedule *s, uint32_t year, uint32_t month, uint32_t day, uint32_t hour, uint32_t minute, uint32_t second)
{
	setEndTime(s, getTimeFromParts(year, month, day, hour, minute, second));
}

void setEndTimeFromNow(Schedule *s, int32_t t)
{
	setEndTime(s, now() + t);
}

void setEndTimeNow(Schedule *s)
{
	setEndTime(s, now());
}

void setPeriodic(Schedule *s, bool isPeriodic)
{
	s->IsPeriodic = isPeriodic;
}

uint16_t updateElapsedTime(Schedule *s)
{
	if(s->StartTime > 0 && s->EndTime > 0)
	{
		if(s->EndTime < s->StartTime)
		{
			s->DurationElapsed = UINT16_MAX;
		}
		else
		{
			uint64_t n = now() - s->StartTime;
			s->DurationElapsed = (n * UINT16_MAX) / (s->EndTime - s->StartTime);
		}
	}
	else
	{
		s->DurationElapsed = 0;
	}

	return s->DurationElapsed;
}

void ackSchedule(Schedule *s)
{
	if(s->IsPeriodic)
	{
		time_t delta = s->EndTime - s->StartTime;
		s->StartTime = s->EndTime;
		s->EndTime += delta;
		updateElapsedTime(s);
	}
	else
	{
		s->StartTime = 0;
		s->EndTime = 0;
		s->DurationElapsed = 0;
	}
}

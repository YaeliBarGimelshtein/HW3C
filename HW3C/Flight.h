#pragma once
#ifndef __FLIGHT__
#define __FLIGHT__

#include "AirportManager.h"
#include "Date.h"
#include "General.h"

typedef struct
{
	char		originCode[CODE_LENGTH + 1];
	char		destCode[CODE_LENGTH + 1];
	int			hour;
	Date		date;
}Flight;

void	initFlight(Flight* pFlight, const AirportManager* pManager);
int		initFlightFromFile(Flight* pFlight, FILE* fp);
int		isFlightInRoute(const Flight* pFlight, const char* codeSource, const char* codeDest);
int		countFlightsInRoute(Flight** arr, int size, const char* codeSource, const char* codeDest);
void	printFlight(const void* pFlight);
int		getFlightHour();
Airport*	setAiportToFlight(const AirportManager* pManager, const char* msg);
void	freeFlight(void* pFlight);
int compareFlightsbyHour(const void* o1, const void* o2);
int compareFlightsByDestCode(const void* o1, const void* o2);
int compareFlightsByOriginCode(const void* o1, const void* o2);
int compareFlightsByDate(const void* o1, const void* o2);
void writeFlightToFile(Flight* flight, FILE* fp);

#endif

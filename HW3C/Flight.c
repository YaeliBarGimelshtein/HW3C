#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Flight.h"


void	initFlight(Flight* pFlight, const AirportManager* pManager)
{
	Airport* pPortOr = setAiportToFlight(pManager, "Enter code of origin airport:");
	strcpy(pFlight->originCode, pPortOr->code);
	int same;
	Airport* pPortDes;
	do {
		pPortDes = setAiportToFlight(pManager, "Enter code of destination airport:");
		same = isSameAirport(pPortOr, pPortDes);
		if (same)
			printf("Same origin and destination airport\n");
	} while (same);
	strcpy(pFlight->destCode, pPortDes->code);
	getCorrectDate(&pFlight->date);
	pFlight->hour = getFlightHour();
}

int	isFlightInRoute(const Flight* pFlight, const char* codeSource, const char* codeDest)
{
	if ((strcmp(pFlight->originCode, codeSource) == 0) &&
		(strcmp(pFlight->destCode, codeDest) == 0))
		return 1;

	return 0;
}

int	countFlightsInRoute(Flight** arr, int size, const char* codeSource,
	const char* codeDest)
{
	int count = 0;
	for (int i = 0; i < size; i++)
	{
		if (isFlightInRoute(arr[i], codeSource, codeDest))
			count++;
	}
	return count;
}

void	printFlight(const Flight* pFlight)
{
	printf("Flight From %s To %s\t", pFlight->originCode, pFlight->destCode);
	printDate(&pFlight->date);
	printf("Hour: %d\n", pFlight->hour);
}


int getFlightHour()
{
	int h;
	do {
		printf("Enter flight hour [0-23]:\t");
		scanf("%d", &h);
	} while (h < 0 || h>23);
	return h;
}

Airport* setAiportToFlight(const AirportManager* pManager, const char* msg)
{
	char code[MAX_STR_LEN];
	Airport* port;
	do
	{
		printf("%s\t", msg);
		myGets(code, MAX_STR_LEN);
		port = findAirportByCode(pManager, code);
		if (port == NULL)
			printf("No airport in this country - try again\n");
	} while (port == NULL);

	return port;

}

void	freeFlight(Flight* pFlight)
{
	free(pFlight);
}

int compareFlightsbyHour(const void* o1, const void* o2)
{
	Flight* pFlight1 = *(Flight**)o1;
	Flight* pFlight2 = *(Flight**)o2;

	if (pFlight1->hour > pFlight2->hour)
		return 1;

	if (pFlight1->hour == pFlight2->hour)
		return 0;

	return -1;
}

int compareFlightsByDestCode(const void* o1, const void* o2)
{
	Flight* pFlight1 = *(Flight**)o1;
	Flight* pFlight2 = *(Flight**)o2;
	return strcmp(pFlight1->destCode, pFlight2->destCode);
}

int compareFlightsByOriginCode(const void* o1, const void* o2)
{
	Flight* pFlight1 = *(Flight**)o1;
	Flight* pFlight2 = *(Flight**)o2;
	return strcmp(pFlight1->originCode, pFlight2->originCode);
}

int compareFlightsByDate(const void* o1, const void* o2)
{
	Flight* pFlight1 = *(Flight**)o1;
	Flight* pFlight2 = *(Flight**)o2;

	if (pFlight1->date.day == pFlight2->date.day && pFlight1->date.month == pFlight2->date.month && pFlight1->date.year == pFlight2->date.year)
		return 0;
	if (pFlight1->date.year > pFlight2->date.year)
		return 1;
	else if(pFlight1->date.year < pFlight2->date.year)
		return -1;
	else if (pFlight1->date.month > pFlight2->date.month)
		return 1;
	else if(pFlight1->date.month < pFlight2->date.month)
		return -1;
	else if (pFlight1->date.day > pFlight2->date.day)
		return 1;

	return -1;
}
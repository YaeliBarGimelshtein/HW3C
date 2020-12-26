#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Company.h"
#include "Airport.h"
#include "General.h"

void	initCompany(Company* pComp)
{
	printf("-----------  Init Airline Company\n");
	pComp->name = getStrExactName("Enter company name");
	pComp->flightArr = NULL;
	pComp->flightCount = 0;
	L_init(&pComp->allDates);
	pComp->sorted = eNotSorted;
}

int	addFlight(Company* pComp, const AirportManager* pManager)
{
	if (pManager->count < 2)
	{
		printf("There are not enoght airport to set a flight\n");
		return 0;
	}
	pComp->flightArr = (Flight**)realloc(pComp->flightArr, (pComp->flightCount + 1) * sizeof(Flight*));
	if (!pComp->flightArr)
		return 0;
	pComp->flightArr[pComp->flightCount] = (Flight*)calloc(1, sizeof(Flight));
	if (!pComp->flightArr[pComp->flightCount])
		return 0;
	initFlight(pComp->flightArr[pComp->flightCount], pManager);
	pComp->flightCount++;

	if (pComp->flightCount>1)
	{
		for (int i = 0; i < pComp->flightCount-1; i++)
		{
			if (compareDate(&pComp->flightArr[pComp->flightCount - 1]->date, &pComp->flightArr[i]->date) == 0)
				return 1;
		}
	}
	L_insert(&pComp->allDates.head, &pComp->flightArr[pComp->flightCount-1]->date);
	

	return 1;
}

void printCompany(const Company* pComp)
{
	printf("Company %s:\n", pComp->name);
	printf("Has %d flights\n", pComp->flightCount);
	printFlightArr(pComp->flightArr, pComp->flightCount);
	printf("The filgts that are not repetetive are on dates:\n");
	L_print(&pComp->allDates, printDate);
}

void printFlightsCount(const Company* pComp)
{
	char codeOrigin[CODE_LENGTH + 1];
	char codeDestination[CODE_LENGTH + 1];

	if (pComp->flightCount == 0)
	{
		printf("No flight to search\n");
		return;
	}

	printf("Origin Airport\n");
	getAirportCode(codeOrigin);
	printf("Destination Airport\n");
	getAirportCode(codeDestination);

	int count = countFlightsInRoute(pComp->flightArr, pComp->flightCount, codeOrigin, codeDestination);
	if (count != 0)
		printf("There are %d flights ", count);
	else
		printf("There are No flights ");

	printf("from %s to %s\n", codeOrigin, codeDestination);
}



void	printFlightArr(Flight** pFlight, int size)
{
	for (int i = 0; i < size; i++)
		printFlight(pFlight[i]);
}

void	freeFlightArr(Flight** arr, int size)
{
	for (int i = 0; i < size; i++)
	{
		freeFlight(arr[i]);
	}
}

void	freeCompany(Company* pComp)
{
	freeFlightArr(pComp->flightArr, pComp->flightCount);
	free(pComp->flightArr);
	free(pComp->name);
	L_free(&pComp->allDates,NULL);
}

void	sortByWithComp(Company* pComp, int(*compareFunc)(const void*, const void*))
{
	qsort(pComp->flightArr, pComp->flightCount, sizeof(Flight*), compareFunc);
}


void	sortBy(Company* pComp)
{
	printf("press 1 to sort by hour, press 2 to sort by date, press 3 to sort by destenstion, press 4 to sort by origin\n");
	int choise;
	scanf("%d", &choise);
	
	switch (choise)
	{
	case eHourSort:
		sortByWithComp(pComp, compareFlightsbyHour);
		pComp->sorted = eHourSort;
		printf("finished sorting\n");
		break;

	case eDateSort:
		sortByWithComp(pComp, compareFlightsByDate);
		pComp->sorted = eDateSort;
		printf("finished sorting\n");
		break;

	case eDestenationCodeSort:
		sortByWithComp(pComp, compareFlightsByDestCode);
		pComp->sorted = eDestenationCodeSort;
		printf("finished sorting\n");
		break;

	case eOriginCodeSort:
		sortByWithComp(pComp, compareFlightsByOriginCode);
		pComp->sorted = eOriginCodeSort;
		printf("finished sorting\n");
		break;

	default:
		printf("not a valid option\n");
		break;
	}
}

Flight**	findFlight(Flight* key,Company* pComp, int(*compareFunc)(const void*, const void*))
{
	return (Flight**) bsearch(&key,pComp->flightArr,pComp->flightCount,sizeof(Flight*),compareFunc);
}


void	searchBy(Company* pComp, AirportManager* pPort)
{
	if (pComp->sorted == eNotSorted)
	{
		printf("cant search an un sorted array\n");
		return;
	}

	printf("enter the flight you are lokking for:\n");
	Flight* flightToSearch=(Flight*)malloc(1*sizeof(Flight));
	if (!flightToSearch)
	{
		printf("problem loading flight\n");
		return;
	}
		
	initFlight(flightToSearch, pPort);

	Flight** answer;
	
	switch (pComp->sorted)
	{
	case eHourSort:
		answer = findFlight(flightToSearch,pComp, compareFlightsbyHour);
		if (!answer)
			printf("flight not found\n");
		else
		{
			printf("here is your flight\n");
			printFlight(*answer);
		}
		
		break;

	case eDateSort:
		answer = findFlight(flightToSearch, pComp, compareFlightsByDate);
		if (!answer)
			printf("flight not found\n");
		else
		{
			printf("here is your flight\n");
			printFlight(*answer);
		}
		
		break;

	case eDestenationCodeSort:
		answer = findFlight(flightToSearch, pComp, compareFlightsByDestCode);
		if (!answer)
			printf("flight not found\n");
		else
		{
			printf("here is your flight\n");
			printFlight(*answer);
		}
		break;

	case eOriginCodeSort:
		answer = findFlight(flightToSearch, pComp, compareFlightsByOriginCode);
		if (!answer)
			printf("flight not found\n");
		else
		{
			printf("here is your flight\n");
			printFlight(*answer);
		}
		break;
	}
}

void	generalArrayFunction(void* arr, int numOfElements, int sizeOfElement, void	f(void* element))
{
	
}
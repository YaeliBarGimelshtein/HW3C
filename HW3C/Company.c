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


int	initCompanyFromFile(Company* pComp, FILE* fp)
{
	int len;
	if (fread(&len, sizeof(int), 1, fp) != 1)
		return 0;
	
	pComp->name = (char*)malloc(len * sizeof(char));

	if (fread(pComp->name, sizeof(char), len, fp) != len)
		return 0;

	if (fread(&pComp->flightCount, sizeof(int), 1, fp) != 1)
		return 0;

	if (fread(&pComp->sorted, sizeof(int), 1, fp) != 1)
		return 0;

	L_init(&pComp->allDates);

	pComp->flightArr = (Flight**)malloc(pComp->flightCount * sizeof(Flight*));
	if (pComp->flightArr == NULL)
		return 0;
	

	char dateStr[MAX_STR_LEN];


	for (int i = 0; i < pComp->flightCount; i++)
	{
		pComp->flightArr[i]= (Flight*)malloc(pComp->flightCount * sizeof(Flight));
		if (!pComp->flightArr[i])
			return 0;
		if (initFlightFromFile(pComp->flightArr[i], fp) == 0)
			return 0;
	}

	
	
	if (pComp->flightCount == 1)
	{
		sprintf(dateStr, "%d/%d/%d", pComp->flightArr[pComp->flightCount - 1]->date.day,
			pComp->flightArr[pComp->flightCount - 1]->date.month,
			pComp->flightArr[pComp->flightCount - 1]->date.year);
		L_insert(&pComp->allDates.head, getDynStr(dateStr));
		return 1;
	}
		
	int counter = 0;
	
	for (int i = 0; i < pComp->flightCount; i++)
	{
		for (int j=0; j < i; j++)
		{
			if (compareDate(&pComp->flightArr[i]->date, &pComp->flightArr[j]->date) != 0)
			{
				counter++;
			}
		}
		if (counter ==i)
		{
			sprintf(dateStr, "%d/%d/%d", pComp->flightArr[i]->date.day,
				pComp->flightArr[i]->date.month,
				pComp->flightArr[i]->date.year);

			L_insert(&pComp->allDates.head, getDynStr(dateStr));
		}
		counter = 0;
	}



	return 1;
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
	
	char dateStr[MAX_STR_LEN];
	sprintf(dateStr, "%d/%d/%d", pComp->flightArr[pComp->flightCount-1]->date.day,
		pComp->flightArr[pComp->flightCount - 1]->date.month,
		pComp->flightArr[pComp->flightCount - 1]->date.year);

	
	L_insert(&pComp->allDates.head, getDynStr(dateStr));
	

	return 1;
}

void printCompany(const Company* pComp)
{
	printf("Company %s:\n", pComp->name);
	printf("Has %d flights\n", pComp->flightCount);
	printFlightArr(pComp->flightArr, pComp->flightCount);
	if (pComp->flightCount == 0)
		return;
	printf("The filgts that are not repetetive are on dates:\n");
	L_print(&pComp->allDates, printStrDate);
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
	generalArrayFunction(pFlight, size, sizeof(Flight*), printFlight);
}

void	freeFlightArr(Flight** arr, int size)
{
	generalArrayFunction(arr, size, sizeof(Flight*), freeFlight);
}

void	freeCompany(Company* pComp)
{
	freeFlightArr(pComp->flightArr, pComp->flightCount);
	free(pComp->flightArr);
	free(pComp->name);
	L_free(&pComp->allDates,freeStrDate);
}

void	sortByWithComp(Company* pComp, int(*compareFunc)(const void*, const void*))
{
	qsort(pComp->flightArr, pComp->flightCount, sizeof(Flight*), compareFunc);
}


void	sortBy(Company* pComp)
{
	if (pComp->flightCount == 0)
	{
		printf("cant sort, no flights\n");
		return;
	}
	
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
	if (pComp->flightCount == 0)
	{
		printf("cant search, no flights\n");
		return;
	}

	if (pComp->sorted == eNotSorted)
	{
		printf("cant search an un sorted array\n");
		return;
	}

	printf("enter the flight you are looking for:\n");
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
	for (int i = 0; i < numOfElements; i++)
	{
		f(*(char*)arr + i * sizeOfElement);
	}
}

void	wtireCompanyToFile(Company* pComp, FILE* fp)
{
	int len = strlen(pComp->name)+1;

	if (fwrite(&len, sizeof(int), 1, fp) != 1)
		return;

	if (fwrite(pComp->name, sizeof(char), strlen(pComp->name)+1, fp) != strlen(pComp->name) + 1)
		return;

	if (fwrite(&pComp->flightCount, sizeof(int), 1, fp) != 1)
		return;

	if (fwrite(&pComp->sorted, sizeof(int), 1, fp) != 1)
		return;

	for (int i = 0; i < pComp->flightCount; i++)
	{
		writeFlightToFile(pComp->flightArr[i], fp);
	}

}
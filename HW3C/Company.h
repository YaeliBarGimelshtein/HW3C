#pragma once
#ifndef __COMP__
#define __COMP__

#include "Flight.h"
#include "AirportManager.h"

typedef enum
{
	eNotSorted, eHourSort, eDateSort,eDestenationCodeSort, eOriginCodeSort,eNumOfChoises
} eSort;


typedef struct
{
	char*		name;
	int			flightCount;
	Flight**	flightArr;
	LIST		allDates;
	int			sorted;
}Company;

void	initCompany(Company* pComp);
int		initCompanyFromFile(Company* pComp,FILE* fp);
int		addFlight(Company* pComp, const AirportManager* pManager);
void	printCompany(const Company* pComp);
void	printFlightsCount(const Company* pComp);
void	printFlightArr(Flight** pFlight, int size);
void	freeFlightArr(Flight** arr, int size);
void	freeCompany(Company* pComp);
void	sortByWithComp(Company* pComp, int(*compareFunc)(const void*, const void*));
void	sortBy(Company* pComp);
void	searchBy(Company* pComp, AirportManager* pPort);
Flight** findFlight(Flight* key, Company* pComp, int(*compareFunc)(const void*, const void*));
void	generalArrayFunction(void* arr, int numOfElements, int sizeOfElement, void	f(void* element));
void	wtireCompanyToFile(Company* pComp, FILE* fp);

#endif


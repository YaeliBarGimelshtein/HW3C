#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "AirportManager.h"

int	initManager(AirportManager* pManager)
{
	printf("-----------  Init airport Manager\n");
	pManager->count = 0;
	L_init(&pManager->arr);

	int count = 0;
	do {
		printf("How many airport?\t");
		scanf("%d", &count);
	} while (count < 0);
	//clean buffer
	char tav;
	scanf("%c", &tav);
	if (count == 0)
		return 1;


	for (int i = 0; i < count; i++)
	{
		Airport* helper = (Airport*)malloc(1 * sizeof(Airport));
		if (helper == NULL)
			return 0;
		setAirport(helper, pManager);
		if (L_SortInsert(&pManager->arr.head, helper, compareAirportsByCode) == NULL)
			return 0;
	}
	pManager->count = count;

	return 1;
}

int		initManagerFromFile(AirportManager* pManager, FILE* fp)
{
	int res=fscanf(fp, "%d", &pManager->count);
	if (res != 1)
		return 0;

	L_init(&pManager->arr);
	char clean='a';
	fscanf(fp, "%c", &clean);
	

	for (int i = 0; i < pManager->count; i++)
	{
		Airport* helper = (Airport*)malloc(1 * sizeof(Airport));
		if (helper == NULL)
			return 0;
		int result=setAirportFromFile(helper,fp);
		if (!result)
			return 0;
		
		if (L_SortInsert(&pManager->arr.head, helper, compareAirportsByCode) == NULL)
			return 0;
	}
	return 1;
}

int setAirportFromFile(Airport* airport,FILE* fp)
{
	airport->name=getStrExactNameFromFile( MAX_STR_LEN, fp);
	airport->country=getStrExactNameFromFile(MAX_STR_LEN, fp);
	int res=fscanf(fp, "%s", airport->code);
	char clean = 'a';
	fscanf(fp, "%c", &clean);
	if (res == 1)
		return 1;
	
	return 0;
}



int	addAirport(AirportManager* pManager)
{
	Airport* airport=(Airport*)malloc(1*sizeof(Airport));
	setAirport(airport, pManager);
	if (L_SortInsert(&pManager->arr.head,airport,compareAirportsByCode)!=NULL)
	{
		pManager->count++;
		return 1;
	}
	return 0;
}

void  setAirport(Airport* pPort, AirportManager* pManager)
{
	while (1)
	{
		getAirportCode(pPort->code);
		if (checkUniqeCode(pPort->code, pManager))
			break;

		printf("This code already in use - enter a different code\n");
	}

	initAirportNoCode(pPort);
}

Airport* findAirportByCode(const AirportManager* pManager, const char* code)
{
	if (&pManager->arr == NULL)
		return NULL;

	NODE* helper;
	if (pManager->arr.head.next == NULL)
		return NULL;
	
	helper = pManager->arr.head.next;
	while (helper!=NULL)
	{
		if (isAirportCode(helper->key, code))
			return helper->key;

		helper = helper->next;
	}
	
	return NULL;
}

int checkUniqeCode(const char* code, const AirportManager* pManager)
{
	Airport* port = findAirportByCode(pManager, code);

	if (port != NULL)
		return 0;

	return 1;
}

void	printAirports(const AirportManager* pManager)
{
	printf("there are %d airports\n", pManager->count);
	L_print(&pManager->arr, printAirport);
}

void	freeManager(AirportManager* pManager)
{
	L_free(&pManager->arr,freeAirport);
}


void writeManagerToFile(AirportManager* pManage, FILE* fp)
{
	fprintf(fp,"%d\n", pManage->count);
	
	NODE* first = pManage->arr.head.next;

	for (int i = 0; i < pManage->count; i++)
	{
		writeAirportToFile(first->key, fp);
		first = first->next;
	}
}

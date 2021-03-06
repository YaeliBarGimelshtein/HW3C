#include <stdio.h>
#include <stdlib.h>
#include "Company.h"
#include "AirportManager.h"
#include "General.h"



#define TEXT_FILE "airport_authority.txt"
#define BIN_FILE "company.bin"

typedef enum
{
	eAddFlight, eAddAirport, ePrintCompany, ePrintAirports,
	ePrintFlightOrigDest, eSortBy,eSearchBy, eNofOptions
} eMenuOptions;

const char* str[eNofOptions] = { "Add Flight", "Add Airport",
								"PrintCompany", "Print all Airports",
								"Print flights between origin-destination" , "Sort flights","Search flight" };

#define EXIT			-1
int menu();

int main()
{
	AirportManager	manager;
	Company			company;
	
	FILE* fManagerRead = fopen(TEXT_FILE, "r");
	FILE* fCompanyRead = fopen(BIN_FILE, "rb");
	

	if (!fManagerRead || !fCompanyRead)
	{
		initManager(&manager);
		initCompany(&company);
	}
	else
	{
		initManagerFromFile(&manager, fManagerRead);
		int res=initCompanyFromFile(&company, fCompanyRead);
	}

	

	int option;
	int stop = 0;

	do
	{
		option = menu();
		switch (option)
		{
		case eAddFlight:
			if (!addFlight(&company, &manager))
				printf("Error adding flight\n");
			break;


		case eAddAirport:
			if (!addAirport(&manager))
				printf("Error adding airport\n");
			break;

		case ePrintCompany:
			printCompany(&company);
			break;

		case ePrintAirports:
			printAirports(&manager);
			break;

		case ePrintFlightOrigDest:
			printFlightsCount(&company);
			break;

		case eSortBy:
			sortBy(&company);
			break;

		case eSearchBy:
			searchBy(&company,&manager);
			break;

		case EXIT:
			printf("Bye bye\n");
			stop = 1;
			break;

		default:
			printf("Wrong option\n");
			break;
		}
	} while (!stop);
	
	fclose(fManagerRead);
	fclose(fCompanyRead);

	FILE* fManagerWrite = fopen(TEXT_FILE, "w");
	FILE* fCompanyWrite = fopen(BIN_FILE, "wb");

	wtireCompanyToFile(&company, fCompanyWrite);
	writeManagerToFile(&manager, fManagerRead);
	

	fclose(fManagerWrite);
	fclose(fCompanyWrite);
	
	

	freeManager(&manager);
	freeCompany(&company);

	return 1;
}

int menu()
{
	int option;
	printf("\n\n");
	printf("Please choose one of the following options\n");
	for (int i = 0; i < eNofOptions; i++)
		printf("%d - %s\n", i, str[i]);
	printf("%d - Quit\n", EXIT);
	scanf("%d", &option);
	//clean buffer
	char tav;
	scanf("%c", &tav);
	return option;
}

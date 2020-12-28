#pragma once
#ifndef __AIR_MANAGER__
#define __AIR_MANAGER__

#include "Airport.h"
#include "LinkedList.h"

typedef struct
{
	LIST	arr;
	int			count;
}AirportManager;

int		initManager(AirportManager* pManager);
int		initManagerFromFile(AirportManager* pManager, FILE* fp);
int		setAirportFromFile(Airport* airport, FILE* fp);
int		addAirport(AirportManager* pManager);
void	setAirport(Airport* pPort, AirportManager* pManager);
Airport* findAirportByCode(const AirportManager* pManager, const char* code);
int		checkUniqeCode(const char* code, const AirportManager* pManager);
void	printAirports(const AirportManager* pManager);
void	freeManager(AirportManager* pManager);
void	writeManagerToFile(AirportManager* pManage, FILE* fp);
#endif
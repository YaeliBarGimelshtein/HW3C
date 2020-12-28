#pragma once
#ifndef __MYDATE__
#define __MYDATE__

#define MIN_YEAR 2020

typedef struct
{
	int			day;
	int			month;
	int			year;
}Date;

void	getCorrectDate(Date* pDate);
int		checkDate(char* date, Date* pDate);
void	printDate(const Date* pDate);
int		compareDate(const Date* date1, const Date* date2);
void	freeStrDate(char* date);
void printStrDate(const char* date);

#endif

#pragma once
#ifndef __GENERAL__
#define __GENERAL__

#define MAX_STR_LEN 255
#define CODE_LENGTH 3

char*	getStrExactName(const char* msg);
char*	getStrExactNameFromFile(int size, FILE* fp);
char*	myGets(char* buffer, int size);
char*  myGetsFile(char* buffer, int size, FILE* fp);
char*	getDynStr(char* str);
char**	splitCharsToWords(char* str, int* pCount, int* pTotalLength);



#endif


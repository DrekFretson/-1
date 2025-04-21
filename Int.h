#ifndef INT_H
#define INT_H

#include <stdio.h>
#include "typeInfo.h"

typedef struct
{
	int value;
}Int;


Int assignInt(Int i);
void creat_int(void* r, double i);
void sum_int(void* firstD, void* secD, void* res);
void multiplicate_int(void* firstD, void* secD, void* res);
void multiplicate_int_withScal(void* firstD, double scal, void* res);
void printInt(void* el);
void* reverseInt(void* a);
void PrintFile_Int(const void* element, FILE* file);
void ScanFile_Int(void* element, FILE* file);

extern typeInfo intType;

#endif

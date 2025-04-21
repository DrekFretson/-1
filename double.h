#ifndef DOUBLE_H
#define DOUBLE_H

#include <stdio.h>
#include "typeInfo.h"


typedef struct
{
	double value;
}Double;



Double assignDouble(Double i);
void creat_Double(void* r, double i);
void sum_double(void* firstD, void* secD, void* res);
void multiplicate_double(void* firstD, void* secD, void* res);
void multiplicate_double_withScal(void* firstD, double scal, void* res);
void printDouble(void* el);
void* reverseDouble(void* a);
void PrintFile_Double(const void* element, FILE* file);
void ScanFile_Double(void* element, FILE* file);


extern typeInfo doubleType;

#endif

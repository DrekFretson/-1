#ifndef COMPLEX_H
#define COMPLEX_H

#include <stdio.h>
#include "typeInfo.h"


typedef struct 
{
	double real;
	double imaginary;
}Complex;

void creatComplex(Complex com, double r, double i);
void sum_complex(void* firstComp, void* secComp, void* res);
void multiplicate_complex(void* firstComp, void* secComp, void* res);
void multiplicate_complex_withScal(void* firstComp, double scal, void* res);
void printComplex(void* el);
void* reverseComplex(void* a);
void PrintFile_Complex(const void* element, FILE* file);
void ScanFile_Complex(void* element, FILE* file);

extern typeInfo complexType;

#endif

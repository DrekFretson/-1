#include "Complex.h"
#include "typeInfo.h"
#include <stdio.h>


void creat_Complex(void* com, double i) {
    Complex* res = (Complex*)com;
    res->real = i;
    res->imaginary = i;
};
void sum_complex(void* firstComp, void* secComp, void* res) {
    if (firstComp && secComp && res) {
        Complex* first_Comp = (Complex*)firstComp;
        Complex* sec_Comp = (Complex*)secComp;
        Complex* cres = (Complex*)res;
        cres->real = first_Comp->real + sec_Comp->real;
        cres->imaginary = first_Comp->imaginary + sec_Comp->imaginary;
    }
}
void multiplicate_complex(void* firstComp, void* secComp, void* res) {
    if (firstComp && secComp && res) {
        Complex* first_Comp = (Complex*)firstComp;
        Complex* sec_Comp = (Complex*)secComp;
        Complex* cres = (Complex*)res;
        cres->real = first_Comp->real * sec_Comp->real - sec_Comp->imaginary * first_Comp->imaginary;
        cres->imaginary = first_Comp->real * sec_Comp->imaginary + first_Comp->imaginary * sec_Comp->real;
    }
}
void multiplicate_complex_withScal(void* firstComp, double scal, void* res) {
    if (firstComp && res) {
        Complex* first_Comp = (Complex*)firstComp;
        Complex* cres = (Complex*)res;
        cres->real = first_Comp->real * scal;
        cres->imaginary = first_Comp->imaginary * scal;
    }
}
void printComplex(void* el) {
    if (el)
    {
        Complex* c = (Complex*)el;
        printf("(%lf + %lfi) ", c->real, c->imaginary);
    }
}
void* reverseComplex(void* A) {
    if (A) {
        Complex* a = (Complex*)A;
        Complex* b = (Complex*)malloc(sizeof(Complex));
        if (b != NULL) {
            b->real = -(a->real);
            b->imaginary = -(a->imaginary);
        }
        return b;
    }
    return NULL;
}
void PrintFile_Complex(const void* element, FILE* file) {
    if (element == NULL || file == NULL) {
        fprintf(stderr, "Error: Data cannot be written. Pointers are NULL\n");
        return;
    }
    const Complex* el = (const Complex*)element;
    fprintf(file, "%.2f + %.2fi ", el->real, el->imaginary);
}
void ScanFile_Complex(void* element, FILE* file) {
    if (element == NULL || file == NULL) {
        fprintf(stderr, "Ошибка: Указатели не могут быть NULL\n");
        return;
    }
    Complex* el = (Complex*)element;

    if (fscanf_s(file, "%lf %lf", &el->real, &el->imaginary) != 2) {
        fprintf(stderr, "Ошибка: Не удалось считать целое число из файла\n");
    }
}



typeInfo complexType = {
    sizeof(Complex),
    creat_Complex,
    sum_complex,
    multiplicate_complex,
    multiplicate_complex_withScal,
    printComplex,
    reverseComplex,
    PrintFile_Complex,
    ScanFile_Complex,
    COMPLEX_TYPE
};

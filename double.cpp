#include <stdio.h>
#include "double.h"
#include "typeInfo.h"


Double assignDouble(Double i) {
    Double newDouble;
    newDouble.value = i.value;
    return newDouble;
};
void creat_Double(void* r, double i) {
    Double* res = (Double*)r;
    res->value = i;
};
void sum_double(void* a, void* b, void* res) {
    if (a && b && res)
    {
        Double* douA = (Double*)a;
        Double* douB = (Double*)b;
        Double* doures = (Double*)res;

        doures->value = douA->value + douB->value;
    }
}
void multiplicate_double(void* a, void* b, void* res) {
    if (a && b && res)
    {
        Double* douA = (Double*)a;
        Double* douB = (Double*)b;
        Double* doures = (Double*)res;

        doures->value = douA->value * douB->value;
    }
}
void multiplicate_double_withScal(void* a, double scal, void* res) {
    if (a && res)
    {
        Double* douA = (Double*)a;
        Double* doures = (Double*)res;

        doures->value = douA->value * scal;
    }
}
void printDouble(void* el) {
    if (el)
    {
        Double* douel = (Double*)el;
        printf("%lf ", douel->value);
    }
}
void* reverseDouble(void* A) {
    if (A) {
        Double* a = (Double*)A;
        Double* b = (Double*)malloc(sizeof(Double));
        if (b != NULL) {
            b->value = -(a->value);
        }
        return b;
    }
    return NULL;
}
void PrintFile_Double(const void* element, FILE* file) {
    if (element == NULL || file == NULL) {
        fprintf(stderr, "Error: Data cannot be written. Pointers are NULL\n");
        return;
    }
    const Double* el = (const Double*)element;
    fprintf(file, "%.2f ", el->value);
}
void ScanFile_Double(void* element, FILE* file) {
    if (element == NULL || file == NULL) {
        fprintf(stderr, "Ошибка: Указатели не могут быть NULL\n");
        return;
    }
    Double* el = (Double*)element;

    if (fscanf_s(file, "%lf", &el->value) != 1) {
        fprintf(stderr, "Ошибка: Не удалось считать целое число из файла\n");
    }
}


typeInfo doubleType = {
    sizeof(Double),
    creat_Double,
    sum_double,
    multiplicate_double,
    multiplicate_double_withScal,
    printDouble,
    reverseDouble,
    PrintFile_Double,
    ScanFile_Double,
    DOUBLE_TYPE
};

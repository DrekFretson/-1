#include <stdio.h>
#include "Int.h"
#include "typeInfo.h"


Int assignInt(Int i) {
    Int newInt;
    newInt.value = i.value;
    return newInt;
}
void creat_int(void* r, double i) {
    Int* res = (Int*)r;
    res->value = i;
};
void sum_int(void* a, void* b, void* res) {
    if (a && b && res) {
        Int* intA = (Int*)a;
        Int* intB = (Int*)b;
        Int* intRes = (Int*)res;

        intRes->value = intA->value + intB->value;
    }
}
void multiplicate_int(void* a, void* b, void* res) {
    if (a && b && res)
    {
        Int* intA = (Int*)a;
        Int* intB = (Int*)b;
        Int* intRes = (Int*)res;
        
        intRes->value = intA->value * intB->value;
    }
}
void multiplicate_int_withScal(void* a, double scal, void* res) {
    if (a && res)
    {
        Int* intA = (Int*)a;
        Int* intRes = (Int*)res;

        intRes->value = intA->value * scal;
    }
}
void printInt(void* el) {
    if (el)
    {
        Int* intel = (Int*)el;
        printf("%d ", intel->value);
    }
}
void* reverseInt(void* A) {
    if (A) {
        Int* a = (Int*)A;
        Int* b = (Int*)malloc(sizeof(Int));
        if (b != NULL) {
            b->value = -(a->value);
        }
        return b;
    }
    return NULL;
}
void PrintFile_Int(const void* element, FILE* file) {
    if (element == NULL || file == NULL) {
        fprintf(stderr, "Error: Data cannot be written. Pointers are NULL.\n");
        return;
    }
    const Int* el = (const Int*)element;
    fprintf(file, "%d ", el->value);
}
void ScanFile_Int(void* element, FILE* file) {
    if (element == NULL || file == NULL) {
        fprintf(stderr, "Eror: Pointers cannot be NULL\n");
        return;
    }
    Int* el = (Int*)element;

    if (fscanf_s(file, "%d", &el->value) != 1) {
        fprintf(stderr, "Error: An integer could not be read from the file.\n");
    }
}


typeInfo intType = {
    sizeof(int),
    creat_int,
    sum_int,
    multiplicate_int,
    multiplicate_int_withScal,
    printInt,
    reverseInt,
    PrintFile_Int,
    ScanFile_Int,
    INT_TYPE
};

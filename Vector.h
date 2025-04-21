#ifndef VECTOR_H
#define VECTOR_H


#include "typeInfo.h"
#include "double.h"
#include "Int.h"
#include "Complex.h"
#include "TypeVector.h"
#include <string>


typedef struct
{
    int dimensions;      // Количество измерений вектора
    void* data;         // Указатель на данные вектора
    const typeInfo* type; // Указатель на информацию о типе данных
}Vector;

void* createElement(void* Vec);
void* createVector(int dimensions, const typeInfo* type);
void SetVectorValue(void* vec, int index, void* value);
void* GetVectorElement(void* vec, int index);
void* sumVectors(void* Vec1, void* Vec2);
void* multiplicate_vector(void* Vec1, void* Vec2);
void* multiplicate_vector_withScal(void* Vec1, double scal);
void printVector(void* Vector);
void freeVector(void* Vec);
void inputValuesForVector(void* vec);
void* vector_multiplicate(void* vec1, void* vec2);
void PrintFile_Vector(const void* element, FILE* file);
void* ScanFile_Vector(FILE* file);

extern typeInfoV VectorType;

#endif

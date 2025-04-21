#include "Vector.h"
#include "typeInfo.h"
#include "double.h"
#include "Int.h"
#include "Complex.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


void* createElement(void* Vec) {
    Vector* vec = (Vector*)Vec;
    if (vec == NULL || vec->type == NULL) return NULL;

    switch (vec->type->type) {
    case DOUBLE_TYPE: {
        Double* result = (Double*)malloc(sizeof(double));
        if (result != NULL) {
            result->value = 0;
        }
        return result;
    }
    case INT_TYPE: {
        Int* result = (Int*)malloc(sizeof(int));
        if (result != NULL) {
            result->value = 0;
        }
        return result;
    }
    case COMPLEX_TYPE: {
        Complex* result = (Complex*)malloc(sizeof(Complex));
        if (result != NULL) {
            result->imaginary = 0;
            result->real = 0;
        }
        return result;
    }
    }
    return NULL;
};
void* createVector(int dimension, const typeInfo* typ) {
	Vector* vec = (Vector*)malloc(sizeof(Vector));
    if (vec == NULL) {
        fprintf(stderr, "Memory allocation error\n");
        exit(EXIT_FAILURE);
    }
	vec->dimensions = dimension;
	vec->type = typ;

    if (vec->type->size > 0) {
        vec->data = malloc(vec->dimensions * vec->type->size);
    }
    else {
        vec->data = NULL;
    }
    return vec;
};
void SetVectorValue(void* vec1, int index, void* value) {
    Vector* vec = (Vector*)vec1;
    if (index < vec->dimensions) {
        memcpy((char*)vec->data + index * vec->type->size, value, vec->type->size);
    }
    else {
        printf("Index selection error.\n");
    }
};
void* GetVectorElement(void* vec, int index) {
    Vector* vector = (Vector*)vec;

    if (vector == NULL) {
        fprintf(stderr, "Error: The vector pointer must not be NULL \n");
        exit(EXIT_FAILURE);
    }

    if (index < 0 || index >= vector->dimensions) {
        fprintf(stderr, "Error: Index out of range \n");
        exit(EXIT_FAILURE);
    }
    
    if (vector->type == NULL) {
        fprintf(stderr, "Error: The data type pointer is not initialized \n");
        exit(EXIT_FAILURE);
    }

    void* a = (char*)vector->data + index * vector->type->size;
    

    return a;
}
void* sumVectors(void* Vec1, void* Vec2) {
    Vector* vec1 = (Vector*)Vec1;
    Vector* vec2 = (Vector*)Vec2;
    if (vec1->dimensions != vec2->dimensions) {
        fprintf(stderr, "Error: Vectors must have the same dimension for addition.\n");
        exit(EXIT_FAILURE);
    }

    void* res = createVector(vec1->dimensions, vec1->type);
    Vector* result = (Vector*)res;

    for (int i = 0; i < vec1->dimensions; i++)
    {
        void* elV1 = GetVectorElement(vec1, i);
        void* elV2 = GetVectorElement(vec2, i);

        vec1->type->sum(elV1, elV2, GetVectorElement(result, i));
    }
    return result;
};
void* multiplicate_vector(void* Vec1, void* Vec2) {
    Vector* vec1 = (Vector*)Vec1;
    Vector* vec2 = (Vector*)Vec2;
    if (vec1->dimensions != vec2->dimensions) {
        fprintf(stderr, "Error: Vectors must have the same dimension for a scalar product.\n");
        exit(EXIT_FAILURE);
    }

    void* res = createElement(vec1);


    //исправить на сравнение адресов на тип
    vec1->type->creat(res, 0);
    

    /*if (vec1->type->type == DOUBLE_TYPE) {
        Double* result = (Double*)res;
        creatDouble(*result, 0);
    }
    else if (vec1->type->type == INT_TYPE) {
        Int* result = (Int*)res;
        creatInt(*result, 0);
    }
    else if (vec1->type->type == COMPLEX_TYPE) {
        Complex* result = (Complex*)res;
        creatComplex(*result, 0.0, 0.0);
    }*/


    

    for (int i = 0; i < vec1->dimensions; i++) {
        void* elV1 = GetVectorElement(vec1, i);
        void* elV2 = GetVectorElement(vec2, i);

        void* tempResult = createElement(vec1);
        vec1->type->multiplicate(elV1, elV2, tempResult);
        vec1->type->sum(res, tempResult, res);

        free(tempResult);
    }
    return res;
};
void* multiplicate_vector_withScal(void* Vec1, double scal) {
    Vector* vec1 = (Vector*)Vec1;
    void* result = createVector(vec1->dimensions, vec1->type);

    for (int i = 0; i < vec1->dimensions; i++)
    {
        void* elV1 = GetVectorElement(vec1, i);
        void* elVR = GetVectorElement(result, i);
        vec1->type->multiplicate_withScal(elV1, scal, elVR);
    }
    return result;
};
void printVector(void* Vec) {
    Vector* vec = (Vector*)Vec;

    void* result = createElement(vec);
    printf("{ ");
    for (int i = 0; i < vec->dimensions; i++)
    {
        result = GetVectorElement(vec, i);
        vec->type->print(result);
        if (i<vec->dimensions-1)
        {
            printf(", ");
        }
    }
    printf(" }");
};
void freeVector(void* Vec) {
    if (Vec != NULL) {
        Vector* vec = (Vector*)Vec;
        if (vec->data != NULL) {
            free(vec->data);
        }
        free(vec);
    }
};
void inputValuesForVector(void* vec) {
    Vector* vector = (Vector*)vec;

    switch (vector->type->type) {
    case INT_TYPE: {
        for (int i = 0; i < vector->dimensions; i++) {
            int a;
            scanf_s("%d", &a);
            Int b;
            b.value = a;
            SetVectorValue(vector, i, &b);
        }
        break;
    }

    case DOUBLE_TYPE: {
        for (int i = 0; i < vector->dimensions; i++) {
            double a;
            scanf_s("%lf", &a);
            Double b;
            b.value = a;
            SetVectorValue(vector, i, &b);
        }
        break;
    }

    case COMPLEX_TYPE: {
        for (int i = 0; i < vector->dimensions; i++) {
            double real, imag;
            scanf_s("%lf %lf", &real, &imag);
            Complex c;
            c.real = real;
            c.imaginary = imag;
            SetVectorValue(vector, i, &c);
        }
        break;
    }

    default:
        fprintf(stderr, "Ошибка: Неподдерживаемый тип.\n");
        exit(EXIT_FAILURE);
    }
};
void* vector_multiplicate(void* Vec1, void* Vec2) {
    Vector* vec1 = (Vector*)Vec1;
    Vector* vec2 = (Vector*)Vec2;

    if (vec1->dimensions != 3 || vec2->dimensions != 3) {
        fprintf(stderr, "Error: The vector product is only possible for three-dimensional vectors.\n");
        return NULL;
    }
    void* res = createVector(3, vec1->type);
    if (res == NULL) {
        fprintf(stderr, "Error: The result of the vector product could not be created.\n");
        return NULL;
    }
    Vector* result = (Vector*)res;


    void* elV1_x = GetVectorElement(vec1, 0);
    void* elV1_y = GetVectorElement(vec1, 1);
    void* elV1_z = GetVectorElement(vec1, 2);

    void* elV2_x = GetVectorElement(vec2, 0);
    void* elV2_y = GetVectorElement(vec2, 1);
    void* elV2_z = GetVectorElement(vec2, 2);
    
    void* result_x = createElement(vec1);
    void* result_y = createElement(vec1);
    void* result_z = createElement(vec1);

    void* product1 = createElement(vec1); // Умножение 12 на 23
    void* product2 = createElement(vec1); // Умножение 13 на 22
    void* product3 = createElement(vec1); // Умножение 11 на 23
    void* product4 = createElement(vec1); // Умножение 13 на 21
    void* product5 = createElement(vec1); // Умножение 11 на 22
    void* product6 = createElement(vec1); // Умножение 12 на 21

    vec1->type->multiplicate(elV1_y, elV2_z, product1);
    vec1->type->multiplicate(elV1_z, elV2_y, product2);
    vec1->type->multiplicate(elV1_x, elV2_z, product3);
    vec1->type->multiplicate(elV1_z, elV2_x, product4);
    vec1->type->multiplicate(elV1_x, elV2_y, product5);
    vec1->type->multiplicate(elV1_y, elV2_x, product6);

    void* reversedProduct2 = vec1->type->reverse(product2); // Обратное значение к product2
    void* reversedProduct3 = vec1->type->reverse(product3); // Обратное значение к product4
    void* reversedProduct6 = vec1->type->reverse(product6); // Обратное значение к product6

    vec1->type->sum(product1, reversedProduct2, result_x);
    vec1->type->sum(reversedProduct3, product4, result_y);
    vec1->type->sum(product5, reversedProduct6, result_z);


    SetVectorValue(result, 0, result_x);
    SetVectorValue(result, 1, result_y);
    SetVectorValue(result, 2, result_z);

    free(product1);
    free(product2);
    free(product3);
    free(product4);
    free(product5);
    free(product6);
    free(reversedProduct2);
    free(reversedProduct3);
    free(reversedProduct6);

    return result;
}
void PrintFile_Vector(const void* el, FILE* file) {
    if (el == NULL || file == NULL) {
        fprintf(stderr, "Error: Data cannot be written. Pointers are NULL.\n");
        return;
    }
    Vector* vec = (Vector*)el;

    void* result = createElement(vec);
    fprintf(file, "{ ");
    for (int i = 0; i < vec->dimensions; i++)
    {
        result = GetVectorElement(vec, i);
        vec->type->printFile(result, file);
        if (i < vec->dimensions - 1)
        {
            fprintf(file, ", ");
        }
    }
    fprintf(file, "}");
};
void* ScanFile_Vector(FILE* file) {
    char type_str[20];
    if (fscanf_s(file, "%19s", type_str, (unsigned)_countof(type_str)) != 1) {
        fprintf(stderr, "Error reading vector type\n");
        return NULL;
    }
    fprintf(stderr, "Debug: Reading vector of type %s\n", type_str);

    DataType type;
    if (strcmp(type_str, "INT") == 0) type = INT_TYPE;
    else if (strcmp(type_str, "DOUBLE") == 0) type = DOUBLE_TYPE;
    else if (strcmp(type_str, "COMPLEX") == 0) type = COMPLEX_TYPE;
    else {
        fprintf(stderr, "Unknown type: %s\n", type_str);
        return NULL;
    }
    int measurements = 0;
    if (fscanf_s(file, "%i", &measurements) != 1 || measurements <= 0) {
        fprintf(stderr, "Ошибка: не удалось считать количество измерений. Оно должно быть положительным.\n");
        return NULL;
    }

    void* el = NULL;
    if (type == INT_TYPE) {
        el = malloc(sizeof(Int));
        void* Vec = createVector(measurements, &intType);
        Vector* vec = (Vector*)Vec;
        for (int i = 0; i < measurements; i++)
        {
            ScanFile_Int(el, file);
            SetVectorValue(vec, i, el);
        }
        return vec;
    }
    else if (type == DOUBLE_TYPE) {
        el = malloc(sizeof(Double));
        void* Vec = createVector(measurements, &doubleType);
        Vector* vec = (Vector*)Vec;
        for (int i = 0; i < measurements; i++)
        {
            ScanFile_Double(el, file);
            SetVectorValue(vec, i, el);
        }
        return vec;
    }
    else if (type == COMPLEX_TYPE) {
        el = malloc(sizeof(Complex));
        void* Vec = createVector(measurements, &complexType);
        Vector* vec = (Vector*)Vec;
        for (int i = 0; i < measurements; i++)
        {
            ScanFile_Complex(el, file);
            SetVectorValue(vec, i, el);
        }
        return vec;
    }
};


typeInfoV VectorType = {
    sizeof(Vector),
    createElement,
    createVector,
    SetVectorValue,
    GetVectorElement,
    sumVectors,
    multiplicate_vector,
    multiplicate_vector_withScal,
    printVector,
    freeVector,
    inputValuesForVector,
    vector_multiplicate,
    PrintFile_Vector,
    ScanFile_Vector
};

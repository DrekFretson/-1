#include "typeInfo.h"
#include "typesEnum.h"
#include "Int.h"
#include "double.h"
#include "Complex.h"
#include "Vector.h"
#include "TypeVector.h"
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>



void FileWork(FILE* input, FILE* output) {
    setlocale(LC_ALL, "Rus");
    int pair_count;
    if (fscanf_s(input, "%d", &pair_count) != 1) {
        fprintf(stderr, "Error reading pair count\n");
        return;
    }

    for (int i = 0; i < pair_count; i++) {
        void* Vec1 = ScanFile_Vector(input);
        void* Vec2 = ScanFile_Vector(input);
        Vector* vec1 = (Vector*)Vec1;

        //сумма
        void* Vec_sum = sumVectors(Vec1, Vec2);
        fprintf(output, "Sum vector:\n");
        PrintFile_Vector(Vec_sum, output);
        fprintf(output, "\n");

        //умножение на скаляр(2)
        void* Vec_2 = multiplicate_vector_withScal(Vec1, 2);
        fprintf(output, "Multiplikate vector with 2:\n");
        PrintFile_Vector(Vec_2, output);
        fprintf(output, "\n");

        //скалярное произведение
        void* skal = multiplicate_vector(Vec1, Vec2);
        fprintf(output, "Skal_multiplicate:\n");
        if (vec1->type == &intType) {
            PrintFile_Int(skal, output);
        }
        else {
            PrintFile_Double(skal, output);
        }
        fprintf(output, "\n");

        //векторное произведение
        void* Vec_mult = vector_multiplicate(Vec1, Vec2);
        fprintf(output, "Vector_multiplicate:\n");
        PrintFile_Vector(Vec_mult, output);
        fprintf(output, "\n");
        fprintf(output, "\n");

        freeVector(Vec1);
        freeVector(Vec2);
        freeVector(Vec_sum);
        freeVector(Vec_mult);
        free(skal);
    }
};


int main() {
    setlocale(LC_ALL, "Rus");

    FILE* inFile;
    if (fopen_s(&inFile, "input.txt", "r") != 0) {
        perror("Ошибка: Не удалось открыть файл для чтения");
        return EXIT_FAILURE;
    }
    FILE* outFile;
    if (fopen_s(&outFile, "output.txt", "w") != 0) {
        perror("Ошибка: Не удалось открыть файл для записи");
        fclose(inFile);
        return EXIT_FAILURE;
    }

    
    
    FileWork(inFile, outFile);
    //creatvector(3, &intType);

    fclose(inFile);
    fclose(outFile);

    return 0;
}

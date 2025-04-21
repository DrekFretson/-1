#ifndef TYPEVECTOR_H
#define TYPEVECTOR_H

#include <stdio.h>
#include <stdlib.h>
#include "typesEnum.h"
#include "Vector.h"

typedef struct {
	size_t size;
	void* (*createElement)(void*);
	void* (*createVector)(int, const typeInfo*);
	void (*SetVectorValue)(void*, int, void*);
	void* (*GetVectorElement)(void*, int);
	void* (*sumVectors)(void*, void*);
	void* (*multiplicate)(void*, void*);
	void* (*multiplicate_withScal)(void*, double);
	void (*print)(void*);
	void (*freeVector)(void*);
	void (*inputValuesForVector)(void*);
	void* (*vector_multiplicate)(void*, void*);
	void (*printFile_Vector)(const void*, FILE*);
	void* (*ScanFile_Vector)(FILE*);
	DataType type;
}typeInfoV;
#endif

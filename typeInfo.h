#ifndef TYPEINFO_H
#define TYPEINFO_H

#include <stdlib.h>
#include <stdio.h>
#include "typesEnum.h"




typedef struct {
	size_t size;
	void(*creat)(void*, double);
	void(*sum)(void*, void*, void*);
	void(*multiplicate)(void*, void*, void*);
	void(*multiplicate_withScal)(void*, double, void*);
	void(*print)(void*);
	void*(*reverse)(void*);
	void(*printFile)(const void*, FILE*);
	void(*ScanFile)(void*, FILE*);
	DataType type;
}typeInfo;

#endif

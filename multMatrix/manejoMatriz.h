#pragma once
//linka con el cliente, reproduce la clase base

#include <iostream>
#include <stdio.h>
#include <stdlib.h>

#include "multmatrix.h"

matrix_t* leerMatriz(const char* file);
void escribirMatrix(matrix_t* m, const char *fileName);
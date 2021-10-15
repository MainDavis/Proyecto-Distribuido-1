#pragma once
//linka con el server, reproduce la clase base

#include "multmatrix.h"

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "utils.h"

#define IP_SERVER "127.0.0.1"
#define PORT_SERVER  3301

class multmatrix_stub
{
private:
    
    int serverId = 0;

public:
    multmatrix_stub();
    ~multmatrix_stub();
    matrix_t* readMatrix(const char* fileName);
    matrix_t *multMatrices(matrix_t* m1, matrix_t *m2);
    void writeMatrix(matrix_t* m, const char *fileName);
    matrix_t *createIdentity(int rows, int cols);
    matrix_t *createRandMatrix(int rows, int cols);
};

multmatrix_stub::multmatrix_stub()
{
}

multmatrix_stub::~multmatrix_stub()
{
}

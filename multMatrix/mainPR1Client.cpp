#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <cstring>
#include <sys/types.h>
#include <unistd.h>

#include "multmatrix_stub.h"


void freeMatrix(matrix_t* m){
    delete[] m->data;
    delete[] m;

}
int main()
{
    multmatrix_stub* mmatrix=new multmatrix_stub();


    //matrix_t* m1= mmatrix->createRandMatrix(5,5);
    //matrix_t* m2= mmatrix->createIdentity(5,5);
    //matrix_t* mres=mmatrix->multMatrices(m1,m2);
    //mmatrix->writeMatrix(mres,"resultado.txt");
    matrix_t* m3=mmatrix->readMatrix("resultado.txt");
    //matrix_t* mres2=mmatrix->multMatrices(m1,m3);
    //mmatrix->writeMatrix(mres2,"resultado2.txt");

    std::cout << "COLS: " << m3->cols;

    //freeMatrix(m1);
    //freeMatrix(m2);
    //freeMatrix(mres);
    freeMatrix(m3);
    //freeMatrix(mres2);
    delete mmatrix;

}
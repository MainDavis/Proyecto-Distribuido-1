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
    int op;

    

    do{
        std::cout << "Inserte la operación que desea hacer:\n\n";

        std::cout << "\t1. Crear matriz.\n";
        std::cout << "\t2. Cargar matriz.\n";
        std::cout << "\t3. Guardar matriz.\n";
        std::cout << "\t4. Mostrar matrices cargadas\n";
        std::cout << "\t5. Multiplicar matrices.\n";
        std::cout << "\t6. Salir.\n\n";

        std::cout << "Opcion: ";
        std::cin >> op;

        switch(op){
            case 1: {

                std::cout << "\nComo desea crear la matriz:\n\n";
                
                std::cout << "\t1. Manualmente.\n";
                std::cout << "\t2. Aleatoria.\n";
                std::cout << "\t3. Matriz identidad\n\n";

                std::cout << "\tOpcion: ";
                std::cin >> op;

                switch(op){
                    case 1: {
                        
                    }
                    break;

                }

                }
                break;


        }


    }while(op != 6);
    


    matrix_t* m1= mmatrix->createRandMatrix(5,5);
    matrix_t* m2= mmatrix->createIdentity(5,5);
    matrix_t* mres=mmatrix->multMatrices(m1,m2);
    mmatrix->writeMatrix(mres,"resultado.txt");
    matrix_t* m3=mmatrix->readMatrix("resultado.txt");
    matrix_t* mres2=mmatrix->multMatrices(m1,m3);
    mmatrix->writeMatrix(mres2,"resultado2.txt");

    freeMatrix(m1);
    freeMatrix(m2);
    freeMatrix(mres);
    freeMatrix(m3);
    freeMatrix(mres2);
    delete mmatrix;

}

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <cstring>
#include <sys/types.h>
#include <unistd.h>
#include <vector>

#include "multmatrix_stub.h"
#include "manejoMatriz.h"


void freeMatrix(matrix_t* m){
    delete[] m->data;
    delete[] m;

}
int main()
{
    multmatrix_stub* opMatrix=new multmatrix_stub();
    std::vector<matrix_t> arrMatrix;
    int op, filas, columnas, id;
    char* fileName = new char[25];

    do{
        std::cout << " \n\nInserte la operación que desea hacer:\n\n";

        std::cout << "\t1. Crear matriz.\n";
        std::cout << "\t2. Cargar matriz.\n";
        std::cout << "\t3. Guardar matriz.\n";
        std::cout << "\t4. Mostrar matrices cargadas\n";
        std::cout << "\t5. Multiplicar matrices.\n";
        std::cout << "\t6. Salir.\n\n";

        std::cout << "\tOpcion: ";
        std::cin >> op;

        switch(op){
            case 1: {

                std::cout << "\nComo desea crear la matriz:\n\n";
                
                std::cout << "\t1. Manualmente.\n";
                std::cout << "\t2. Aleatoria.\n";
                std::cout << "\t3. Matriz identidad\n\n";

                std::cout << "\tOpcion: ";
                std::cin >> op;

                std::cout << "\nDe cuantas filas y columnas desea:\n\n";
                std::cout << "\tFilas: ";
                
                std::cin >> filas;

                std::cout << "\tColumnas: ";

                std::cin >> columnas;

                switch(op){
                    case 1: {
    
                        matrix_t* result = new matrix_t;

                        result->rows = filas;
                        result->cols = columnas;
                        result->data = new int[filas*columnas];
                        
                        std::cout << "\nInserte los " << filas*columnas << " datos: \n\n";

                        for(int i=0; i<filas*columnas; i++){
                            std::cout << "\tDato " << i+1 << ": ";
                            std::cin >> result->data[i];
                        }

                        arrMatrix.push_back(*result);

                    }
                        break;
                    
                    case 2: {

                        arrMatrix.push_back(*opMatrix->createRandMatrix(filas,columnas));

                    }
                        break;

                    case 3: {

                        arrMatrix.push_back(*opMatrix->createIdentity(filas,columnas));

                    }
                        break;
                }

            }
                break;

            case 2: {
                
                std::cout << "\nInserte el nombre del fichero: ";
                std::cin >> fileName;

                arrMatrix.push_back(*leerMatriz(fileName));

            }
                break;

            case 3: {

                std::cout << "\nInserte el ID y el nombre del fichero que desea:\n\n";
                std::cout << "\tID: ";
                std::cin >> id;
                std::cout << "\tNombre del fichero: ";
                std::cin >> fileName;
                
                if(id < 1 || id > arrMatrix.size()){
                    std::cout << "\nNo existe ese ID";
                }else{
                    escribirMatrix( &arrMatrix.at(id-1), fileName);
                }

            }
                break;

            case 4: {

                std::cout << "Actualmente hay cargadas " << arrMatrix.size() << " matrices.\n";
                std::cout << "Inserte 0 para salir o el ID para ver los datos: \n";
                std::cout << "\tOpcion: ";
                std::cin >> id;

                if(id > arrMatrix.size()){
                    std::cout << "\nNo existe ese ID";
                }else if(id > 0){
                    
                    std::cout << "\nFilas: " << arrMatrix.at(id)->cols; 

                }

            }
                break;

        }


    }while(op != 6);



    /* matrix_t* m1= mmatrix->createRandMatrix(5,5);
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
    delete mmatrix; */

}

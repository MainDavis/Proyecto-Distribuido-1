#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <cstring>
#include <sys/types.h>
#include <unistd.h>
#include <vector>

#include "multmatrix_stub.h"

void freeMatrix(matrix_t* m){
    delete[] m->data;
    delete[] m;
}
int main()
{
    multmatrix_stub* opMatrix=new multmatrix_stub();
    std::vector<matrix_t> arrMatrix;
    int op, filas, columnas, id, id2;
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

                matrix_t* temp = opMatrix->readMatrix(fileName);

                if(temp != NULL)
                    arrMatrix.push_back( *temp );      

                delete temp;         

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
                    opMatrix->writeMatrix(&arrMatrix.at(id-1), fileName);
                }

            }
                break;

            case 4: {

                std::cout << "\n\nActualmente hay cargadas " << arrMatrix.size() << " matrices.";
                std::cout << "\n\n\tInserte 0 para salir o el ID para ver los datos: ";
                std::cin >> id;

                if(id > arrMatrix.size()){
                    std::cout << "\nNo existe ese ID";
                }else if(id > 0){
                    
                    std::cout << "\n\tFilas: " << arrMatrix.at(id-1).cols; 
                    std::cout << "\n\tColumnas: " << arrMatrix.at(id-1).rows << "\n";

                    for(int i = 0; i < arrMatrix.at(id-1).rows * arrMatrix.at(id-1).cols; i++)
                        std::cout << "\n\tDato [" << i+1 << "]: " << arrMatrix.at(id-1).data[i];                   

                }

            }
                break;

            case 5: {
                //Si no tiene como minimo dos matrices cargadas se sale
                if(arrMatrix.size()<2){
                    std::cout << "\n\nNo hay suficientes matrices cargadas, minimo necesitas 2.\n";
                }else{

                    std::cout << "\n\nInserte el ID de las matrices a multiplicar:";
                    std::cout << "\n\n\tMatriz 1: ";
                    std::cin >> id;
                    std::cout << "\tMatriz 2: ";
                    std::cin >> id2;

                    //Enviamos las matrices para que las multiplique el servidor
                    matrix_t* result = opMatrix->multMatrices(&arrMatrix.at(id-1), &arrMatrix.at(id-1));

                    //Si no se ha podido realizar la operación
                    if(result == NULL){
                        std::cout << "\nMatrices no compatibles.";
                    }else{
                        //Imprimimos la matriz resultado
                        std::cout << "\nResultado:";
                        std::cout << "\n\n\tFilas: " << result->rows;
                        std::cout << "\n\tColumnas: " << result->cols << "\n";
                        for(int i = 0; i < result->rows * result->cols; i++)
                            std::cout << "\n\tDato [" << i+1 << "]: " << result->data[i];
                    }

                    delete result;
                }
                
            }
                break;
                
        }


    }while(op != 6);


    arrMatrix.clear();

    delete opMatrix;
    delete fileName;

}

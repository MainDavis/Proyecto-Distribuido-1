#include "multmatrix_stub.h"

#define LEER_MATRIX	            'L'
#define ESCRIBIR_MATRIX 	 	'R'
#define MULT_MATRIX 	        'M'
#define CREATE_IDENTITY  	    'C'
#define CREATE_RANDOM  	        'A'

#define OP_EXIT			'E'
#define OP_OK			'O'

multmatrix_stub::multmatrix_stub(){

    char* ip=NULL;
    ip=new char[strlen(IP_SERVER)+1];
    memcpy(ip,IP_SERVER,strlen(IP_SERVER)+1);

    std::cout<<"INICIANDO CLIENTE\n";

    serverID=initClient(ip,PORT_SERVER);

    if(serverID==-1)
        std::cout<<"ERROR CLIENTE Fichero: "<< __FILE__ <<" Línea: "<< __LINE__ <<" Conexión no válida\n";

    delete ip;

}
/////
/////
multmatrix_stub::~multmatrix_stub(){

    char msg=OP_EXIT;
    sendMSG(serverID,(void*)&msg,sizeof(char));
    //recibir resultado
    char* buff=nullptr;
    int dataLen=0;
    char state=0;
    recvMSG(serverID, (void**)&buff, &dataLen);
    memcpy(&state,buff,sizeof(char));
    delete buff;

    if(state!=OP_OK)
        std::cout<<"ERROR cerrando conexion\n";

}
/////
/////
matrix_t* multmatrix_stub::readMatrix(const char* file){
    
    matrix_t* result = new matrix_t;
    char msg = LEER_MATRIX;
    int dataLen = 0;
    int *exito = nullptr, *buff = nullptr;
    
    //Enviamos la operación al server 
    sendMSG(serverID, (void*)&msg, sizeof(char));
    //Enviamos el nombre del fichero
    sendMSG(serverID, (void**)file, strlen(file)+1);

    //Recibimos si ha tenido exito
    recvMSG(serverID, (void**)&exito, &dataLen);
    if(*exito == 1){

        //Recibimos las columnas
        recvMSG(serverID, (void**)&buff, &dataLen);
        memcpy(&result->cols, buff, sizeof(int));

        //Recibimos las filas
        recvMSG(serverID, (void**)&buff, &dataLen);
        memcpy(&result->rows, buff, sizeof(int));

        //Recibimos los datos
        recvMSG(serverID, (void**)&buff, &dataLen);
        result->data = buff;
        
        return result;
    }else{
        std::cout<< "ERROR: Fichero " << std::string(file) <<" no existe\n";
        return NULL;
    }
    
}
/////
/////
matrix_t* multmatrix_stub::multMatrices(matrix_t* m1, matrix_t *m2){
    return NULL;
}
/////
/////
void multmatrix_stub::writeMatrix(matrix_t* m, const char *fileName){

}
/////
/////
matrix_t* multmatrix_stub::createIdentity(int rows, int cols){
    return NULL;
}
/////
/////
matrix_t* multmatrix_stub::createRandMatrix(int rows, int cols){

    matrix_t* result = new matrix_t;
    char msg = CREATE_RANDOM;
    int dataLen = 0;
    int* data = nullptr;

    //Enviamos la operación al server 
    sendMSG(serverID, (void*)&msg, sizeof(char));

    //Enviamos las filas y columnas
    data = new int[2];
    data[0] = rows;
    data[1] = cols;

    sendMSG(serverID, (void**)&data, sizeof(int)*2);
    delete data;
    //Ensamblamos la matriz
    result->cols = cols;
    result->rows = rows;

    data = new int[rows*cols];
    recvMSG(serverID, (void**)&data, &dataLen);
    result->data = data;

    delete data;

    return result;
}
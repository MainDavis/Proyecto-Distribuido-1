#pragma once
//linka con el server, reproduce la clase base

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include "utils.h"

using namespace std;

#define IP_SERVER "192.168.167.71"
#define PORT_SERVER  32001

class filemanager_stub
{
private:
    
    int serverID = 0;
    vector<string*> *listaServer = nullptr;
    std::string path = "./dirpruebaCliente/";

public:
    filemanager_stub();
    ~filemanager_stub();
    vector<string*>* listFiles();
    void readFile(char* fileName);
    void writeFile(char* fileName, vector<string*>* vListFiles);
};
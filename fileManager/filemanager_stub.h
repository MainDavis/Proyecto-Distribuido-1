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

#define IP_SERVER "127.0.0.1"
#define PORT_SERVER  3301

class filemanager_stub
{
private:
    
    int serverID = 0;
    std::string path = "./dirpruebaCliente/";

public:
    filemanager_stub();
    ~filemanager_stub();
    vector<string*>* listFiles();
    void readFile(char* fileName);
    void writeFile(char* fileName, vector<string*>* vListFiles);
};
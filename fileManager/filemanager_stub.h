#pragma once
//linka con el server, reproduce la clase base

#include "filemanager.h"

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "utils.h"

#define IP_SERVER "127.0.0.1"
#define PORT_SERVER  3301

class filemanager_stub
{
private:
    
    FileManager* ops = nullptr;
    int serverID = 0;
    string path = "./dirpruebaCliente/";

public:
    filemanager_stub();
    ~filemanager_stub();
    void listFiles();
    void readFile(char* fileName);
    void writeFile(char* fileName);
};
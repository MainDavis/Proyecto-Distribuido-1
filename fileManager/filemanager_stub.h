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
    
    int serverID = 0;

public:
    filemanager_stub(string path);
    ~filemanager_stub();
    vector<string*>* listFiles();
    void readFile(char* fileName);
    void writeFile(char* fileName);
    void freeListedFiles(vector<string*>* fileList);
};
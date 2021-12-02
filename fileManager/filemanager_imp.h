#pragma once
//linka con el server, reproduce la clase base

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "utils.h"

#include "filemanager.h"


class filemanager_imp{
private:
	FileManager* ops = nullptr;
	vector<string*> *listaServer = nullptr;
	bool salir=false;
	int clientID=0;
	string path = "./dirServer/";
public:
	filemanager_imp(int clientID);
	~filemanager_imp();
	void exec();
};

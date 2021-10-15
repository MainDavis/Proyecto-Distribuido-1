#pragma once
//linka con el cliente, reproduce la clase base

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "utils.h"
#include "multmatrix.h"


class multmatrix_imp{
private:
	multMatrix* ops=nullptr;
	bool salir=false;
	int clientID=0;
public:
	multmatrix_imp(int clientID);
	~multmatrix_imp();
	void exec();
};

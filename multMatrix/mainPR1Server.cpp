#include "operaciones_imp.h"
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <thread>
#include "utils.h"


void threadclient(int clientID){

    multmatrix_imp* ops = new multmatrix_imp(clientID);
    ops->exec();
	delete ops;
}



int main(int argc,char** argv){

	int idSocket=0;
	idSocket=initServer(3301);


	while(true)
	{
	
		if(checkNewConnections()){
		
			int clientID=getNewConnection();	
			std::thread* newThread=new std::thread(threadClient,clientID);
			newThread->detach();
		}
	}

	return 0;
}
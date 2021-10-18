#include "filemanager_imp.h"
#include "utils.h"

#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <thread>



void threadclient(int clientID){

    filemanager_imp* ops = new filemanager_imp(clientID);
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
			std::thread* newThread=new std::thread(threadclient,clientID);
			newThread->detach();
		}
	}

	return 0;
}
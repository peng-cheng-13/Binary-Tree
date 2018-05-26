#include "Alluxio.h"
#include "Util.h"
#include <stdlib.h>
#include <string.h>
#include <fstream>
#include <iostream>
#include <ctime>
#include <iomanip>
#include <chrono>
#include <functional>
#include <thread>
#include "JNIHelper.h"
#include <string>
using namespace tdms;

int main(int argc, char *argv[]){
	if(argc < 2){
		printf("invalid argment\n");
	}
	std::ifstream fin(argv[1]);
	std::string  input;
	std::string inputfilepath;
	std::string output = argv[2];
        std::string datapath = argv[3];
	std::string outputfilepath = datapath + "/" +output ;
	if(outputfilepath.find("/home/condor/alluxio-data")<outputfilepath.length())
                outputfilepath=outputfilepath.replace(0,26,"/");
	const char* outfile = outputfilepath.c_str();
	const char* infile;
	static char mydata[131072];
	printf("Ready to Init TDMS \n");
        TDMSClientContext acc;
        printf("Context successed \n");
	
	TDMSFileSystem stackFS(acc);
        jTDMSFileSystem client = &stackFS;
        printf("Init jTDMSFileSystem  successed \n");
        if(client->exists(outfile))
                client->deletePath(outfile, false);
        // Create file output stream
	TDMSCreateFileOptions* options = TDMSCreateFileOptions::getCreateFileOptions();
        //options->setDataAccessPattern("SCATTER");
        jFileOutStream fileOutStream = client->createFile(outfile, options);
	jFileInStream fileInStream;
	while ( getline(fin,input) ) 
    	{
		inputfilepath = datapath + "/" +input ;
		if(inputfilepath.find("/home/condor/alluxio-data")<inputfilepath.length())
	                inputfilepath=inputfilepath.replace(0,26,"/");
		infile = inputfilepath.c_str();
		fileInStream = client->openFile(infile);	
		while(fileInStream->read(mydata, 131071) != -1)
	                fileOutStream->write(mydata, strlen(mydata));
		fileInStream->close();
     	}
	fileOutStream->close();
        delete fileInStream;
        delete fileOutStream;
	return 0;
}


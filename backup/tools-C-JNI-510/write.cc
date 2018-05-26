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
	//argv[1], Outputfile name
	//argv[2], Data size
	//char* testfile =argv[1];
	std::string filename = argv[1];
	std::string datapath = argv[3];
	std::string filepath = datapath + "/" +filename ;
	std::cout << "Path of file is " << filepath << std::endl;
	if(filepath.find("/home/condor/alluxio-data")<filepath.length())
		filepath=filepath.replace(0,26,"/");
	std::cout << "Repalced file path is " << filepath << std::endl;
	char* testfile = (char*)filepath.data();
	int datasize = atoi(argv[2]);
	
	TDMSClientContext acc;
	printf("Context successed \n");
	TDMSFileSystem stackFS(acc);
        jTDMSFileSystem client = &stackFS;
        printf("Init jTDMSFileSystem  successed \n");
  	// Create file output stream
	TDMSCreateFileOptions* options = TDMSCreateFileOptions::getCreateFileOptions();
	options->setDataAccessPattern("PIPELINE");
	jFileOutStream fileOutStream = client->createFile(testfile, options);
	//Write 4GB file 
	char mydata[1048576];
  	std::chrono::duration<double> duration = std::chrono::duration<double>::zero();
  	std::chrono::time_point<std::chrono::system_clock> startTime, stopTime;
  	int i,j,k=0;
  	for(i=0;i<1048576;i++)
		mydata[i]='6';
	startTime = std::chrono::system_clock::now();
	for(j=0;j<datasize;j++){
  	    	fileOutStream->write(mydata, strlen(mydata));
	}
  	stopTime =  std::chrono::system_clock::now();
  	duration = stopTime - startTime;
  	std::cout << "Write 4GB to TDMS in " << duration.count() << " seconds" << std::endl;
	long bd = 4096/duration.count();
	std::cout << "Write Bandwidth is " <<  bd << "MB/s" << std::endl;
	fileOutStream->close();
	delete fileOutStream;
	return 0;
}


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
	std::string input = argv[1];
	std::string output = argv[2];
	std::string datapath = argv[4];
	std::string inputfilepath = datapath + "/" +input ;
	std::string outputfilepath = datapath + "/" +output ;
	std::cout << "Path of file is " << inputfilepath << std::endl;
	if(inputfilepath.find("/home/condor/alluxio-data")<inputfilepath.length())
		inputfilepath=inputfilepath.replace(0,26,"/");
	if(outputfilepath.find("/home/condor/alluxio-data")<outputfilepath.length())
		outputfilepath=outputfilepath.replace(0,26,"/");
	std::cout << "Repalced inputfile path is " << inputfilepath << std::endl;
	std::cout << "Repalced outputfile path is " << outputfilepath << std::endl;
	
	char* infile = (char*)inputfilepath.data();
	char* outfile = (char*)outputfilepath.data();

	int datasize = atoi(argv[3]);
	
	TDMSClientContext acc;
	printf("Context successed \n");
	TDMSFileSystem stackFS(acc);
        jTDMSFileSystem client = &stackFS;
        printf("Init jTDMSFileSystem  successed \n");
  	// Create file output stream
	TDMSCreateFileOptions* options = TDMSCreateFileOptions::getCreateFileOptions();
	options->setDataAccessPattern("PIPELINE");
	jFileOutStream fileOutStream = client->createFile(outfile, options);
	jFileInStream fileInStream = client->openFile(infile);
	
	//Write 4GB file 
	char mydata[1048576];
  	std::chrono::duration<double> duration = std::chrono::duration<double>::zero();
  	std::chrono::time_point<std::chrono::system_clock> startTime, stopTime;
	while(fileInStream->read(mydata, 1048577) != -1)
		fileOutStream->write(mydata, strlen(mydata));
  	stopTime =  std::chrono::system_clock::now();
  	duration = stopTime - startTime;
  	std::cout << "Binary in  " << duration.count() << " seconds" << std::endl;
	//long bd = 4096/duration.count();
	//std::cout << "Write Bandwidth is " <<  bd << "MB/s" << std::endl;
	fileInStream->close();
	fileOutStream->close();
	delete fileInStream;
	delete fileOutStream;
	return 0;
}


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
	std::string input2 = argv[2];
	std::string output = argv[3];
	std::string datapath = argv[4];
	std::string inputfilepath = datapath + "/" +input ;
	std::string inputfilepath2 = datapath + "/" +input2 ;
	std::string outputfilepath = datapath + "/" +output ;
	std::cout << "Path of file is " << inputfilepath << std::endl;
	if(inputfilepath.find("/home/condor/alluxio-data")<inputfilepath.length())
		inputfilepath=inputfilepath.replace(0,26,"/");
	if(inputfilepath2.find("/home/condor/alluxio-data")<inputfilepath2.length())
                inputfilepath2=inputfilepath2.replace(0,26,"/");
	if(outputfilepath.find("/home/condor/alluxio-data")<outputfilepath.length())
		outputfilepath=outputfilepath.replace(0,26,"/");
	std::cout << "Repalced inputfile path is " << inputfilepath << std::endl;
	std::cout << "Repalced outputfile path is " << outputfilepath << std::endl;
	
	const char* infile = inputfilepath.c_str();
	const char* infile2 = inputfilepath2.c_str();
	const char* outfile = outputfilepath.c_str();

	//int datasize = atoi(argv[3]);
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
	//options->setDataAccessPattern("GATHER","cn17662-enp5s0");
	jFileOutStream fileOutStream = client->createFile(outfile, options);
	jFileInStream fileInStream = client->openFile(infile);
	jFileInStream fileInStream2 = client->openFile(infile2);
	//Write 1GB file 
	static char mydata[131072];
	int i;
  	std::chrono::duration<double> duration = std::chrono::duration<double>::zero();
  	std::chrono::time_point<std::chrono::system_clock> startTime, stopTime;
	for( i=0;i<8192;i++){
		if(fileInStream->read(mydata, 131071) != -1)
			fileOutStream->write(mydata, strlen(mydata));
		if(fileInStream2->read(mydata, 131071) != -1)
                	fileOutStream->write(mydata, strlen(mydata));
	}
  	stopTime =  std::chrono::system_clock::now();
  	duration = stopTime - startTime;
  	std::cout << "Process in  " << duration.count() << " seconds" << std::endl;
	//long bd = 4096/duration.count();
	//std::cout << "Write Bandwidth is " <<  bd << "MB/s" << std::endl;
	fileInStream->close();
	fileInStream2->close();
	fileOutStream->close();
	delete fileInStream;
	delete fileInStream2;
	delete fileOutStream;
	
	return 0;
}


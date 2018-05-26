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
using namespace tdms;

int main(int argc, char *argv[]){

        char* testfile = "/testfile-c-jni";
        TDMSClientContext acc;
        printf("Context successed \n");
        TDMSFileSystem stackFS(acc);
        jTDMSFileSystem client = &stackFS;
        printf("Init jTDMSFileSystem  successed \n");
	
	char mydata[1048576];
        std::chrono::duration<double> duration = std::chrono::duration<double>::zero();
        std::chrono::time_point<std::chrono::system_clock> startTime, stopTime;
        int i,j,k=0;
        char content[] = "hello, alluxio!!";
        jFileInStream fileInStream = client->openFile(testfile); 
        startTime = std::chrono::system_clock::now();
        for(j=0;j<4096;j++){
                fileInStream->read(mydata, 1048577);
		if(j==0)
			std::cout << "mydata [20] = " << mydata[20]  << std::endl;
        }
        stopTime =  std::chrono::system_clock::now();
        duration = stopTime - startTime;
        std::cout << "Read 4GB from TDMS in " << duration.count() << " seconds" << std::endl;
        long bd = 4096/duration.count();
        std::cout << "Read Bandwidth is " <<  bd << "MB/s" << std::endl;
        fileInStream->close();
        delete fileInStream;
        return 0;
}

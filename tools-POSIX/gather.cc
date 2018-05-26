#include <stdlib.h>
#include <string.h>
#include <fstream>
#include <iostream>
#include <ctime>
#include <iomanip>
#include <string>

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
	const char* outfile = outputfilepath.c_str();
	const char* infile;
	static char data[131072];
	int rc;
	FILE *fp, *of;
	of=fopen(outfile,"wb");
	while ( getline(fin,input) ) 
    	{
		inputfilepath = datapath + "/" +input ; 
		infile = inputfilepath.c_str();
		fp=fopen(infile,"r");
		while(1){
                	rc = fread(data,sizeof(char),131072,fp);
                	if(rc <= 0)
                    		break;
                	else
                    		fwrite(data,sizeof(char),131072,of);
		}
     		fclose(fp);
	}
	fclose(of);
	return 0;
}


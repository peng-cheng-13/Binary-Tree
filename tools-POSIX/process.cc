#include<stdio.h>
#include<stdlib.h>
#include <iostream>
#include<string.h>
int main( int argc, char *argv[])
{
	if(argc < 2){
                printf("invalid argment\n");
        }
	std::string input = argv[1];
        std::string output = argv[2];
        std::string datapath = argv[3];
        std::string inputfilepath = datapath + "/" +input ;
        std::string outputfilepath = datapath + "/" +output ;
        
	const char* infile = inputfilepath.c_str();
        const char* outfile = outputfilepath.c_str();

	
	static char data[131072];
        int i,j=0;
	int rc;
        FILE *fp, *of;
	//fp=fopen("/ssd/testfile-c-posix","r");
        //fp=fopen("/home/condor/alluxio-data/testfile-c-posix","r");
	//fp=fopen("/mnt/ramdisk/testfile-c-posix","r");
        fp=fopen(infile,"r");
	of=fopen(outfile,"wb");
	 while(1){
                rc = fread(data,sizeof(char),131072,fp);
                if(rc <= 0)
                    break;
                else
                    fwrite(data,sizeof(char),131072,of);

        }
		
        fclose(fp);
	fclose(of);

        return 0;
}


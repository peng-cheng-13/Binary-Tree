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
        std::string input2 = argv[2];
        std::string output = argv[3];
        std::string datapath = argv[4];
        std::string inputfilepath = datapath + "/" +input ;
        std::string inputfilepath2 = datapath + "/" +input2 ;
        std::string outputfilepath = datapath + "/" +output ;
        
	const char* infile = inputfilepath.c_str();
        const char* infile2 = inputfilepath2.c_str();
        const char* outfile = outputfilepath.c_str();

	
	char data[131072];
        int i,j=0;
	int rc;
        FILE *fp1, *fp2, *of;
	//fp=fopen("/ssd/testfile-c-posix","r");
        //fp=fopen("/home/condor/alluxio-data/testfile-c-posix","r");
	//fp=fopen("/mnt/ramdisk/testfile-c-posix","r");
        fp1=fopen(infile,"r");
	fp2=fopen(infile2,"r");
	of=fopen(outfile,"wb");
	
	for(i=0;i<8192;i++){
		if(fread(data,sizeof(char),131072,fp1)!= -1)
			fwrite(data,sizeof(char),131072,of);
		if(fread(data,sizeof(char),131072,fp2)!= -1)
        	       fwrite(data,sizeof(char),131072,of);
	}
        fclose(fp1);
	fclose(fp2);
	fclose(of);

        return 0;
}


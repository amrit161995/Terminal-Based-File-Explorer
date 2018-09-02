#include <stdio.h>
#include <stdlib.h>
#include<iostream>
#include<dirent.h>
#include<string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include<vector>
#include <pwd.h>
#include<unistd.h>
#include <grp.h>
#include <unistd.h>
using namespace std;


void snapshot(FILE *fptr,string source,string path,int slength){
	source=realpath(source.c_str(),NULL);	
	struct dirent *dtr,*dtr1;
	struct stat f_info,f_info1;
	string path1,path2;
	chdir(path.c_str());
	stat(source.c_str(), &f_info);
	

	if(S_ISDIR(f_info.st_mode)){
	chdir(source.c_str());
			
	
	DIR *dir=opendir(".");
	
	//source=getPath();
	while((dtr=readdir(dir))!=NULL){
			
			stat(dtr->d_name, &f_info1);
			if(dtr->d_name[0]=='.')
					continue;
				fprintf(fptr,"%s	",dtr->d_name);
			
	
	}
	
	fprintf(fptr,"\n\n");
	chdir(source.c_str());
	DIR *dir1=opendir(".");
	while((dtr=readdir(dir1))!=NULL){
	if(dtr->d_type == DT_DIR){
				
				if(dtr->d_name[0]=='.')
					continue;
				
				path2=realpath(dtr->d_name,NULL);
				path2=path2.replace(0,slength,".");
				fprintf(fptr,"%s: \n",path2.c_str());
				path1=source+"/"+dtr->d_name;
				snapshot(fptr,path1,path,slength);
				
			
				
			}
			
	
	}
	//relative=rel;
	chdir("..");
	closedir(dir1);
}
return;
}




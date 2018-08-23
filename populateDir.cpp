#include<iostream>
#include<dirent.h>
#include<string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include<time.h>
#include<vector>
using namespace std;
#include "functions.h"
#include "fileAttributes.cpp"
//to create the list of drectory and file names
void populateDir(int arg,char **args){
	vector <struct dirent*> dtr_array;
	struct dirent *dtr;
	struct stat f_info;
	
	DIR *dir=opendir(".");
	if(dir==NULL)
		cout<<"Cannot display file"<<endl;
	else{
		while((dtr=readdir(dir))!=NULL){
			//dtr_array.push_back(dtr);
			stat(dtr->d_name, &f_info);
			
			permissions(dtr,f_info);
			ownership(f_info.st_uid,f_info.st_gid);
			sizeInKB(f_info);
			fileName(dtr);
			lastModified(f_info);
					
		
		}
	}
	closedir(dir);
}


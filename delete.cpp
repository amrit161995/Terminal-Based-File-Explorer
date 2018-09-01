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
using namespace std;
struct dirent *dtr,*dtr1;
struct stat f_info,f_info1;
string path1;
void delete_file(string path)
{
path=realpath(path.c_str(),NULL);
chdir(path.c_str());
remove(path.c_str());
}


void delete_dir(string path){
	path=realpath(path.c_str(),NULL);
	stat(path.c_str(), &f_info);
	if(S_ISDIR(f_info.st_mode)){
				//mkdir((target+"/"+source).c_str(),0777);
				chdir(path.c_str());
			
	
	
	DIR *dir=opendir(".");

	while((dtr=readdir(dir))!=NULL){
			//cout<<dtr->d_name;
			
			stat(dtr->d_name, &f_info1);
			if(dtr->d_type==DT_REG) {	
				
				remove(dtr->d_name);
				
			}
			else{
			
				
				if(strcmp(dtr->d_name,".")==0 || strcmp(dtr->d_name,"..")==0)
					continue;
				string temp=dtr->d_name;
				path1=path+"/"+dtr->d_name;
				delete_dir(path1);
				//cout<<temp<<" ";
				rmdir(temp.c_str());
			}
	
	}
		
	chdir("..");
	closedir(dir);
	}
	
return;
}

void delete_fun(string path){
stat(path.c_str(), &f_info);
if(S_ISDIR(f_info.st_mode))
	delete_dir(path);
else
	delete_file(path);
}


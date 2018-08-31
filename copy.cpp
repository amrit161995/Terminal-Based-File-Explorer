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

struct dirent *dtr,*dtr1;
struct stat f_info,f_info1;
string path1,path2;

void copy_file(char source[100],char target[100]){
FILE *fptr1, *fptr2;
    char c;
 
    fptr1 = fopen(source, "r");
    if (fptr1 == NULL)
    {
        return;
    }
 
   
    fptr2 = fopen(target, "w");
    if (fptr2 == NULL)
    {
      return;
    }
 
    c = fgetc(fptr1);
    while (c != EOF)
    {
        fputc(c, fptr2);
        c = fgetc(fptr1);
    }
 
   
 
    fclose(fptr1);
    fclose(fptr2);

return;

}

void copy_dir(string source,string target){
	
	stat(source.c_str(), &f_info);
	

	if(S_ISDIR(f_info.st_mode)){
				mkdir((target+"/"+source).c_str(),0777);
				chdir(source.c_str());
			
	
	
	DIR *dir=opendir(".");

	//source=getPath();
	while((dtr=readdir(dir))!=NULL){
			stat(dtr->d_name, &f_info1);
			if(dtr->d_type==DT_REG) {	
				
				string target2=target+"/"+source+"/"+dtr->d_name;
				char *tar = new char[target2.length() + 1]; 
				strcpy(tar, target2.c_str());
				copy_file(dtr->d_name,tar);
				
			}
			else{
			path1=target+"/"+source;
				
				if(strcmp(dtr->d_name,".")==0 || strcmp(dtr->d_name,"..")==0)
					continue;
				
				copy_dir(dtr->d_name,path1);
			}
	
	}
		
	chdir("..");
	closedir(dir);
	}
	
return;
}

void copy(string source,string target){
stat(source.c_str(), &f_info);
	if(S_ISDIR(f_info.st_mode))
		copy_dir(source,target);
	else{
		string target3=target+"/"+source;
		char *sour = new char[source.length()+1];
		strcpy(sour, source.c_str());
		char *targ = new char[target3.length() + 1]; 
		strcpy(targ, target3.c_str());
		copy_file(sour,targ);
			
	}
}



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

struct dirent *dtrc,*dtr1c;
struct stat f_infoc,f_info1c;
string path1c,path2c;

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
	target=realpath(target.c_str(),NULL);
	stat(source.c_str(), &f_infoc);
	

	if(S_ISDIR(f_infoc.st_mode)){
				mkdir((target+"/"+source).c_str(),0777);
				chdir(source.c_str());
			
	
	
	DIR *dirc=opendir(".");

	//source=getPath();
	while((dtrc=readdir(dirc))!=NULL){
			stat(dtrc->d_name, &f_info1c);
			if(dtrc->d_type==DT_REG) {	
				
				string target2=target+"/"+source+"/"+dtrc->d_name;
				char *tar = new char[target2.length() + 1]; 
				strcpy(tar, target2.c_str());
				copy_file(dtrc->d_name,tar);
				
			}
			else{
			path1c=target+"/"+source;
				
				if(strcmp(dtrc->d_name,".")==0 || strcmp(dtrc->d_name,"..")==0)
					continue;
				
				copy_dir(dtrc->d_name,path1c);
			}
	
	}
		
	chdir("..");
	closedir(dirc);
	}
	
return;
}

void copy(string source,string target){
stat(source.c_str(), &f_infoc);
	if(S_ISDIR(f_infoc.st_mode))
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


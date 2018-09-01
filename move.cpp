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
#include"delete.cpp"
#include"copy.cpp"
using namespace std;


void move(string source,string target){
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



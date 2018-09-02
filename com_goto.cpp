#include<dirent.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include<iostream>
#include"list.h"
#include"cursor.h"
using namespace std;

int goto_fun(string path){
	vector<struct dirent*> dtr_array;
	int no_of_files;
	if(path=="/"){
		chdir(getenv("PWD"));
		cursor();
	}
	else{
		string relative=realpath(path.c_str(),NULL);
		string root=getenv("PWD");
		if(relative.substr(0,root.length())==root)
			chdir(path.c_str());
		cursor();
	}
	
return 1;
}



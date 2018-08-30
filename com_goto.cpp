#include<dirent.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include<iostream>
using namespace std;

int goto_fun(string path){
	vector<struct dirent*> dtr_array;
	int no_of_files;
	if(path=="/"){
		chdir(getenv("PWD"));
		dtr_array=populateDir();
		no_of_files=(int)dtr_array.size();
		if(no_of_files>=20)
			printDir(0,19,dtr_array);
		else	
			printDir(0,no_of_files-1,dtr_array);
	}
	else{
		chdir(path.c_str());
		dtr_array=populateDir();
		no_of_files=(int)dtr_array.size();
		if(no_of_files>=20)
			printDir(0,19,dtr_array);
		else
			printDir(0,no_of_files-1,dtr_array);
	}
	
return 1;
}



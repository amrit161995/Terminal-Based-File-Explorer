
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include<iostream>
#include"list.cpp"
using namespace std;

int goto_fun(string path){
	if(path=="/"){
		chdir(getenv("PWD"));
		populateDir();
	}
	else{
		chdir(path.c_str());
		populateDir();
	}
return 0;
}

int main(){
string path;
cin>>path;

goto_fun(path);
return 0;
}

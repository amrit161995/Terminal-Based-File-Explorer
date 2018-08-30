#include<string>
#include<iostream>
#include<stdio.h>

using namespace std;


void rename_fun(string oldname,string newname){
   int retv;
   retv = rename(oldname.c_str(), newname.c_str());
}






#include<iostream>
#include <stdio.h>
#include <stdlib.h>
#include<dirent.h>
#include<string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include<time.h>
#include<vector>
#include <pwd.h>
#include <grp.h>
#include <unistd.h>
#ifndef INC_LIST_H
#define INC_LIST_H
using namespace std;
string getPath();
void permissions(struct dirent *dtr,struct stat f_info);
void ownership(int uid,int gid);
void sizeInKB(struct stat f_info);
void lastModified(struct stat f_info);
void fileName(struct dirent *dtr);
vector <struct dirent*> populateDir();
void printDir(int lower,int upper,vector <struct dirent*> dtr_array);
#endif  


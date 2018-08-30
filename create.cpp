#include<dirent.h>
#include<vector>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include<iostream>
#include <stack>

#include <sys/stat.h>
#include <algorithm>
#include <bits/stdc++.h>
#include <limits.h>


void create_file(string name,string destination){
FILE *fptr;
chdir(destination.c_str());
opendir(".");
string path=name;
 fptr = fopen(path.c_str(), "w");
    if (fptr == NULL)
    {
       exit(0);
    }
fclose(fptr);
}

void create_dir(string name,string destination)
{
chdir(destination.c_str());
opendir(".");
if( mkdir(name.c_str(),0777) && errno != EEXIST );
else
	mkdir(name.c_str(),0777);
}



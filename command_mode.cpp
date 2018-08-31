#include <bits/stdc++.h>
#include"com_goto.cpp"
#include"create.cpp"
#include"rename.cpp"
#include<dirent.h>
#include<vector>
#include"command_mode.h"
#include"cursor.h"
#include"list.h"
using namespace std;
int command_mode(string path)
{	vector<struct dirent *> dtr_array;
	string s;	
	getline(cin,s);
	vector <string> command;
	stringstream check1(s);
     	string token;
     	while(getline(check1, token, ' '))
        	command.push_back(token);
    	if(command[0]=="goto"){
		printf("\033[2J");
		goto_fun(command[1]);
		printf("\e[23;1H");
		printf("COMMAND MODE\n");
		printf("\e[24;1H");
		printf(":");
		command_mode(path);
	}

	if(command[0]=="create_file"){
		printf("\033[2J");
		create_file(command[1],command[2]);
		chdir(path.c_str());
		dtr_array=populateDir();
		int no_of_files=(int)dtr_array.size();
		if(no_of_files>=20)
			printDir(0,19,dtr_array);
		else	
			printDir(0,no_of_files-1,dtr_array);
		printf("\e[23;1H");
		printf("COMMAND MODE\n");
		printf("\e[24;1H");
		printf(":");
		command_mode(path);
		
		
	}

	if(command[0]=="create_dir"){
		printf("\033[2J");
		create_dir(command[1],command[2]);
		chdir(path.c_str());
		dtr_array=populateDir();
		int no_of_files=(int)dtr_array.size();
		if(no_of_files>=20)
			printDir(0,19,dtr_array);
		else	
			printDir(0,no_of_files-1,dtr_array);
		printf("\e[23;1H");
		printf("COMMAND MODE\n");
		printf("\e[24;1H");
		printf(":");
		command_mode(path);
		
		
	}
	if(command[0]=="rename"){
		printf("\033[2J");
		rename_fun(command[1],command[2]);
		chdir(path.c_str());
		dtr_array=populateDir();
		int no_of_files=(int)dtr_array.size();
		if(no_of_files>=20)
			printDir(0,19,dtr_array);
		else	
			printDir(0,no_of_files-1,dtr_array);
		printf("\e[23;1H");
		printf("COMMAND MODE\n");
		printf("\e[24;1H");
		printf(":");
		command_mode(path);	
	}
	return 0;
}


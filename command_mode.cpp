#include <bits/stdc++.h>
#include"com_goto.cpp"
using namespace std;
int command_mode()
{
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
		//printf("\e[1;1H");
		
		
		command_mode();
	}
	return 0;
}


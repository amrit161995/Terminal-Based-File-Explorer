#include <bits/stdc++.h>
#include"com_goto.cpp"
#include"create.cpp"
#include"rename.cpp"
#include"move.cpp"
#include"snapshot.cpp"
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
	if(command.size()<1){
		printf("\033[2J");
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
    	if(command[0]=="goto"){
		printf("\033[2J");
		if(command.size()>1)
			goto_fun(command[1]);
		printf("\e[23;1H");
		printf("COMMAND MODE\n");
		printf("\e[24;1H");
		printf(":");
		//command_mode(path);
	}

	else if(command[0]=="create_file"){
		printf("\033[2J");
		if(command.size()>2)
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
	
	else if(command[0]=="create_dir"){
		printf("\033[2J");
		if(command.size()>2)
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
	else if(command[0]=="rename"){
		printf("\033[2J");
		if(command.size()>2)
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

	else if(command[0]=="copy"){
		printf("\033[2J");
		if(command.size()>2){
			for(int i=0;i<command.size()-2;i++)
				copy(command[i+1],command[command.size()-1]);
		}
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
	
	else if(command[0]=="move"){
		printf("\033[2J");
		if(command.size()>2){
			for(int i=0;i<command.size()-2;i++){
				copy(command[i+1],command[command.size()-1]);
				delete_fun(command[i+1]);
				rmdir(command[i+1].c_str());
			}
		}
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

	else if(command[0]=="delete_file"){
		printf("\033[2J");
		if(command.size()>1){
			delete_file(command[1]);
			//rmdir(command[1].c_str());
		}
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

	else if(command[0]=="delete_dir"){
		printf("\033[2J");
		if(command.size()>1){
			delete_dir(command[1]);
			rmdir(command[1].c_str());
		}
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
		
	else if(command[0]=="snapshot"){
		printf("\033[2J");
		FILE *fptr;
		if(command.size()>2){
			string source=command[1];
		
   			fptr = fopen(command[2].c_str(),"w");
			if(fptr == NULL)
   			{
      			exit(1);             
   			}
			string relative=realpath(source.c_str(),NULL);
			int slen=relative.length();
 			snapshot(fptr,source,command[2],slen);
			fclose(fptr); 
		}
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
	else if(command[0]=="n"||command[0]=="normal"||command[0]=="Normal"||command[0]=="normalmode"||command[0]=="escape"||command[0]=="esc"){
		printf("\033[2J");
		goto_fun(path);
		printf("\e[23;1H");
		printf("COMMAND MODE\n");
		printf("\e[24;1H");
		printf(":");
		
		
	}
	else if(command[0]=="quit" || command[0]=="q"){
		printf("\033[2J");
			
	}
	else{
		printf("\033[2J");
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


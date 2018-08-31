#include<dirent.h>
#include<vector>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include<iostream>
#include <stack>
#include"list.h"
#include <sys/stat.h>
#include <algorithm>
#include <bits/stdc++.h>
#include <limits.h>
#include"command_mode.h" 
#include"cursor.h"

using namespace std;
struct termios saved_attributes;
vector <string> dirStack_f;		//forward
vector <string> dirStack_b;		//backward



void reset_input_mode()
{
  tcsetattr (STDIN_FILENO, TCSANOW, &saved_attributes);
}

void set_input_mode()
{

  struct termios tattr;
  char *name;

  if (!isatty (STDIN_FILENO))
    {
      fprintf (stderr, "Not a terminal.\n");
      exit (EXIT_FAILURE);
    }

  
  tcgetattr (STDIN_FILENO, &saved_attributes);
  atexit (reset_input_mode);

  tattr=saved_attributes;
  tcgetattr (STDIN_FILENO, &tattr);
  tattr.c_lflag &= ~(ICANON|ECHO); 
  tattr.c_cc[VMIN] = 1;
  tattr.c_cc[VTIME] = 0;
  tcsetattr (STDIN_FILENO, TCSANOW, &tattr);
}

void cursor(){
	
	set_input_mode();
	vector<struct dirent*> dtr_array;
	int no_of_files;
	string path;
	struct stat f_info;
	char c;
	dirStack_b.push_back(getenv("PWD"));
	DIRECTORY:
	int cursorindex=0;
	
	printf("\033[2J");
	printf("\e[1;1H");
  	//printf("%s\n",getPath().c_str());
	
	dtr_array=populateDir();
	no_of_files=(int)dtr_array.size();
	if(no_of_files>=20)
		printDir(0,19,dtr_array);
	else
		printDir(0,no_of_files-1,dtr_array);
	printf("\e[24;1H");
	printf("NORMAL MODE");
	printf("\e[2;1H");
	
	int low=0;
	int up=19;
	int upperindex=0;
while (1)
    {
      scanf("%c",&c);
	if(cursorindex<0)
		cursorindex=0;
	if(cursorindex>=no_of_files)
		cursorindex=no_of_files-1;

     	if (c == 65 && cursorindex>0){      			//up arrow key
       		printf("\e[1A");
		cursorindex--;
		
		if(cursorindex<upperindex && low>0){
			low--;
			up--;
			printDir(low,up,dtr_array);
			printf("\e[24;1H");
			printf("NORMAL MODE");
			printf("\e[2;1H");
		}
	}


    	if(c == 66 && cursorindex<no_of_files-1){		//down arrow key
		cursorindex++;		
		printf("\e[1B");
		
		if(cursorindex>=20 && up<no_of_files-1){
			low++;
			up++;
			upperindex=low;
			printDir(low,up,dtr_array);
			printf("\e[24;1H");
			printf("NORMAL MODE");
			printf("\e[21;1H");
		}
		
		
	}

 	if(c == 67){
		dirStack_b.push_back(realpath(getPath().c_str(),NULL));						//right arrow key
		if(!dirStack_f.empty()){
			path=dirStack_f[dirStack_f.size()-1];
			dirStack_f.pop_back();
			chdir(path.c_str());
			goto DIRECTORY;
		}

	}
 	if(c == 68){							//left arrow key
		if(!dirStack_b.empty()){
			
			if(dirStack_b.size()>1){
				
				dirStack_f.push_back(dirStack_b[dirStack_b.size()-1]);
				dirStack_b.pop_back();
			
				path=dirStack_b[dirStack_b.size()-1];
				
			chdir(path.c_str());
			goto DIRECTORY;
			}
			//cout<<dirStack_b.size();
			
			
			
		}

	}
		
    	
		

	if(c=='\n'){									//enter key pressed
		stat(dtr_array[cursorindex]->d_name,&f_info);
		if(S_ISDIR(f_info.st_mode)){
			path=realpath(dtr_array[cursorindex]->d_name,NULL);
			dirStack_b.push_back(path);
			//cout<<path;
			chdir(dtr_array[cursorindex]->d_name);//entering into a directory!
			goto DIRECTORY;
			//printf("hello");
			
		}
		else{
			pid_t pid;
			pid=fork();
			if (pid == 0) {
  			execl("/usr/bin/xdg-open", "xdg-open",dtr_array[cursorindex]->d_name, (char *)0);
  			exit(1);
			}
			//chdir(".");
			//goto DIRECTORY;

		}
	}
	
	if(c==127){
							//backspace key								
		dirStack_b.push_back(realpath(getPath().c_str(),NULL));
		chdir("..");//up one level
		goto DIRECTORY;
	}

	if(c==';' || c== ':'){
		printf("\e[23;1H");
		printf("COMMAND MODE\n");
		printf("\e[24;1H");
		printf("              ");
		printf("\e[24;1H");
		printf(":");
		reset_input_mode();
		break;
		
	}

	if(c=='h'){
		dirStack_b.push_back(realpath(getPath().c_str(),NULL));
		chdir(getenv("PWD"));
		goto DIRECTORY;	

	}
	
    }

	if(c==';' || c==':'){
		//set_input_mode();
		command_mode(realpath(getPath().c_str(),NULL));
	}



}



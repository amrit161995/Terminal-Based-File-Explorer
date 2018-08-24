#include<dirent.h>
#include<vector>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include<iostream>
#include <stack>
#include"list.cpp"
#include <algorithm>
struct termios saved_attributes;
vector <struct dirent*> dirStack;
int stack_top=-1;


void reset_input_mode (void)
{
  tcsetattr (STDIN_FILENO, TCSANOW, &saved_attributes);
}

void set_input_mode (void)
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
vector<struct dirent*> dtr_array;
int no_of_files;
int cursorindex=0;

printf("\033[2J");
printf("\e[1;1H");
//printf("hello");
  char c;
dtr_array=populateDir();
no_of_files=(int)dtr_array.size();

printf("\e[1;1H");


  while (1)
    {
      scanf("%c",&c);
	
     	if (c == 65 && cursorindex>0 ){      
       		printf("\e[1A");
		cursorindex--;
	}
    	if(c == 66 && cursorindex<no_of_files-1){
		printf("\e[1B");
		cursorindex++;
	}
 	if(c == 67)
		printf("right");
 	if(c == 68){
		printf("left");
		cout<<dirStack.size();
		if(dirStack.size()!=0){
		
			struct dirent* temp=dirStack[stack_top];
			 
			chdir(temp->d_name);
			cursor();
			stack_top--;
			//dirStack.pop();
		}

	}
		
    	
		

	if(c=='\n'){
		printf("\033[2J");
		printf("\e[1;1H");
	//	dirStack.push_back(dtr_array[cursorindex]);
		chdir(dtr_array[cursorindex]->d_name);//entering into a directory!
		dtr_array=populateDir();
		no_of_files=(int)dtr_array.size();
		cursorindex=0;
	//	stack_top++;
		
		printf("\e[1;1H");
	}
	
	if(c==127){
		printf("\033[2J");
		printf("\e[1;1H");
		chdir("..");//up one level
		dtr_array=populateDir();
		no_of_files=(int)dtr_array.size();
		cursorindex=0;
		printf("\e[1;1H");
	}

	if(c==';'){
		printf("\033[2J");
		printf("\e[1;1H");
		break;
	}
	
    }

}
int main (int a,char **ar)
{
set_input_mode ();
cursor();

  return 0;
}


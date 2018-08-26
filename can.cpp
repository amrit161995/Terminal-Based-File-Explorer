#include<dirent.h>
#include<vector>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include<iostream>
#include <stack>
#include"list.cpp"
#include <sys/stat.h>
#include <algorithm>
#include <limits.h>

struct termios saved_attributes;
vector <string> dirStack_f;		//forward
vector <string> dirStack_b;		//backward


string getPath(){
 char cwd[PATH_MAX];
  string a;
   if (getcwd(cwd, sizeof(cwd)) != NULL) {
	a=cwd;
     return a;
   }

}
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
	string path;
	struct stat f_info;
	char c;
	DIRECTORY:
	int cursorindex=0;
	
	printf("\033[2J");
	printf("\e[1;1H");
  	
	
	dtr_array=populateDir();
	no_of_files=(int)dtr_array.size();
	if(no_of_files>=20)
		printDir(0,19,dtr_array);
	else
		printDir(0,no_of_files-1,dtr_array);
	printf("\e[24;1H");
	printf("NORMAL MODE");
	printf("\e[1;1H");
	
	int low=0;
	int up=19;
	int upperindex=0;
	//dirStack_b.push("/");
    while (1)
    {
      scanf("%c",&c);
	if(cursorindex<0)
		cursorindex=0;
	if(cursorindex>=no_of_files)
		cursorindex=no_of_files-1;

     	if (c == 65 && cursorindex>0 ){      			//up arrow key
       		printf("\e[1A");
		cursorindex--;
		
		if(cursorindex<upperindex && low>0){
			low--;
			up--;
			printDir(low,up,dtr_array);
			printf("\e[24;1H");
			printf("NORMAL MODE");
			printf("\e[1;1H");
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
			printf("\e[20;1H");
		}
		
		
	}

 	if(c == 67)							//right arrow key
		printf("right");


 	if(c == 68){							//left arrow key
		//printf("left");
		
		if(!dirStack_b.empty()){
			path=dirStack_b[dirStack_b.size()-1];
			dirStack_b.pop_back(); 
			chdir(path.c_str());
			goto DIRECTORY;
			
			//cout<<dirStack_b.size();
			
			
			
		}

	}
		
    	
		

	if(c=='\n'){									//enter key pressed
		stat(dtr_array[cursorindex]->d_name,&f_info);
		if(S_ISDIR(f_info.st_mode)){
			path=getPath();
			//if(path!="/home/amrit")
			
			//cout<<path;
			chdir(dtr_array[cursorindex]->d_name);//entering into a directory!
			//dirStack_b.push_back(path);
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
		//dirStack_b.push(getPath());
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
		chdir(getenv("PWD"));
		goto DIRECTORY;	

	}
	
    }
	if(c==';' || c==':'){
		string s;	
		cin>>s;
	}

}

int main (int a,char **ar)
{

set_input_mode ();
cursor();

  return 0;
}


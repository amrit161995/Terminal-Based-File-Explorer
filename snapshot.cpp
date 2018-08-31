#include<iostream>
#include<dirent.h>
#include<string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include<time.h>
#include<vector>
#include <pwd.h>
#include <grp.h>
#include <unistd.h>
using namespace std;

void populateDir(string path){
	vector <struct dirent*> dtr_array;
	struct dirent *dtr;
	struct stat f_info;
	chdir(realpath(path.c_str(),NULL));
	DIR *dir=opendir(".");
	if(dir==NULL)
		cout<<"Cannot display file"<<endl;
	else{
		while(dtr=readdir(dir)){
			//dtr_array.push_back(dtr);
			stat(dtr->d_name, &f_info);
			
			if(dtr->d_type==DT_DIR){
				//cout<<"a";
				if(dtr->d_name[0]=='.')
					continue;
				//chdir(dtr->d_name);
				cout<<"-----------------"<<endl;		
				cout<<dtr->d_name<<endl;
				cout<<"-----------------"<<endl;
				populateDir(dtr->d_name);
				//cout<<endl;
			}
			else
				cout<<dtr->d_name<<endl;
			
					
		
		}
		


	}
	closedir(dir);

//return dtr_array;
}
int main()
{
populateDir("/home/amrit/Desktop/project");
}







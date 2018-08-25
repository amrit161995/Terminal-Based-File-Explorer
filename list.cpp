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

//to convert size from bytes to KB


void permissions(struct dirent *dtr,struct stat f_info){
	stat(dtr->d_name, &f_info);
	printf("  ");
	printf( (S_ISDIR(f_info.st_mode)) ? "d" : "-");
  	printf( (f_info.st_mode & S_IRUSR) ? "r" : "-");
   	printf( (f_info.st_mode & S_IWUSR) ? "w" : "-");
    	printf( (f_info.st_mode & S_IXUSR) ? "x" : "-");
    	printf( (f_info.st_mode & S_IRGRP) ? "r" : "-");
    	printf( (f_info.st_mode & S_IWGRP) ? "w" : "-");
    	printf( (f_info.st_mode & S_IXGRP) ? "x" : "-");
    	printf( (f_info.st_mode & S_IROTH) ? "r" : "-");
    	printf( (f_info.st_mode & S_IWOTH) ? "w" : "-");
    	printf( (f_info.st_mode & S_IXOTH) ? "x" : "-");
}

void ownership(int uid,int gid){
	struct passwd *pw = getpwuid(uid);
	struct group  *gr = getgrgid(gid);
	printf("%7s %7s", pw->pw_name, gr->gr_name);
}

void sizeInKB(struct stat f_info){
	float sizeKB;
	sizeKB=(float)f_info.st_size/1024;
	printf("%10fKB",sizeKB);
}

void lastModified(struct stat f_info){
	printf("  %15s",ctime(&f_info.st_mtime)+4);
}

void fileName(struct dirent *dtr){
	
	char temp[10]=" ";
	if(strlen(dtr->d_name)>10){
	for(int i=0;i<8;i++){
	temp[i]=dtr->d_name[i];
	}
	temp[8]='.';
	temp[9]='.';
	
	printf("%10s",temp);
	}

	else
		printf("%10s",dtr->d_name);	
	
	
}
//to create the list of drectory and file names
vector <struct dirent*> populateDir(){
	vector <struct dirent*> dtr_array;
	struct dirent *dtr;
	struct stat f_info;
	
	DIR *dir=opendir(".");
	//chdir(args[1]);
	if(dir==NULL)
		cout<<"Cannot display file"<<endl;
	else{
		while(dtr=readdir(dir)){
			dtr_array.push_back(dtr);
			stat(dtr->d_name, &f_info);
			fileName(dtr);
			permissions(dtr,f_info);
			ownership(f_info.st_uid,f_info.st_gid);
			sizeInKB(f_info);
			lastModified(f_info);
					
		
		}
		


	}
	closedir(dir);

return dtr_array;
}

void printDir(int lower,int upper,vector <struct dirent*> dtr_array){
	
	struct dirent *dtr;
	struct stat f_info;
	printf("\033[2J");
	printf("\e[1;1H");
	DIR *dir=opendir(".");
	//chdir(args[1]);
	if(dir==NULL)
		cout<<"Cannot display file"<<endl;
	else{
		for(int i=lower;i<=upper;i++){
			stat(dtr_array[i]->d_name, &f_info);
			fileName(dtr_array[i]);
			permissions(dtr_array[i],f_info);
			ownership(f_info.st_uid,f_info.st_gid);
			sizeInKB(f_info);
			lastModified(f_info);
					
		
		}
		


	}
	closedir(dir);


}





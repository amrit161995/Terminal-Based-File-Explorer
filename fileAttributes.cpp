#include<iostream>
#include<dirent.h>
#include<string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include<time.h>
#include <bits/stdc++.h>
#include<vector>
#include <pwd.h>
#include <grp.h>
using namespace std;

void permissions(struct dirent *dtr,struct stat f_info){
	stat(dtr->d_name, &f_info);
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
	
	char temp[20]=" ";
	if(strlen(dtr->d_name)>20){
	for(int i=0;i<16;i++){
	temp[i]=dtr->d_name[i];
	}
	temp[16]='.';
	temp[17]='.';
	
	printf("%20s",temp);
	}

	else
		printf("%20s",dtr->d_name);	
	
	
}


// #include<stdio.h>
// #include<sys/types.h>
// #include<dirent.h>
// #include<stdlib.h>
// #include<string.h>
#include"diff.h"


//first fetching the files in current directory comparing them and then applying diff on them.
//then calling the function recursively which in order calls list files recursively
int givemefiles(char *file1, char *file2, char *path1, char *path2, int flag_y, int flag_c, int flag_r, int flag_t1, int flag_w, int flag_b, int flag_i, int flag_u) {
	info i1;
	char pathdirs[100], pathfiles[100];
	
	i1 = listfilesrecursively(path1);
	
	info i2;
	i2 = listfilesrecursively(path2);
	int tabledirs[i1.j][i2.j];
	for(int i = 0; i < i1.j; i++) {
		for(int j = 0; j < i2.j; j++) {
			tabledirs[i][j] = 0;
		}
	}
	for(int i = 0; i < i1.j; i++) {
		for(int j = 0; j < i2.j; j++) {
			if(strcmp(i1.dirs[i], i2.dirs[j])) {
				tabledirs[i][j] = 0;
			}
			else
				tabledirs[i][j] = 1;
		}
	}
	for(int i = 0; i < i1.j; i++) {
		for(int j = 0; j < i2.j; j++) {
			if(strcmp(i1.dirs[i], i2.dirs[j])) {
				tabledirs[i][j] = 0;
			}
			else
				tabledirs[i][j] = 1;
		}
	}
	int tablefiles[i1.i][i2.i];
	for(int i = 0; i < i1.i; i++) {
		for(int j = 0; j < i2.i; j++) {
			tablefiles[i][j] = 0;
		}
	}
	for(int i = 0; i < i1.i; i++) {
		for(int j = 0; j < i2.i; j++) {
			if(strcmp(i1.files[i], i2.files[j])) {
				tablefiles[i][j] = 0;
			}
			else
				tablefiles[i][j] = 1;
		}
	}
	for(int i = 0; i < i1.i; i++) {
		for(int j = 0; j < i2.i; j++) {
			if(strcmp(i1.files[i], i2.files[j])) {
				tablefiles[i][j] = 0;
			}
			else
				tablefiles[i][j] = 1;
		}
	}
	for(int i = 0; i < i1.j; i++) {
		int count = 0;
		for(int j = 0; j < i2.j; j++) {
			if(tabledirs[i][j] == 1) {
				//printf("inside\n");
				strcpy(pathdirs, path1);
				strcat(pathdirs, "/");
				strcat(pathdirs, i1.dirs[i]);
				strcpy(pathfiles, path2);
				strcat(pathfiles, "/");
				strcat(pathfiles, i2.dirs[j]);
				printf("%s %s\n", pathdirs, pathfiles);
				givemefiles(file1, file2, pathdirs, pathfiles, flag_y, flag_c, flag_r, flag_t1, flag_w, flag_b, flag_i, flag_u);
				count = 1;
			}
		}
		if(count == 0) {
			printf("only in %s : %s\n", path1,  i1.dirs[i]);
		}

	}


	//listing directories of file2*
	for(int i = 0; i < i2.j; i++) {
		int count = 0;
		for(int j = 0; j < i1.j; j++) {
			if(tabledirs[j][i] == 1) {
				//printf("inside\n");
				count = 1;
			}
		}
		if(count == 0) {
			printf("only in %s : %s\n", path2,  i2.dirs[i]);
		}
	}



	//listing files of dir2*
	for(int i = 0; i < i1.i; i++) {
		int count = 0;
		for(int j = 0; j < i2.i; j++) {
			if(tablefiles[i][j] == 1) {
				strcpy(pathdirs, path1);
				strcat(pathdirs, "/");
				strcat(pathdirs, i1.files[i]);
				strcpy(pathfiles, path2);
				strcat(pathfiles, "/");
				strcat(pathfiles, i2.files[j]);
				printf("diff -r %s %s\n", pathdirs, pathfiles);
				int fd1, fd2;
				fd1 = open(pathdirs, O_RDONLY);
				fd2 = open(pathfiles, O_RDONLY);
				if(fd1 == -1 || fd2 == -1) {
					printf("can't open file : %s\n", pathfiles);
					exit(0);
				}
				int len1, len2;
				len1 = countlines(fd1);
				lseek(fd1, SEEK_SET, 0);
				len2 = countlines(fd2);
				lseek(fd2, SEEK_SET, 0);
				count = 1;
				diff(file1, file2, fd1, fd2, len1, len2, flag_y, flag_c, flag_r, flag_t1, flag_w, flag_b, flag_i, flag_u);
			}
		}
		if(count == 0) {
			printf("only in %s : %s\n", path1, i1.files[i]);
		}
	}


	for(int i = 0; i < i2.i; i++) {
		int count = 0;
		for(int j = 0; j < i1.i; j++) {
			if(tabledirs[j][i] == 1) {
				//printf("inside\n");
				count = 1;
			}
		}
		if(count == 0) {
			printf("only in %s : %s\n", path2,  i2.files[i]);
		}
	}



}
info listfilesrecursively(char *basepath) {
	info i1;
	int i = 0, j = 0;
	char path[100];
	struct dirent *dp;
	DIR *d;
	DIR *dir = opendir(basepath);
	if(!dir) {
		i1.dirs = NULL;
		i1.files = NULL;
	}
	//Unable to open directory stream
	i1.dirs = (char **)malloc(sizeof(char*) * 100);
	i1.files = (char **)malloc(sizeof(char*) * 100);
	for(int i = 0; i < 100; i++) {
		i1.dirs[i] = (char *)malloc((sizeof(char) * 100));
	}
	for(int i = 0; i < 100; i++) {
		i1.files[i] = (char *)malloc((sizeof(char) * 100));
	}    
	i = 0;
	j = 0;
	while((dp = readdir(dir)) != NULL) {
		if(strcmp(dp -> d_name, ".") != 0 && strcmp(dp -> d_name, "..") != 0) {
			//printf("%s\n", dp ->d_name);
			strcpy(path, basepath);
			strcat(path, "/");
			strcat(path, dp -> d_name);
			d = opendir(path);
			if(!d) {
				strcpy(i1.files[i++], dp -> d_name);
			}
			else {
				//printf("%s\n", dp -> d_name);
				strcpy(i1.dirs[j++], dp -> d_name);
			}
		}
	}
	i1.i = i;
	i1.j = j;
	return i1;
}

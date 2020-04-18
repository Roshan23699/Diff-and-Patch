#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<fcntl.h>
#include<unistd.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<errno.h>
#include<getopt.h>
#include<dirent.h>
#include <time.h>

typedef struct longest_common_subsequence {
    int lcs;
   	char **str;
}subseq;
typedef struct info {
	char **dirs;
	char **files;
	int i;
	int j;
}info;
int givemefiles(char *file1, char *file2, char *path1, char *path2, int flag_y, int flag_c, int flag_r, int flag_t1, int flag_w, int flag_b, int flag_i, int flag_u);
info listfilesrecursively(char *basepath);
int max(int a, int b);
subseq calulate(int, int, int m, int n, int flag_w, int flag_i, int flag_b);
int countlines(int);
char *readline(int fd, int flag_w, int flag_b);
void diff(char *file1, char *file2, int fd1, int fd2, int len1, int len2, int flag_y, int flag_c, int flag_r, int flat_t1, int flag_w, int flag_b, int flag_i, int flag_u);
void patch(char *s, int fd1, int fd2, int len1, int len2, int);
int mystrcmp(char *, char *, int);
char *strrev(char *s1);
int mystrcmpw(char *str1, char *str2, int flag_i);
void printfory(char *s1, int flag_t1);
void printfort(char *s2);
void getFileCreationTime(char *);


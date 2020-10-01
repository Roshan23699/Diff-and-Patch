#include "diff.h"

// function to count lines from file
int countlines(int fd) {
	int count = 0;
	char ch;
	while(read(fd, &ch, 1)) {
		if(ch == '\n')
			count++;
	}
	return count;
}

// function to read lines
char *readline(int fd, int flag_w, int flag_b) {
	char ch;
	int i = 0;
	char *s = (char *)malloc(sizeof(char)*10000);
	while(read(fd, &ch, 1)) {
		if(flag_w == 2) {
			if(ch != '\n')
					if(ch != 9 && ch != '>' && ch != '<')
						s[i++] = ch;
					else
						continue;
				else {
					s[i++] = '\0';
					break;
				}
		}
		else {
			if(ch != '\n')
				s[i++] = ch;
			else {
				s[i++] = '\0';
				break;
			}
		
		}
	}
	s[i] = '\0';
	return s;
}

// String comparison function to compare strings according to flag
int mystrcmp(char *str1, char *str2, int flag_i) {
	int len1 = strlen(str1);
	int len2 = strlen(str2);
	char word1[1000], word2[1000];
	int i = 0, k = 0, j = 0;
	while(i < len1 || j < len2) {
		k = 0;
		flag1 :
		while(i < len1 && str1[i] != ' ' && str1[i] != 9) {
			word1[k++] = str1[i];
			i++;
		}
		if(k == 0 && i < len1) {
			i++;
			goto flag1;
		}
		word1[k] = '\0';
		k = 0;
		flag2 :
		while(j < len2 && str2[j] != ' ' && str2[j] != 9) {
			word2[k++] = str2[j];
			j++;
		}
		if(k == 0 && j < len2) {
			j++;
			goto flag2;
		}
		word2[k] = '\0';
		if(flag_i) {
			if(strcasecmp(word1, word2))
				return 1;
		}
		else {
			if(strcmp(word1, word2))
				return 1;
		}
		
		k = 0;
		i++;
		j++;
	}
	return 0;
}
int mystrcmpw(char *str1, char *str2, int flag_i) {
	int len1 = strlen(str1);
	int len2 = strlen(str2);
	int i = 0, k = 0;
	char word1[1000], word2[1000];
	while(i < len1) {
		if(str1[i] != ' ' && str1[i] != 9)
			word1[k++] = str1[i];
		i++;
	}
	word1[k] = '\0';
	i = 0;
	k = 0;
	while(i < len2) {
		if(str2[i] != ' ' && str2[i] != 9)
			word2[k++] = str2[i];
		i++;
	}
	word2[k] = '\0';
	//printf("this are the words %s %s\n", word1, word2);
	if(flag_i) {
		if(strcasecmp(word1, word2))
			return 1;
		else 
			return 0;
	}
	else if(strcmp(word1, word2))
		return 1;
	else
		return 0;
	
}

// function to reverse string
char *strrev(char *s1) {
	char temp;
	int len = strlen(s1);
	for(int i = 0; i < len/2; i++){
		temp = s1[i];
		s1[i] = s1[len - i - 1];
		s1[len - i - 1] = temp;
	}
	return s1;

}
void printfory(char *s1, int flag_t1) {
	int i = 0, x = 0;
	while(x < 56) {
		if(i < strlen(s1)) {	
			if(s1[i] != 9) {
				printf("%c", s1[i]);
				x++;
			}
			else {
				if(flag_t1) {
					if(x < 48) {
						printf("        ");
						x += 8;
					}
					else {
						while(x < 56) {
							printf(" ");
							x++;
						}
					}
				}
				else {
					x += 8;
					printf("\t");
				}
			}
			i++;
		}
		else {
			printf(" ");
			x++;
		}
	}
}
void printfort(char *s1) {
	int i = 0;
	int len = strlen(s1);
	while(i < len) {
		if(s1[i] == 9) {
			printf("        ");
		}
		else {
			printf("%c", s1[i]);
		}
		i++;
	}


}

// To get the creation time of file
void getFileCreationTime(char *filePath){
	struct stat attrib;
	stat(filePath, &attrib);
	char date[10];
	strftime(date, 10, "%d-%m-%y", localtime(&(attrib.st_ctime)));
	printf("%s %s\n", filePath, date);
	date[0] = 0;
}

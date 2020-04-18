#include"diff.h"
void patch(char *s, int fd1, int fd2, int len1, int len2, int flag_b) {
	lseek(fd1, SEEK_SET, 0);
	int i = 0, j = 0, k = 0;
	char **s1, **s2;
	s1 = (char **)malloc(sizeof(char*) * max(len1, len2));
	s2 = (char **)malloc(sizeof(char*) * max(len1, len2));
	
	if(s1 == NULL) {
		printf("No memory\n");
		exit(0);
	}
	
	if(s2 == NULL) {
		printf("No memory\n");
		exit(0);
	}
	
	for(i = 1; i <= len1; i++) {
    	s1[i - 1] = readline(fd1, 0, 0);
    	
    }
  
    i = 0;
	while(i < len2) {
		s2[i] = readline(fd2, 2, 0);
		i++;
	}
	close(fd1);
	close(fd2);
	if(flag_b) {
		char s2[100];
		strcpy(s2, s);
		strcat(s2, "(backup)");
		FILE *fp1 = fopen(s2, "w");
		if(!fp1) {
			char ch;
			printf("Unable to create backup file, do you want to countinue : n(no)\n");
			scanf("%c", &ch);
			if(ch == 'n')
				exit(0);
		}
		for(i = 1; i <= len1; i++) {
    		fprintf(fp1, "%s", s1[i - 1]);
			fprintf(fp1, "%c", '\n');
    	}
		fclose(fp1);
	}
	FILE *fp = fopen(s, "w");
	int f[4], len, a = 0, d = 0, c = 0;
	i = 0;
	int count = 1;
	while(i < len2) {
		len = strlen(s2[i]);
		j = 0;
		k = 0;
		while(k < 4) {
			f[k] = 0;
			k++;
		}
		k = 0;
		j = 0;
		
		while(j < len) {			
			switch(s2[i][j]) {
				case 'a':
					a = 1;
					d = 0;
					c = 0;
					k = 2;
					break;
				
				case 'c':
					a = 0;
					d = 0;
					c = 1;
					k = 2;
					break;
					
				case 'd':
					a = 0;
					d = 1;
					c = 0;
					k = 2;
					break;
				case '0' : case '1' : case '2': case '3' : case '4': case '5' : case '6': case '7' : case '8': case '9':
					f[k] = f[k] * 10 + (s2[i][j] - '0');
					break;
				case ',':
					k++;
					break;
			}
			j++;
		}
		/*checking if the difference is generated*/
		if(d == 1) {
			while(count < f[0]) {
				fprintf(fp, "%s", s1[count - 1]);
				fprintf(fp, "%c", '\n');
				count++;
			}
			
			count++;
			i++;
			while(count <= f[1]) {
				count++;
				i++;
			}
			if(i == len2 - 1) {
				while(count <= len1) {
			
					fprintf(fp, "%s", s1[count - 1]);
					fprintf(fp, "%c", '\n');
					count++;
				}
			
			}
			
		}
		/*checking if the add is generated*/
		if(a == 1) {
			
			while(count <= f[0]) {
			
				fprintf(fp, "%s", s1[count - 1]);
				fprintf(fp, "%c", '\n');
				count++;
			}	
			j = 0;
			if(f[3] - f[2] < 0)
				f[3] = f[2];
			while(j <= f[3] - f[2]) {
				i++;
			
				fprintf(fp, "%s", s2[i] + 1);
				fprintf(fp, "%c", '\n');
				j++;
			}
			if(i == len2 - 1) {
				while(count <= len1) {
			
					fprintf(fp, "%s", s1[count - 1]);
					fprintf(fp, "%c", '\n');
					count++;
				}
			}
			
		}
			
		/*checking if the change is generated*/
		if(c == 1) {
			while(count < f[0]) {
			
				fprintf(fp, "%s", s1[count - 1]);
				fprintf(fp, "%c", '\n');
				count++;
			}	
			j = 0;
			if(f[1] - f[0] < 0)
				f[1] = f[0];
			while(j <= f[1] - f[0]) {
			
				count++;
				i++;
				j++;
			}
			i++;
			j = 0;
			if(f[3] - f[2] < 0)
				f[3] = f[2];
			while(j <= f[3] - f[2]) {
			
				i++;
			
				fprintf(fp, "%s", s2[i] + 1);
				fprintf(fp, "%c", '\n');
				j++;
			}
			if(i == len2 - 1) {
				while(count <= len1) {
			
					fprintf(fp, "%s", s1[count - 1]);
					fprintf(fp, "%c", '\n');
					count++;
				}
			}
			
		}
		i++;
	}
	printf("patching in file %s\n", s);
	fclose(fp);
}

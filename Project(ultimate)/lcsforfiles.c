#include"diff.h"

subseq calulate(int fd1, int fd2, int m, int n, int flag_w, int flag_i, int flag_b) {
	subseq l_c_s;
	char **s1, **s2;
	s1 = (char **)malloc(sizeof(char*) * max(m, n));
	s2 = (char **)malloc(sizeof(char*) * max(m, n));
	if(s1 == NULL || s2 == NULL) {
		printf("No memory\n");
			exit(0);
	}
	for(int i = 0; i < max(m, n); i++) {
		s1[i] = (char *)malloc(sizeof(char) * 1000);
		s2[i] = (char *)malloc(sizeof(char) * 1000);
		if(s1[i] == NULL || s2[i] == NULL) {
			printf("No memory\n");
			exit(0);
		}
	}
	if(s1 == NULL || s2 == NULL)
		exit(0);
	l_c_s.lcs = 0;
	int **table;
	table = (int **)malloc(sizeof(int*) * (m + 1));

	for(int i = 0; i < m + 1; i++) {
		table[i] = (int *)malloc(sizeof(int) * (n + 1));
		if(table[i] == NULL) {
			printf("No memory\n");
			exit(0);
		}
	}

    //int  table[m + 1][n + 1], 
	int i, j;
    for (i = 0; i <= m; i++) {
        table[i][0] = 0;
    }
	for (i = 0; i <= n; i++) {
        table[0][i] = 0;
    }
    lseek(fd1, SEEK_SET, 0);
    lseek(fd2, SEEK_SET, 0);
    for(i = 1; i <= m; i++) {
    	s1[i - 1] = readline(fd1, flag_w, flag_b);
    }
    for(j = 1; j <= n; j++) {
    	s2[j - 1] = readline(fd2, flag_w, flag_b);
    }
	for(i = 1; i <= m; i++) {
		if(flag_w) {
			for(j = 1; j <= n; j++) {
				if(mystrcmpw(s1[i - 1], s2[j - 1], flag_i) == 0) {
					table[i][j] = table[i - 1][j - 1] + 1;
				}
				else {
					table[i][j] = max(table[i][j - 1], table[i - 1][j]);
				}
			}
		}
		else if(flag_b) {
			for(j = 1; j <= n; j++) {
				if(mystrcmp(s1[i - 1], s2[j - 1], flag_i) == 0) {
					table[i][j] = table[i - 1][j - 1] + 1;
				}
				else {
					table[i][j] = max(table[i][j - 1], table[i - 1][j]);
				}
			}
		}
		else if(flag_i) {
			for(j = 1; j <= n; j++) {
					if(strcasecmp(s1[i - 1], s2[j - 1]) == 0) {
						table[i][j] = table[i - 1][j - 1] + 1;
					}
					else {
						table[i][j] = max(table[i][j - 1], table[i - 1][j]);
					}
			}
		}
		else {
			for(j = 1; j <= n; j++) {
				if(strcmp(s1[i - 1], s2[j - 1]) == 0) {
					table[i][j] = table[i - 1][j - 1] + 1;
				}
				else {
					table[i][j] = max(table[i][j - 1], table[i - 1][j]);
				}
			}
		}
	}
	
	l_c_s.lcs = table[m][n];
	i = m;
	j = n;
	l_c_s.str = (char **)malloc(sizeof(char *) * max (m, n));
	int k = 0;
	while(table[i][j]) {
			if(table[i][j] != max(table[i][j - 1], table[i - 1][j])) {
				l_c_s.str[k++] = s1[i - 1];
				i--;
				j--;
			}
			else {
				if(table[i][j] == table[i - 1][j]) {
					i--;
				}
				else
				{
					j--;

				}
			}
	}
	for(int i = 0; i < m + 1; i++) {
		free(table[i]);
	}
	free(table);
	return l_c_s;
}
int max(int a, int b) {
	if(a > b)
		return a;
	else 
		return b;
}

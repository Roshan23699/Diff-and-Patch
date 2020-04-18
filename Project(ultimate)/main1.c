#include"diff.h"
int main(int argc, char **argv) {
    int len1, len2, fd[5];
    char st[5][100];
    int flag_y = 0, flag_c = 0, flag_r = 0, flag_t1 = 0, flag_w = 0, flag_b = 0, flag_i = 0, i, flag_u = 0;
    int opt;
    int error = 0;
    while((opt = getopt(argc, argv, ":ycrtwbiu")) != -1) {
    	switch(opt) {
    		case 'y':
    			flag_y = 1;
    			break;
    		case 'c':
    			flag_c = 1;
    			break;
    		case 'r':
    			flag_r = 1;
    			break;
    		case 't':
    			flag_t1 = 1;
    			break;
    		case 'w':
    			flag_w = 1;
    			break;
    		case 'b':
    			flag_b = 1;
    			break;
    		case 'i':
    			flag_i = 1;
    			break;
			case 'u':
				flag_u = 1;
				break;
			default:
				error = 1;
				break;
    	}
    }
	if(error) {
		printf("Invalid options\n");
		return 0;
	}

	if(optind == argc) /*sanity check*/ {
		printf("Insufficient arguments : ");
		exit(0);
	}
	else if(flag_r) {
		int ind = 0;
		for(i = optind; i < argc; i++) {
			strcpy(st[ind++], argv[i]);
		}
		givemefiles(st[0], st[1], st[0], st[1], flag_y, flag_c, flag_r, flag_t1, flag_w, flag_b, flag_i, flag_u);
		return 0;
	}
	else {
		//loop over files
		int k = 0;
		int ind = 0;
		for(i = optind; i < argc; i++) {
			if((fd[k++] = open(argv[i], O_RDONLY)) != -1) {
				strcpy(st[ind++], argv[i]);
				continue;
			}
			else {
				printf("can't open file\n");
				exit(0);
				
			}
		
		}
	}
	
    
	len1 = countlines(fd[0]);
	lseek(fd[0], SEEK_SET, 0);
	len2 = countlines(fd[1]);
	lseek(fd[1], SEEK_SET, 0);
	diff(st[0], st[1], fd[0], fd[1], len1, len2, flag_y, flag_c, flag_r, flag_t1, flag_w, flag_b, flag_i, flag_u);
    return 0;
}
/*the original diff command resembling output will be given by the diff function by using the output of lcs function*/
void diff(char *file1, char *file2, int fd1, int fd2, int len1, int len2, int flag_y, int flag_c, int flag_r, int flag_t1, int flag_w, int flag_b, int flag_i, int flag_u) {
	int i, j;
	subseq L_C_S;
	lseek(fd1, SEEK_SET, 0);
	lseek(fd2, SEEK_SET, 0);
	L_C_S = calulate(fd1, fd2, len1, len2, flag_w, flag_i, flag_b);
	lseek(fd1, SEEK_SET, 0);
	lseek(fd2, SEEK_SET, 0);
	
	char **s1, **s2;
	s1 = (char **)malloc(sizeof(char*) * max(len1, len2));
	s2 = (char **)malloc(sizeof(char*) * max(len1, len2));
	if(s1 == NULL || s2 == NULL) {
		printf("No memory\n");
			exit(0);
	}
	
	if(s1 == NULL || s2 == NULL)
		exit(0);
	lseek(fd1, SEEK_SET, 0);
	lseek(fd2, SEEK_SET, 0);
	for(i = 1; i <= len1; i++) {
    	s1[i - 1] = readline(fd1, flag_w, flag_b);
    }
    for(i = 1; i <= len2; i++) {
    	s2[i - 1] = readline(fd2, flag_w, flag_b);
    }
	i = 0;
	j = 0;
	int f1 = 0, f2 = 0;
	int k;
	k = L_C_S.lcs - 1;
	if((flag_y && flag_c) || (flag_y && flag_u) || (flag_c && flag_u)) {
		printf("diff : conflicting output style options\n");
		exit(0);
	}
	
	int xyz = 0;
	char **s3; /*array of strings required for -c*/
	s3 = (char **)malloc(sizeof(char*) * max(len1, len2));
	if(s3 == NULL) {
		printf("No memory\n");
			exit(0);
	}
	for(i = 0; i < max(len1, len2); i++) {
		s3[i] = (char *)malloc(sizeof(char)*1000);
		if(s3[i] == NULL){
			printf("No memory\n");
			exit(0);
		}
	}
	int a = 0, c = 0, d = 0;
	i = L_C_S.lcs - 1;
	j = 0;
	k = 0;
	if(flag_c) {
		if((L_C_S.lcs != len1 || L_C_S.lcs != len2) && (len1 != 0 || len2 != 0)) {
			printf("***");
			getFileCreationTime(file1);
			printf("---");
			getFileCreationTime(file2);
			printf("***************\n");
			if(len1 == 0)
				printf("*** 0 ****\n");
				else if(len1 == 1)
					printf("--- 1 ----\n");
			else {
				printf("*** 1,%d ****\n", len1);
			}
			
		}
	}
	else if(flag_u) {
		if((L_C_S.lcs != len1 || L_C_S.lcs != len2) && (len1 != 0 || len2 != 0)) {
			printf("---");
			getFileCreationTime(file1);
			printf("+++");
			getFileCreationTime(file2);
			printf("@@ -%d,%d +%d,%d @@\n", 1, len1, 1, len2);
		}
	}
	while(i >= 0) {
		f1 = j;
		while(j < len1) {
			if(flag_w) {
				if(mystrcmpw(L_C_S.str[i], s1[j], flag_i) == 0)
					break;
			}
			else if(flag_b) {
				if(mystrcmp(L_C_S.str[i], s1[j], flag_i) == 0)
					break;
			}
			else if(flag_i) {
				if(strcasecmp(L_C_S.str[i], s1[j]) == 0)
					break;
			}
			else {
				if(strcmp(L_C_S.str[i], s1[j]) == 0)
					break;
			}
			j++;
		}
		f2 = k;
		while(k < len2) {
			if(flag_w) {
				if(mystrcmpw(L_C_S.str[i], s2[k], flag_i) == 0)
					break;
			}
			else if(flag_b) {
				if(mystrcmp(L_C_S.str[i], s2[k], flag_i) == 0)
					break;
			}
			if(flag_i) {
				if(strcasecmp(L_C_S.str[i], s2[k]) == 0)
					break;
			}
			else {
				if(strcmp(L_C_S.str[i], s2[k]) == 0)
					break;
			}
			k++;
		}
		if(j - f1 == 0 && k - f2 == 0) {
			if((L_C_S.lcs != len1 || L_C_S.lcs != len2) && (len1 != 0 || len2 != 0)) {
				if(flag_c) {
					if(flag_t1) {
						printfort(s1[j]);
						printf("\n");

					}
					else {
						printf("  %s\n", s1[j]);
					}
					strcpy(s3[xyz], "  ");
					strcat(s3[xyz], s2[k]);
					xyz++;
				}
				else if(flag_u) {
					if(flag_t1) {
						printfort(s1[j]);
						printf("\n");
					}
					else {
						printf(" %s\n", s1[j]);
					}
				}
				else if(flag_y) {
					printfory(s1[j], flag_t1);
					printf("  %s\n", s2[k]);
				}
			}
			i--;
			j++;
			k++;
			continue;
		}
		else {
			if(j - f1 == 0) {
				a = 1;
				d = 0;
				c = 0;
			}
			else if(k - f2 == 0) {
				d = 1;
				a = 0;
				c = 0;
			}
			else {
				c = 1;
				a = 0;
				d = 0;
			}
		}
		if(c == 1) {
		//checking for flag c 
			if(flag_c) {
				while(f1 < j || f2 < k) {
					if(f1 < j && f2 < k) {
						if(flag_t1) {
							printf("! ");
							printfort(s1[j]);
							printf("\n");
						}
						else {
							printf("! %s\n", s1[f1]);
						}
						strcpy(s3[xyz], "! ");
						strcat(s3[xyz], s2[f2]);
						xyz++;
						f1++;
						f2++;
					}
					/*continue from here*/
					else if(f1 < j) {
						if(flag_t1) {
							printf("! ");
							printfort(s1[f1]);
							printf("\n");
						}
						else {
							printf("! %s\n", s1[f1]);
						}
						
						f1++;
					}
					else if(f2 < k) {
						strcpy(s3[xyz], "! ");
						strcat(s3[xyz], s2[f2]);
						xyz++;
						f2++;
					}
				}
				if(flag_t1) {
					printf("  ");
					printfort(s1[j]);
					printf("\n");
				}
				else {
					printf("  %s\n", s1[j]);
				}
				strcpy(s3[xyz], "  ");
				strcat(s3[xyz], s2[f2]);
				xyz++;
			}
			//checking for flag u
			else if(flag_u) {
				while(f1 < j || f2 < k) {
					if(f1 < j && f2 < k) {
						if(flag_t1) {
							printf("-");
							printfort(s1[f1]);
							printf("\n");
							printf("+");
							printfort(s2[f2]);
							printf("\n");
						}
						else {
							printf("-%s\n", s1[f1]);
							printf("+%s\n", s2[f2]);
						}
						f1++;
						f2++;
					}
					/*continue from here*/
					else if(f1 < j) {
						if(flag_t1) {
							printf("-");
							printfort(s1[f1]);
							printf("\n");
						}
						else {
							printf("-%s\n", s1[f1]);
						}
						f1++;
					}
					else if(f2 < k) {
						if(flag_t1) {
							printf("+");
							printfort(s2[f2]);
							printf("\n");
						}
						else {
							printf("+%s\n", s2[f2]);
						}
						
						xyz++;
						f2++;
					}
				}
				if(flag_t1) {
					printfort(s1[j]);
					printf("\n");
				}
				else
					printf(" %s\n", s1[j]);
			}



			/*flag c for c is completed start from a onwards*/
			
			
			else if(flag_y) {
				while(f1 < j || f2 < k) {
					if(f1 < j && f2 < k) {
						printfory(s1[f1], flag_t1);
						printf("| %s\n", s2[f2]);
						f1++;
						f2++;
					}
					else if(f1 < j) {
						printfory(s1[f1], flag_t1);
						printf("<\n");
						f1++;
					}
					else if(f2 < k) {
						printfory("", flag_t1);
							printf("> %s\n", s2[f2]);
							f2++;
					}
				}
				printfory(s1[j], flag_t1);
				printf("  %s\n", s2[k]);
			}
			else {
				if(j - f1 == 1)
					printf("%d", f1 + 1);
				else 
					printf("%d,%d", f1 + 1, j);
				if(k - f2 == 1)
					printf("c%d\n", f2 + 1);
				else 
					printf("c%d,%d\n", f2 + 1, k);
				while(f1 < j) {
					if(flag_t1) {
						printf("< ");
						printfort(s1[f1]);
						printf("\n");
					}
					else {
						printf("< %s\n", s1[f1]);
					}
					f1++;
				}
				printf("---\n");
				while(f2 < k) {
					if(flag_t1) {
						printf("> ");
						printfort(s2[f2]);
						printf("\n");
					}
					else {
						printf("> %s\n", s2[f2]);
					}
					f2++;
				}
			}
		}
		
		else if(a == 1) {
			if(flag_c) {
				while(f2 < k) {
					strcpy(s3[xyz], "+ ");
					strcat(s3[xyz], s2[f2]);
					f2++;
					xyz++;
				}
				if(flag_t1) {
					printf("  ");
					printfort(s1[j]);
					printf("\n");
				}
				else {
					printf("  %s\n", s1[j]);
				}
				strcpy(s3[xyz], "  ");
				strcat(s3[xyz], s2[k]);
				xyz++;
			}

			//checking for flag u
			else if(flag_u) {
				while(f2 < k) {
					if(flag_t1) {
					printf("+");
					printfort(s2[f2]);
					printf("\n");
					}
					else {
						printf("+%s\n", s2[f2]);
					}
					
					f2++;
				}
				if(flag_t1) {
					printf(" ");
					printfort(s1[j]);
					printf("\n");
					}
					else {
						printf(" %s\n", s1[j]);
					}
				
			}

			else if(flag_y) {
				while(f2 < k) {
					printfory("", flag_t1);
					printf("> %s\n", s2[f2]);
					f2++;
				}
				printfory(s1[j], flag_t1);
				printf("  %s\n", s2[k]);
			}
			else {
				printf("%d", f1);
				if(k - f2 == 1)
					printf("a%d\n", f2 + 1);
				else
					printf("a%d,%d\n", f2 + 1, k);
				while(f2 < k) {
					if(flag_t1) {
						printf("> ");
						printfort(s2[f2]);
						printf("\n");
					}
					else {
						printf("> %s\n", s2[f2]);
					}
					f2++;
				}
			}
		}
		else if(d == 1) {
			/*checking for flag_c*/
			if(flag_c) {
				while(f1 < j) {
					if(flag_t1) {
					printf("- ");
					printfort(s1[f1]);
					printf("\n");
					}
					else {
						printf("- %s\n", s1[f1]);
					}
					
					f1++;
				}
					if(flag_t1) {
						printf("  ");
						printfort(s1[j]);
						printf("\n");
					}
					else {
						printf("  %s\n", s1[j]);
					}
				
				strcpy(s3[xyz], "  ");
				strcat(s3[xyz], s2[k]);
				xyz++;
			}
			//checking for flag u
			else if(flag_u) {
				while(f1 < j) {
					if(flag_t1) {
						printf("-");
						printfort(s1[f1]);
						printf("\n");
					}
					else {
						printf("-%s\n", s1[f1]);
					}
					
					f1++;
				}
					if(flag_t1) {
						printf(" ");
						printfort(s1[j]);
						printf("\n");
					}
					else {
						printf(" %s\n", s1[j]);
					}
				
			}
			
			/*checking for flag_y*/
			else if(flag_y) {
				while(f1 < j) {
					printfory(s1[f1], flag_t1);
					printf("<\n");
					f1++;
				}
				printfory(s1[j], flag_t1);
				printf("  %s\n", s2[k]);
			}
			else {
				if(j - f1 == 1)
					printf("%d", f1 + 1);
				else
					printf("%d,%d", f1 + 1, j);
				printf("d%d\n", f2);
				while(f1 < j) {
					if(flag_t1) {
						printf("< ");
						printfort(s1[f1]);
						printf("\n");
					}
					else {
						printf("< %s\n", s1[f1]);
					}
					f1++;
				}
			}
		}
		j++;
		k++;
		i--;
		a = c = d = 0;
	}
	f1 = j;
	while(j < len1) {
		j++;
	}
	f2 = k;
	while(k < len2) {
		k++;
	}
	
	if(j - f1 == 0 && k - f2 == 0) {
		if(flag_c != 1 && flag_u != 1) {
			i--;
			j++;
			k++;
			return;
		}
	}
		else {
			if(j - f1 == 0) {
				a = 1;
			}
			else if(k - f2 == 0) {
				d = 1;
			}
			else {
				c = 1;
			}
		}
		if(c == 1) {
			if(flag_c) {
				while(f1 < j || f2 < k) {
					if(f1 < j && f2 < k) {
						if(flag_t1) {
							printf("! ");
							printfort(s1[j]);
							printf("\n");
						}
						else {
							printf("! %s\n", s1[f1]);
						}
						strcpy(s3[xyz], "! ");
						strcat(s3[xyz], s2[f2]);
						xyz++;
						f1++;
						f2++;
					}
					/*continue from here*/
					else if(f1 < j) {
						if(flag_t1) {
							printf("! ");
							printfort(s1[f1]);
							printf("\n");
						}
						else {
							printf("! %s\n", s1[f1]);
						}
						f1++;
					}
					else if(f2 < k) {
						strcpy(s3[xyz], "! ");
						strcat(s3[xyz], s2[f2]);
						xyz++;
						f2++;
					}
				}
			}
			//checking for flag u
			else if(flag_u) {
				while(f1 < j || f2 < k) {
					if(f1 < j && f2 < k) {
						if(flag_t1) {
							printf("-");
							printfort(s1[f1]);
							printf("\n");
							printf("+");
							printfort(s2[f2]);
							printf("\n");
						}
						else {
							printf("-%s\n", s1[f1]);
							printf("+%s\n", s2[f2]);
						}
						f1++;
						f2++;
					}
					/*continue from here*/
					else if(f1 < j) {
						if(flag_t1) {
							printf("-");
							printfort(s1[f1]);
							printf("\n");
						}
						else {
							printf("-%s\n", s1[f1]);
						}
						f1++;
					}
					else if(f2 < k) {
						if(flag_t1) {
							printf("+");
							printfort(s2[f2]);
							printf("\n");
						}
						else {
							printf("+%s\n", s2[f2]);
						}
						f2++;
					}
				}
			}

				//checking for flag y
			else if(flag_y) {
				while(f1 < j || f2 < k) {
					if(f1 < j && f2 < k) {
						printfory(s1[f1], flag_t1);
						printf("| %s\n", s2[f2]);
						f1++;
						f2++;
					}
					else if(f1 < j) {
						printfory(s1[f1], flag_t1);
						printf("<\n");
						f1++;
					}
					else if(f2 < k) {
							printfory("", flag_t1);
							printf("> %s\n", s2[f2]);
							f2++;
					}
				}
			}
			else {
				if(j - f1 == 1)
					printf("%d", f1 + 1);
				else 
					printf("%d,%d", f1 + 1, j);
				if(k - f2 == 1)
					printf("c%d\n", f2 + 1);
				else 
					printf("c%d,%d\n", f2 + 1, k);
				while(f1 < j) {
					if(flag_t1) {
						printf("< ");
						printfort(s1[f1]);
						printf("\n");
					}
					else {
						printf("< %s\n", s1[f1]);
					}
					f1++;
				}
				printf("---\n");
				while(f2 < k) {
					if(flag_t1) {
						printf("> ");
						printfort(s2[f2]);
						printf("\n");
					}
					else {
						printf("> %s\n", s2[f2]);
					}
					f2++;
				}
			}
		}
		
		else if(a == 1) {
			if(flag_c) {
				while(f2 < k) {
					strcpy(s3[xyz], "+ ");
					strcat(s3[xyz], s2[f2]);
					f2++;
					xyz++;
				}
			}
			//checking for flag u
			if(flag_u) {
				while(f2 < k) {
					if(flag_t1) {
					printf("+");
					printfort(s2[f2]);
					printf("\n");
					}
					else {
						printf("+%s\n", s2[f2]);
					}
					f2++;
				}
			}


			else if(flag_y) {
				while(f2 < k) {
					printfory("", flag_t1);
					printf("> %s\n", s2[f2]);
					f2++;
				}
			}
			else {
				printf("%d", f1);
				if(k - f2 == 1)
					printf("a%d\n", f2 + 1);
				else 
					printf("a%d,%d\n", f2 + 1, k);
				while(f2 < k) {
					if(flag_t1) {
						printf("> ");
						printfort(s2[f2]);
						printf("\n");
					}
					else {
						printf("> %s\n", s2[f2]);
					}
					f2++;
				}
			}
		}
		else if(d == 1) {
			if(flag_c) {
				while(f1 < j) {
					if(flag_t1) {
					printf("- ");
					printfort(s1[f1]);
					printf("\n");
					}
					else {
						printf("- %s\n", s1[f1]);
					}
					f1++;
				}
			}
			//checking for flag u
			else if(flag_u) {
				while(f1 < j) {
					if(flag_t1) {
						printf("-");
						printfort(s1[f1]);
						printf("\n");
					}
					else {
						printf("-%s\n", s1[f1]);
					}
					f1++;
				}
			}


			else if(flag_y) {
				while(f1 < j) {
					printfory(s1[f1], flag_t1);
					printf("<\n");
					f1++;
				}
			}	
			else {
				if(j - f1 == 1)
					printf("%d", f1 + 1);
				else
					printf("%d,%d", f1 + 1, j);
				printf("d%d\n", f2);
				while(f1 < j) {
					if(flag_t1) {
						printf("< ");
						printfort(s1[f1]);
						printf("\n");
					}
					else {
						printf("< %s\n", s1[f1]);
					}
					f1++;
				}
			}
		}
		
		
		/*considering the -c*/
		if(flag_c) {
			//printf("%d\n", xyz);
			if((L_C_S.lcs != len1 || L_C_S.lcs != len2) && (len1 != 0 || len2 != 0)) {
				if(len2 == 0)
					printf("--- 0 ----\n");
				else if(len2 == 1)
					printf("--- 1 ----\n");
				else {
					printf("--- 1,%d ----\n", len2);
				}
			}
		}
		int ss = 0;
		while(ss < xyz) {
			if(flag_t1) {
				printfort(s3[ss]);
				printf("\n");
			}
			else {
				printf("%s\n", s3[ss]);
			}
			ss++;
		}
		free(s1);
		free(s2);	
}


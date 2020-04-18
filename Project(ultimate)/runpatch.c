/*patch takes input as the original file and the output of diff and patch it into the original file*/
#include"diff.h"
int main(int argc, char *argv[]) {
    char st[5][100];
    int  flag_b = 0, opt, i, fd[5], k = 0;
     while((opt = getopt(argc, argv, ":b")) != -1) {
    	switch(opt) {
    		case 'b':
    			flag_b = 1;//flag used to detect if the user wants the backup of the original file
    			break;
		    default:
				break;
    	}
    }
   
//sanity check
   
    for(i = optind; i < argc; i++) {
        strcpy(st[k], argv[i]);
        if((fd[k++] = open(argv[i], O_RDONLY)) != -1) {
            continue;
        }
        else {
            printf("can't open file\n");
            exit(0);
            
        }
		
	}
    int len1, len2;
   
    len1 = countlines(fd[0]);
    len2 = countlines(fd[1]);
    lseek(fd[0], 0, SEEK_SET);
    lseek(fd[1], 0, SEEK_SET);
    patch(st[0], fd[0], fd[1], len1, len2, flag_b);
    return 0;
}
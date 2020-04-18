all:
	gcc main1.c -Wall -c;
	gcc lcsforfiles.c -Wall -c;
	gcc countlines.c -Wall -c;
	gcc patch.c -c ;
	gcc -c ultimater.c;
	gcc ultimater.o lcsforfiles.o countlines.o main1.o patch.o -o diffe;
	rm *.o;
default: longest_common_subseq.o
	for number in "Roshan" "Haresh" "Mahesh" "Rushikesh" "Darshana" "Archana" ;do \
		echo $$number; \
	done
	
longest_common_subseq.o: longest_common_subseq.c
	gcc longest_common_subseq.c;

lcsforfiles.o: lcsforfiles.c
	gcc lcsforfiles.c;

patch:
	gcc -c patch.c -Wall;
	gcc -c runpatch.c -Wall;
	gcc -c countlines.c -Wall;
	gcc -c lcsforfiles.c -Wall;
	gcc patch.o runpatch.o countlines.o lcsforfiles.o -o patchit;
	rm *.o;
	

#include "advent.h"

#define execute(s) 	printf("Solving %d...\n", s); 	\
					fflush(stdout); 				\
					strcpy(path,folder);            \
					strcat(path, "/" #s ".txt");    \
					get##s##a(path); 	            \
					get##s##b(path);	            \
					getTime(s);


struct timespec begin, beginAll, end;
char folder[10], path[20];
bool sample = false, skip = false;

void getTime(int i) {
	clock_gettime(CLOCK_MONOTONIC, &end);
	double time = (end.tv_nsec-begin.tv_nsec)/1000000000.0+(end.tv_sec-begin.tv_sec);
	printf("Runtime %d: %f\n_______________________________\n\n", i, time);
	clock_gettime(CLOCK_MONOTONIC, &begin);
}					

int main(int argc, char* argv[]) {
	for (int i = 1; i < argc; i++) {
		if (strcmp(argv[i],"sample") == 0) sample = true;
		if (strcmp(argv[i],"skip") == 0) skip = true;
	}

	strcpy(folder,"input");
	if (sample)
		strcpy(folder,"samples");
		
	
	printf("\n\n#################\n### Solutions ###\n#################\n\n");

	clock_gettime(CLOCK_MONOTONIC, &beginAll);
	clock_gettime(CLOCK_MONOTONIC, &begin);
	
	// execute(0) // EXAMPLE
	execute(1)
	execute(2)
	execute(3)
	execute(4)
	execute(5)
	execute(6)
	execute(7)
	execute(8)
	execute(9)
	execute(10)
	execute(11)
	execute(12)
	execute(13)
	execute(14)
	/*execute(15)
	execute(16)
	execute(17)
	execute(18)
	execute(19)
	execute(20)
	execute(21)
	execute(22)
	execute(23)
	execute(24)
	execute(25)
	*/
	double time = (end.tv_nsec-beginAll.tv_nsec)/1000000000.0+(end.tv_sec-beginAll.tv_sec);
	printf("Overall Runtime: %f\n_______________________________\n", time);
	#if defined(_WIN32) || defined(_WIN64)
	if (!skip)
		system("Pause");
	#endif

	return 0;
}

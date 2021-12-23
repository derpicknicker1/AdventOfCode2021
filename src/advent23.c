/*

*/
#include "advent.h"

static int *arr;
static int cnt;

/*##########################
# Get input data from file #
##########################*/
static bool getInput(char *f) {
	char line[1000];
	arr = NULL;
	cnt = 0;

	FILE *file = fopen(f, "r");
	if (file == NULL) {
		printf("ERR: CAN NOT OPEN '%s'\n\n", f);
		return false;
	}

	while (fscanf(file, "%[^\n] ", line) != EOF) {
	
	}

	fclose(file);
	return true;
}

/*##########################
# Function to solve part A #
##########################*/
void get23a(char * f) {
	if (!getInput(f)) return;
	
	int result = 0;
	
	printf("23a: %d\n", result);
	free(arr);
}

/*##########################
# Function to solve part B #
##########################*/
void get23b(char *f) {
	if (!getInput(f)) return;

	int result = 0;

	printf("23b: %d\n\n", result);
	free(arr);
}

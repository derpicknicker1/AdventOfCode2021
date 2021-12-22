/*

*/
#include "advent.h"

#define HEX(x) (x >= 'A') ? (x - 'A' + 10) : x - '0';
enum {
	VERSION,
	TYPE,
	LITERAL,
	OP,
	END
};

typedef struct package package;
struct package {
	uint8_t v;
	uint8_t t;
	bool pCnt;
	uint16_t l;
	uint64_t val;
	package *c;
};

package start;
package *curr = &start;
int state = VERSION;
/*##########################
# Get input data from file #
##########################*/
static bool getInput(char *f) {
	char c;
	char rest = 0;
	unsigned char tmp;
	FILE *file = fopen(f, "r");
	if (file == NULL) {
		printf("ERR: CAN NOT OPEN '%s'\n\n", f);
		return false;
	}

	while ((c = fgetc(file)) != EOF) {
		c = HEX(c);
		if(rest)
			c = (tmp << 4) + c;

		if (state == VERSION) {
			
			curr->v = c >> (rest+1);
			tmp = c;
			rest += 4 - 3;
			state = TYPE;
		}
		else if (state == TYPE) {
			tmp = (tmp << rest) + c;
			curr->v = (tmp & 0xE0)>>rest+1;
			curr->t = (tmp & 0x1C)>>2;
			//printf("%d %d\n",curr->v,curr->t);
			if(curr->t = 4)
				state = LITERAL;
			else
				state = OP;
		}
	}

	fclose(file);
	return true;
}

/*##########################
# Function to solve part A #
##########################*/
void get16a(char * f) {
	if (!getInput(f)) return;
	
	int result = 0;
	
	printf("16a: %d\n", result);
}

/*##########################
# Function to solve part B #
##########################*/
void get16b(char *f) {
	if (!getInput(f)) return;

	int result = 0;

	printf("16b: %d\n\n", result);
}

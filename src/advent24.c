/*
--- Day 24: Arithmetic Logic Unit ---
Magic smoke starts leaking from the submarine's arithmetic logic unit (ALU). Without the ability to perform basic arithmetic and logic functions, the submarine can't produce cool patterns with its Christmas lights!

It also can't navigate. Or run the oxygen system.

Don't worry, though - you probably have enough oxygen left to give you enough time to build a new ALU.

The ALU is a four-dimensional processing unit: it has integer variables w, x, y, and z. These variables all start with the value 0. The ALU also supports six instructions:

inp a - Read an input value and write it to variable a.
add a b - Add the value of a to the value of b, then store the result in variable a.
mul a b - Multiply the value of a by the value of b, then store the result in variable a.
div a b - Divide the value of a by the value of b, truncate the result to an integer, then store the result in variable a. (Here, "truncate" means to round the value toward zero.)
mod a b - Divide the value of a by the value of b, then store the remainder in variable a. (This is also called the modulo operation.)
eql a b - If the value of a and b are equal, then store the value 1 in variable a. Otherwise, store the value 0 in variable a.
In all of these instructions, a and b are placeholders; a will always be the variable where the result of the operation is stored (one of w, x, y, or z), while b can be either a variable or a number. Numbers can be positive or negative, but will always be integers.

The ALU has no jump instructions; in an ALU program, every instruction is run exactly once in order from top to bottom. The program halts after the last instruction has finished executing.

(Program authors should be especially cautious; attempting to execute div with b=0 or attempting to execute mod with a<0 or b<=0 will cause the program to crash and might even damage the ALU. These operations are never intended in any serious ALU program.)

For example, here is an ALU program which takes an input number, negates it, and stores it in x:

inp x
mul x -1
Here is an ALU program which takes two input numbers, then sets z to 1 if the second input number is three times larger than the first input number, or sets z to 0 otherwise:

inp z
inp x
mul z 3
eql z x
Here is an ALU program which takes a non-negative integer as input, converts it into binary, and stores the lowest (1's) bit in z, the second-lowest (2's) bit in y, the third-lowest (4's) bit in x, and the fourth-lowest (8's) bit in w:

inp w
add z w
mod z 2
div w 2
add y w
mod y 2
div w 2
add x w
mod x 2
div w 2
mod w 2
Once you have built a replacement ALU, you can install it in the submarine, which will immediately resume what it was doing when the ALU failed: validating the submarine's model number. To do this, the ALU will run the MOdel Number Automatic Detector program (MONAD, your puzzle input).

Submarine model numbers are always fourteen-digit numbers consisting only of digits 1 through 9. The digit 0 cannot appear in a model number.

When MONAD checks a hypothetical fourteen-digit model number, it uses fourteen separate inp instructions, each expecting a single digit of the model number in order of most to least significant. (So, to check the model number 13579246899999, you would give 1 to the first inp instruction, 3 to the second inp instruction, 5 to the third inp instruction, and so on.) This means that when operating MONAD, each input instruction should only ever be given an integer value of at least 1 and at most 9.

Then, after MONAD has finished running all of its instructions, it will indicate that the model number was valid by leaving a 0 in variable z. However, if the model number was invalid, it will leave some other non-zero value in z.

MONAD imposes additional, mysterious restrictions on model numbers, and legend says the last copy of the MONAD documentation was eaten by a tanuki. You'll need to figure out what MONAD does some other way.

To enable as many submarine features as possible, find the largest valid fourteen-digit model number that contains no 0 digits. What is the largest model number accepted by MONAD?

Your puzzle answer was 29989297949519.

--- Part Two ---
As the submarine starts booting up things like the Retro Encabulator, you realize that maybe you don't need all these submarine features after all.

What is the smallest model number accepted by MONAD?

Your puzzle answer was 19518121316118.
*/
#include "advent.h"

static int divZ[14], addX[14], addY[14];
static uint64_t maxZ[14], result;
static char model[15];

/*##########################
# Get input data from file #
##########################*/
static bool getInput(char *f) {
	char a[10],line[10];
	int b, cnt = -1;

	FILE *file = fopen(f, "r");
	if (file == NULL) {
		printf("ERR: CAN NOT OPEN '%s'\n\n", f);
		return false;
	}

	while (fscanf(file, "%[^\n] ", line) != EOF) {
		sscanf(line, "%5c %d",a,&b);
		if 		(strcmp("add x", a) == 0)
			addX[cnt] = b;
		else if (strcmp("div z", a) == 0)
			divZ[cnt] = maxZ[cnt] = b;
		else if (strcmp("add y", a) == 0)
			addY[cnt] = b;
		else if (strcmp("inp w", a) == 0)
			cnt++;
	}

	for(int i = 12; i >= 0; i--) 
		maxZ[i] *= maxZ[i+1];

	fclose(file);
	return true;
}

static uint64_t getZ(int n, int w, uint64_t z) {
  if (z % 26 + addX[n] == w)
    return z / divZ[n];
  else
    return 26 * (z / divZ[n]) + w + addY[n];
}

static void calc(int pos, uint64_t z, char model[15], bool up) {
    if (pos == 14 || z >= maxZ[pos] || result) {
        if (z == 0) 
            result = atoll(model);
        return;
    }
    for (int i = 1; i <= 9 && !result; i++) {
        model[pos] = '0' + (up ? i : 10-i);
        calc(pos + 1, getZ(pos, (up ? i : 10-i), z), model, up);
    }
}

/*##########################
# Function to solve part A #
##########################*/
void get24a(char * f) {
	if (!getInput(f)) return;
	result = 0;
    calc(0, 0, model, false);
	printf("24a: %lld\n", result);
}

/*##########################
# Function to solve part B #
##########################*/
void get24b(char *f) {
	result = 0;
    calc(0, 0, model, true);
	printf("24b: %lld\n\n", result);
}


/*
####################
## My Interpreter ##
####################

static int cnt;
static int inst[500] = {};
static int a[500] = {};
static int b[500][2] = {{}};

static bool getInput(char *f) {
	char line[50];
	cnt = 0;

	FILE *file = fopen(f, "r");
	if (file == NULL) {
		printf("ERR: CAN NOT OPEN '%s'\n\n", f);
		return false;
	}

	while (fscanf(file, "%[^\n] ", line) != EOF) {
		switch ( line[1] ) {
			case 'n': inst[cnt] = 0; break;
			case 'd': inst[cnt] = 1;break;
			case 'u': inst[cnt] = 2;break;
			case 'i': inst[cnt] = 3;break;
			case 'o': inst[cnt] = 4;break;
			case 'q': inst[cnt] = 5;break;
		}
		char aa[5] = {}, bb[5] = {};
		sscanf(line + 4, "%s %s", aa, bb);
		a[cnt] = aa[0]-'w';

		if(bb[0]>='w' && bb[0]<='z') {
			b[cnt][0] = true;
			b[cnt][1] = bb[0]-'w';
		}
		else
			b[cnt][1] = atoi(bb);
		cnt++;
	}

	fclose(file);
	return true;
}


// anywhere...
if (!getInput(f)) return;
int input[14] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14};
int pos = 0;

for(int pc = 0; pc < cnt; pc++ ) {;
	int *valA = &reg[a[pc]];
	int valB = b[pc][0] ? reg[b[pc][1]] : b[pc][1];
	switch (inst[pc]) {
		case 0: *valA = input[pos++]; break;
		case 1: *valA += valB; break;
		case 2: *valA *= valB; break;
		case 3: *valA /= valB; break;
		case 4: *valA %= valB; break;
		case 5: *valA = *valA == valB; break;
	}
}

*/
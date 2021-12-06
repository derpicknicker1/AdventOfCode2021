/*
--- Day 5: Hydrothermal Venture ---
You come across a field of hydrothermal vents on the ocean floor! These vents constantly produce large, opaque clouds, so it would be best to avoid them if possible.

They tend to form in lines; the submarine helpfully produces a list of nearby lines of vents (your puzzle input) for you to review. For example:

0,9 -> 5,9
8,0 -> 0,8
9,4 -> 3,4
2,2 -> 2,1
7,0 -> 7,4
6,4 -> 2,0
0,9 -> 2,9
3,4 -> 1,4
0,0 -> 8,8
5,5 -> 8,2
Each line of vents is given as a line segment in the format x1,y1 -> x2,y2 where x1,y1 are the coordinates of one end the line segment and x2,y2 are the coordinates of the other end. These line segments include the points at both ends. In other words:

An entry like 1,1 -> 1,3 covers points 1,1, 1,2, and 1,3.
An entry like 9,7 -> 7,7 covers points 9,7, 8,7, and 7,7.
For now, only consider horizontal and vertical lines: lines where either x1 = x2 or y1 = y2.

So, the horizontal and vertical lines from the above list would produce the following diagram:

.......1..
..1....1..
..1....1..
.......1..
.112111211
..........
..........
..........
..........
222111....
In this diagram, the top left corner is 0,0 and the bottom right corner is 9,9. Each position is shown as the number of lines which cover that point or . if no line covers that point. The top-left pair of 1s, for example, comes from 2,2 -> 2,1; the very bottom row is formed by the overlapping lines 0,9 -> 5,9 and 0,9 -> 2,9.

To avoid the most dangerous areas, you need to determine the number of points where at least two lines overlap. In the above example, this is anywhere in the diagram with a 2 or larger - a total of 5 points.

Consider only horizontal and vertical lines. At how many points do at least two lines overlap?

Your puzzle answer was 5698.

--- Part Two ---
Unfortunately, considering only horizontal and vertical lines doesn't give you the full picture; you need to also consider diagonal lines.

Because of the limits of the hydrothermal vent mapping system, the lines in your list will only ever be horizontal, vertical, or a diagonal line at exactly 45 degrees. In other words:

An entry like 1,1 -> 3,3 covers points 1,1, 2,2, and 3,3.
An entry like 9,7 -> 7,9 covers points 9,7, 8,8, and 7,9.
Considering all lines from the above example would now produce the following diagram:

1.1....11.
.111...2..
..2.1.111.
...1.2.2..
.112313211
...1.2....
..1...1...
.1.....1..
1.......1.
222111....
You still need to determine the number of points where at least two lines overlap. In the above example, this is still anywhere in the diagram with a 2 or larger - now a total of 12 points.

Consider all of the lines. At how many points do at least two lines overlap?

Your puzzle answer was 15463.
*/
#include "advent.h"

static int *arr;
static int cnt, max;

/*##########################
# Get input data from file #
##########################*/
static bool getInput(char *f) {
	arr = NULL;
	cnt = 0;
	max = 0;

	FILE *file = fopen(f, "r");
	if (file == NULL) {
		printf("ERR: CAN NOT OPEN '%s'\n\n", f);
		return false;
	}

	int pos[4];
	while (fscanf(file, "%d,%d -> %d,%d\n", &pos[0], &pos[1], &pos[2], &pos[3]) != EOF) {
		arr = realloc(arr, ++cnt * 4 * sizeof(int));
		for (int i = 0; i < 4; i++)
			arr[(cnt-1) * 4 + i] = pos[i];
		if (MAX4(pos[0], pos[1], pos[2], pos[3]) >= max)
			max = MAX4(pos[0], pos[1], pos[2], pos[3]) + 1;
	}

	fclose(file);
	return true;
}

static int solve(bool ab) {
	int result = 0;
	char res[max][max];
	memset(res, 0, max*max);
	for (int i = 0; i < cnt; i++) {
		int x1 = arr[i*4], y1 = arr[i*4+1], x2 = arr[i*4+2], y2 = arr[i*4+3];
		if (x1 == x2 || y1 == y2)
			for (int y = MIN(y1,y2); y <= MAX(y1,y2); y++)
				for (int x = MIN(x1,x2); x <= MAX(x1,x2); x++)
					res[y][x]++;
		else if(ab)
			for (int j = 0; j <= abs(x1-x2); j++) {
				int x = x1 < x2 ? x1+j : x1-j;
				int y = y1 < y2 ? y1+j : y1-j;
				res[y][x]++;
			}
	}
	for (int y = 0; y < max; y++)
		for (int x = 0; x < max; x++)
			if (res[y][x] > 1) result++;

	return result;
}

/*##########################
# Function to solve part A #
##########################*/
void get5a(char * f) {
	if (!getInput(f)) return;
	printf("5a: %d\n", solve(false));
	free(arr);
}

/*##########################
# Function to solve part B #
##########################*/
void get5b(char *f) {
	if (!getInput(f)) return;
	printf("5b: %d\n\n", solve(true));
	free(arr);
}

/*
--- Day 9: Smoke Basin ---
These caves seem to be lava tubes. Parts are even still volcanically active; small hydrothermal vents release smoke into the caves that slowly settles like rain.

If you can model how the smoke flows through the caves, you might be able to avoid it and be that much safer. The submarine generates a heightmap of the floor of the nearby caves for you (your puzzle input).

Smoke flows to the lowest point of the area it's in. For example, consider the following heightmap:

2199943210
3987894921
9856789892
8767896789
9899965678
Each number corresponds to the height of a particular location, where 9 is the highest and 0 is the lowest a location can be.

Your first goal is to find the low points - the locations that are lower than any of its adjacent locations. Most locations have four adjacent locations (up, down, left, and right); locations on the edge or corner of the map have three or two adjacent locations, respectively. (Diagonal locations do not count as adjacent.)

In the above example, there are four low points, all highlighted: two are in the first row (a 1 and a 0), one is in the third row (a 5), and one is in the bottom row (also a 5). All other locations on the heightmap have some lower adjacent location, and so are not low points.

The risk level of a low point is 1 plus its height. In the above example, the risk levels of the low points are 2, 1, 6, and 6. The sum of the risk levels of all low points in the heightmap is therefore 15.

Find all of the low points on your heightmap. What is the sum of the risk levels of all low points on your heightmap?

Your puzzle answer was 498.

--- Part Two ---
Next, you need to find the largest basins so you know what areas are most important to avoid.

A basin is all locations that eventually flow downward to a single low point. Therefore, every low point has a basin, although some basins are very small. Locations of height 9 do not count as being in any basin, and all other locations will always be part of exactly one basin.

The size of a basin is the number of locations within the basin, including the low point. The example above has four basins.

The top-left basin, size 3:

2199943210
3987894921
9856789892
8767896789
9899965678
The top-right basin, size 9:

2199943210
3987894921
9856789892
8767896789
9899965678
The middle basin, size 14:

2199943210
3987894921
9856789892
8767896789
9899965678
The bottom-right basin, size 9:

2199943210
3987894921
9856789892
8767896789
9899965678
Find the three largest basins and multiply their sizes together. In the above example, this is 9 * 14 * 9 = 1134.

What do you get if you multiply together the sizes of the three largest basins?

Your puzzle answer was 1071000.
*/
#include "advent.h"

static char *arr;
static int width, height, resultA, resultB;

/*##########################
# Get input data from file #
##########################*/
static bool getInput(char *f) {
	char in;
	arr = NULL;
	width = 0;
	height = 0;

	FILE *file = fopen(f, "r");
	if (file == NULL) {
		printf("ERR: CAN NOT OPEN '%s'\n\n", f);
		return false;
	}

	while (fscanf(file, "%c", &in) != EOF) {
		if(in == '\n')
			++height;
		else {
			arr = realloc(arr, ++width * sizeof(char));
			arr[width-1] = in;
		}
	}
	width /= ++height;

	fclose(file);
	return true;
}

static bool check(int y, int x, unsigned int cy, unsigned int cx) {
	if (cy < height && cx < width)
		return arr[y*width+x] < arr[cy*width+cx];
	return true;
}

static int follow(unsigned int y, unsigned int x) {
	if (  y >= height || x >= width || arr[y*width+x] == '9')
		return 0;
	arr[y*width+x] = '9';
	int ret = follow(y+1,x);
	ret += follow(y-1,x);
	ret += follow(y,x+1);
	ret += follow(y,x-1);
	return ret + 1;
}

int cmpfunc (const void * a, const void * b) {
   return ( *(int*)b - *(int*)a );
}

static void solve() {
	int cntBas = 0, *bas = NULL;
	for (int y = 0; y < height; y++)
		for (int x = 0; x < width; x++)
			if (check(y,x,y-1,x) && check(y,x,y+1,x) && check(y,x,y,x-1) && check(y,x,y,x+1)) {
				resultA += arr[y*width+x] - 47;	
				bas = realloc(bas, ++cntBas*sizeof(int));
				bas[cntBas-1] = follow(y,x);
			}
	qsort(bas, cntBas, sizeof(int), cmpfunc);
    resultB = bas[0] * bas[1] * bas[2]; 
    free(bas);
}

/*##########################
# Function to solve part A #
##########################*/
void get9a(char * f) {
	if (!getInput(f)) return;
	solve();
	printf("9a: %d\n", resultA);
	free(arr);
}

/*##########################
# Function to solve part B #
##########################*/
void get9b(char *f) {
	printf("9b: %d\n\n", resultB);
}

/*
--- Day 20: Trench Map ---
With the scanners fully deployed, you turn their attention to mapping the floor of the ocean trench.

When you get back the image from the scanners, it seems to just be random noise. Perhaps you can combine an image enhancement algorithm and the input image (your puzzle input) to clean it up a little.

For example:

..#.#..#####.#.#.#.###.##.....###.##.#..###.####..#####..#....#..#..##..##
#..######.###...####..#..#####..##..#.#####...##.#.#..#.##..#.#......#.###
.######.###.####...#.##.##..#..#..#####.....#.#....###..#.##......#.....#.
.#..#..##..#...##.######.####.####.#.#...#.......#..#.#.#...####.##.#.....
.#..#...##.#.##..#...##.#.##..###.#......#.#.......#.#.#.####.###.##...#..
...####.#..#..#.##.#....##..#.####....##...##..#...#......#.#.......#.....
..##..####..#...#.#.#...##..#.#..###..#####........#..####......#..#

#..#.
#....
##..#
..#..
..###
The first section is the image enhancement algorithm. It is normally given on a single line, but it has been wrapped to multiple lines in this example for legibility. The second section is the input image, a two-dimensional grid of light pixels (#) and dark pixels (.).

The image enhancement algorithm describes how to enhance an image by simultaneously converting all pixels in the input image into an output image. Each pixel of the output image is determined by looking at a 3x3 square of pixels centered on the corresponding input image pixel. So, to determine the value of the pixel at (5,10) in the output image, nine pixels from the input image need to be considered: (4,9), (4,10), (4,11), (5,9), (5,10), (5,11), (6,9), (6,10), and (6,11). These nine input pixels are combined into a single binary number that is used as an index in the image enhancement algorithm string.

For example, to determine the output pixel that corresponds to the very middle pixel of the input image, the nine pixels marked by [...] would need to be considered:

# . . # .
#[. . .].
#[# . .]#
.[. # .].
. . # # #
Starting from the top-left and reading across each row, these pixels are ..., then #.., then .#.; combining these forms ...#...#.. By turning dark pixels (.) into 0 and light pixels (#) into 1, the binary number 000100010 can be formed, which is 34 in decimal.

The image enhancement algorithm string is exactly 512 characters long, enough to match every possible 9-bit binary number. The first few characters of the string (numbered starting from zero) are as follows:

0         10        20        30  34    40        50        60        70
|         |         |         |   |     |         |         |         |
..#.#..#####.#.#.#.###.##.....###.##.#..###.####..#####..#....#..#..##..##
In the middle of this first group of characters, the character at index 34 can be found: #. So, the output pixel in the center of the output image should be #, a light pixel.

This process can then be repeated to calculate every pixel of the output image.

Through advances in imaging technology, the images being operated on here are infinite in size. Every pixel of the infinite output image needs to be calculated exactly based on the relevant pixels of the input image. The small input image you have is only a small region of the actual infinite input image; the rest of the input image consists of dark pixels (.). For the purposes of the example, to save on space, only a portion of the infinite-sized input and output images will be shown.

The starting input image, therefore, looks something like this, with more dark pixels (.) extending forever in every direction not shown here:

...............
...............
...............
...............
...............
.....#..#......
.....#.........
.....##..#.....
.......#.......
.......###.....
...............
...............
...............
...............
...............
By applying the image enhancement algorithm to every pixel simultaneously, the following output image can be obtained:

...............
...............
...............
...............
.....##.##.....
....#..#.#.....
....##.#..#....
....####..#....
.....#..##.....
......##..#....
.......#.#.....
...............
...............
...............
...............
Through further advances in imaging technology, the above output image can also be used as an input image! This allows it to be enhanced a second time:

...............
...............
...............
..........#....
....#..#.#.....
...#.#...###...
...#...##.#....
...#.....#.#...
....#.#####....
.....#.#####...
......##.##....
.......###.....
...............
...............
...............
Truly incredible - now the small details are really starting to come through. After enhancing the original input image twice, 35 pixels are lit.

Start with the original input image and apply the image enhancement algorithm twice, being careful to account for the infinite size of the images. How many pixels are lit in the resulting image?

Your puzzle answer was 5057.

--- Part Two ---
You still can't quite make out the details in the image. Maybe you just didn't enhance it enough.

If you enhance the starting input image in the above example a total of 50 times, 3351 pixels are lit in the final output image.

Start again with the original input image and apply the image enhancement algorithm 50 times. How many pixels are lit in the resulting image?

Your puzzle answer was 18502.
*/
#include "advent.h"

#define items 100
#define rounds 50
#define mSize (items + 2 * (rounds+1))
#define offset (rounds+1)

static bool map[mSize][mSize] = {}, algo[512] = {};
static int resultA, resultB;

/*##########################
# Get input data from file #
##########################*/
static bool getInput(char *f) {
	char line[1000];
	int h = offset;

	FILE *file = fopen(f, "r");
	if (file == NULL) {
		printf("ERR: CAN NOT OPEN '%s'\n\n", f);
		return false;
	}
	fscanf(file, "%[^\n] ", line);
	for(int i = 0; i < 512; i++)
		algo[i] = line[i] == '.' ? false : true;

	while (fscanf(file, "%[^\n] ", line) != EOF) {
		for(int i = 0; i < items; i++)
			map[h][i+offset] = line[i] == '.' ? false : true;
		h++;
	}

	fclose(file);
	return true;
}

static bool getVal(int y, int x) {
	int val = 0;
	for (int i = y-1; i<= y+1; i++)
		for (int j = x-1; j <= x+1; j++)
			val = (val << 1)+ map[i][j];
	return algo[val];
}

static void solve() {
	static bool newMap[mSize][mSize] = {};
	int result;
	for (int i = 0; i < rounds; i++) {
		result = 0;
		for (int y = 1; y < mSize-1; y++)
			for (int x = 1; x < mSize-1; x++) {
				newMap[y][x] = getVal(y,x);
				result += newMap[y][x];
			}
		for (int j = 0; j < mSize; j++) {
			newMap[0][j] = getVal(1,1);
			newMap[mSize-1][j] = getVal(1,1);
			newMap[j][0] = getVal(1,1);
			newMap[j][mSize-1] = getVal(1,1);
		}
		memcpy(map, newMap, mSize*mSize*sizeof(bool));
		if (i == 1) resultA = result;
	}
	resultB = result;
}

/*##########################
# Function to solve part A #
##########################*/
void get20a(char * f) {
	if (!getInput(f)) return;
	solve();
	printf("20a: %d\n", resultA);
}

/*##########################
# Function to solve part B #
##########################*/
void get20b(char *f) {
	printf("20b: %d\n\n", resultB);
}


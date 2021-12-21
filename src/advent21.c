/*
--- Day 21: Dirac Dice ---
There's not much to do as you slowly descend to the bottom of the ocean. The submarine computer challenges you to a nice game of Dirac Dice.

This game consists of a single die, two pawns, and a game board with a circular track containing ten spaces marked 1 through 10 clockwise. Each player's starting space is chosen randomly (your puzzle input). Player 1 goes first.

Players take turns moving. On each player's turn, the player rolls the die three times and adds up the results. Then, the player moves their pawn that many times forward around the track (that is, moving clockwise on spaces in order of increasing value, wrapping back around to 1 after 10). So, if a player is on space 7 and they roll 2, 2, and 1, they would move forward 5 times, to spaces 8, 9, 10, 1, and finally stopping on 2.

After each player moves, they increase their score by the value of the space their pawn stopped on. Players' scores start at 0. So, if the first player starts on space 7 and rolls a total of 5, they would stop on space 2 and add 2 to their score (for a total score of 2). The game immediately ends as a win for any player whose score reaches at least 1000.

Since the first game is a practice game, the submarine opens a compartment labeled deterministic dice and a 100-sided die falls out. This die always rolls 1 first, then 2, then 3, and so on up to 100, after which it starts over at 1 again. Play using this die.

For example, given these starting positions:

Player 1 starting position: 4
Player 2 starting position: 8
This is how the game would go:

Player 1 rolls 1+2+3 and moves to space 10 for a total score of 10.
Player 2 rolls 4+5+6 and moves to space 3 for a total score of 3.
Player 1 rolls 7+8+9 and moves to space 4 for a total score of 14.
Player 2 rolls 10+11+12 and moves to space 6 for a total score of 9.
Player 1 rolls 13+14+15 and moves to space 6 for a total score of 20.
Player 2 rolls 16+17+18 and moves to space 7 for a total score of 16.
Player 1 rolls 19+20+21 and moves to space 6 for a total score of 26.
Player 2 rolls 22+23+24 and moves to space 6 for a total score of 22.
...after many turns...

Player 2 rolls 82+83+84 and moves to space 6 for a total score of 742.
Player 1 rolls 85+86+87 and moves to space 4 for a total score of 990.
Player 2 rolls 88+89+90 and moves to space 3 for a total score of 745.
Player 1 rolls 91+92+93 and moves to space 10 for a final score, 1000.
Since player 1 has at least 1000 points, player 1 wins and the game ends. At this point, the losing player had 745 points and the die had been rolled a total of 993 times; 745 * 993 = 739785.

Play a practice game using the deterministic 100-sided die. The moment either player wins, what do you get if you multiply the score of the losing player by the number of times the die was rolled during the game?

Your puzzle answer was 921585.

--- Part Two ---
Now that you're warmed up, it's time to play the real game.

A second compartment opens, this time labeled Dirac dice. Out of it falls a single three-sided die.

As you experiment with the die, you feel a little strange. An informational brochure in the compartment explains that this is a quantum die: when you roll it, the universe splits into multiple copies, one copy for each possible outcome of the die. In this case, rolling the die always splits the universe into three copies: one where the outcome of the roll was 1, one where it was 2, and one where it was 3.

The game is played the same as before, although to prevent things from getting too far out of hand, the game now ends when either player's score reaches at least 21.

Using the same starting positions as in the example above, player 1 wins in 444356092776315 universes, while player 2 merely wins in 341960390180808 universes.

Using your given starting positions, determine every possible outcome. Find the player that wins in more universes; in how many universes does that player win?

Your puzzle answer was 911090395997650.
*/
#include "advent.h"

static int player[2][2] = {{}};
static char prob[7] = {1, 3, 6, 7, 6, 3, 1};
static uint64_t nwins[2][11] = {{}};
static uint64_t win[2][11] = {{}};

/*##########################
# Get input data from file #
##########################*/
static bool getInput(char *f) {
	int pos;
	int cnt = 1;

	FILE *file = fopen(f, "r");
	if (file == NULL) {
		printf("ERR: CAN NOT OPEN '%s'\n\n", f);
		return false;
	}

	while (fscanf(file, "Player %*c starting position: %d\n", &pos) != EOF)
		player[cnt--][0] = pos;

	fclose(file);
	return true;
}

static void countRecursive(char pos, char turn, uint64_t nwin, char pts, bool player) {
	for (char i = pos; i < pos+7; i++) {
		char npos = (i + 3) % 10 ? (i + 3) % 10 : 10;
		if (pts + npos >= 21)
			win[player][turn] += nwin * prob[i-pos];
		else {
			nwins[player][turn] += nwin * prob[i-pos];
			countRecursive(npos, turn+1, nwin * prob[i-pos], pts + npos, player);
		}
	}
}

/*##########################
# Function to solve part A #
##########################*/
void get21a(char * f) {
	if (!getInput(f)) return;
	
	int roll = 0;;
	while (player[0][1] < 1000 && player[1][1] < 1000) {
		roll += 3;
		player[roll%2][0] = (player[roll%2][0] + ((3 * (roll-3)) % 100) + 6) % 10;
		player[roll%2][1] += player[roll%2][0] ? player[roll%2][0] : 10;
	}
	printf("21a: %d\n", MIN(player[1][1],player[0][1]) * roll);
}

/*##########################
# Function to solve part B #
##########################*/
void get21b(char *f) {
	if (!getInput(f)) return;

	uint64_t win1 = 0, win2 = 0;
	nwins[0][0] = nwins[1][0] = 1;
	countRecursive(player[1][0], 1, 1, 0, 0);
	countRecursive(player[0][0], 1, 1, 0, 1);
	for (int i = 0; i < 11; i++) {
		if (i) win1 += win[0][i] * nwins[1][i-1];
		win2 += win[1][i] * nwins[0][i];
	}

	printf("21b: %lld\n\n", MAX(win1, win2));
	// old, slow solution. See below
	// play(player[1][0], player[0][0], 0, 0, 1, &win1, &win2);
}


/*
// This was way to slow. 

static void play(char p1, char p2, char s1, char s2, uint64_t c, uint64_t *w1, uint64_t *w2) {
   for (char i = p1; i < p1+7; ++i) {
        char np = (i+3) % 10 ? (i+3) % 10 : 10;
        if (s1 + np >= 21) *w1 += c * prob[i-p1];
        else play(p2, np, s2, s1 + np, c * prob[i-p1], w2, w1);
    }
}

*/
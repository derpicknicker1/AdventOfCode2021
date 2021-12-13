/*
--- Day 12: Passage Pathing ---
With your submarine's subterranean subsystems subsisting suboptimally, the only way you're getting out of this cave anytime soon is by finding a path yourself. Not just a path - the only way to know if you've found the best path is to find all of them.

Fortunately, the sensors are still mostly working, and so you build a rough map of the remaining caves (your puzzle input). For example:

start-A
start-b
A-c
A-b
b-d
A-end
b-end
This is a list of how all of the caves are connected. You start in the cave named start, and your destination is the cave named end. An entry like b-d means that cave b is connected to cave d - that is, you can move between them.

So, the above cave system looks roughly like this:

    start
    /   \
c--A-----b--d
    \   /
     end
Your goal is to find the number of distinct paths that start at start, end at end, and don't visit small caves more than once. There are two types of caves: big caves (written in uppercase, like A) and small caves (written in lowercase, like b). It would be a waste of time to visit any small cave more than once, but big caves are large enough that it might be worth visiting them multiple times. So, all paths you find should visit small caves at most once, and can visit big caves any number of times.

Given these rules, there are 10 paths through this example cave system:

start,A,b,A,c,A,end
start,A,b,A,end
start,A,b,end
start,A,c,A,b,A,end
start,A,c,A,b,end
start,A,c,A,end
start,A,end
start,b,A,c,A,end
start,b,A,end
start,b,end
(Each line in the above list corresponds to a single path; the caves visited by that path are listed in the order they are visited and separated by commas.)

Note that in this cave system, cave d is never visited by any path: to do so, cave b would need to be visited twice (once on the way to cave d and a second time when returning from cave d), and since cave b is small, this is not allowed.

Here is a slightly larger example:

dc-end
HN-start
start-kj
dc-start
dc-HN
LN-dc
HN-end
kj-sa
kj-HN
kj-dc
The 19 paths through it are as follows:

start,HN,dc,HN,end
start,HN,dc,HN,kj,HN,end
start,HN,dc,end
start,HN,dc,kj,HN,end
start,HN,end
start,HN,kj,HN,dc,HN,end
start,HN,kj,HN,dc,end
start,HN,kj,HN,end
start,HN,kj,dc,HN,end
start,HN,kj,dc,end
start,dc,HN,end
start,dc,HN,kj,HN,end
start,dc,end
start,dc,kj,HN,end
start,kj,HN,dc,HN,end
start,kj,HN,dc,end
start,kj,HN,end
start,kj,dc,HN,end
start,kj,dc,end
Finally, this even larger example has 226 paths through it:

fs-end
he-DX
fs-he
start-DX
pj-DX
end-zg
zg-sl
zg-pj
pj-he
RW-he
fs-DX
pj-RW
zg-RW
start-pj
he-WI
zg-he
pj-fs
start-RW
How many paths through this cave system are there that visit small caves at most once?

Your puzzle answer was 4912.

--- Part Two ---
After reviewing the available paths, you realize you might have time to visit a single small cave twice. Specifically, big caves can be visited any number of times, a single small cave can be visited at most twice, and the remaining small caves can be visited at most once. However, the caves named start and end can only be visited exactly once each: once you leave the start cave, you may not return to it, and once you reach the end cave, the path must end immediately.

Now, the 36 possible paths through the first example above are:

start,A,b,A,b,A,c,A,end
start,A,b,A,b,A,end
start,A,b,A,b,end
start,A,b,A,c,A,b,A,end
start,A,b,A,c,A,b,end
start,A,b,A,c,A,c,A,end
start,A,b,A,c,A,end
start,A,b,A,end
start,A,b,d,b,A,c,A,end
start,A,b,d,b,A,end
start,A,b,d,b,end
start,A,b,end
start,A,c,A,b,A,b,A,end
start,A,c,A,b,A,b,end
start,A,c,A,b,A,c,A,end
start,A,c,A,b,A,end
start,A,c,A,b,d,b,A,end
start,A,c,A,b,d,b,end
start,A,c,A,b,end
start,A,c,A,c,A,b,A,end
start,A,c,A,c,A,b,end
start,A,c,A,c,A,end
start,A,c,A,end
start,A,end
start,b,A,b,A,c,A,end
start,b,A,b,A,end
start,b,A,b,end
start,b,A,c,A,b,A,end
start,b,A,c,A,b,end
start,b,A,c,A,c,A,end
start,b,A,c,A,end
start,b,A,end
start,b,d,b,A,c,A,end
start,b,d,b,A,end
start,b,d,b,end
start,b,end
The slightly larger example above now has 103 paths through it, and the even larger example now has 3509 paths through it.

Given these new rules, how many paths through this cave system are there?

Your puzzle answer was 150004.
*/
#include "advent.h"

#define ID(x) *(uint16_t*)(x)

typedef struct step_t step_t;
struct step_t{
	struct step_t *prev;
	uint16_t id;
};

static uint16_t links[32][2];
static int cntLinks = 0;

/*##########################
# Get input data from file #
##########################*/
static bool getInput(char *f) {
	char aa[6], bb[6];

	FILE *file = fopen(f, "r");
	if (file == NULL) {
		printf("ERR: CAN NOT OPEN '%s'\n\n", f);
		return false;
	}
		
	while (fscanf(file, "%[^-]-%s\n", aa, bb) != EOF) {
		links[cntLinks][0] = ID(aa);
		links[cntLinks++][1] = ID(bb);
	}

	fclose(file);
	return true;
}

/*
 * DFS + recursion
 * Route is kept in a linked list pointing *back* to visited notes:
 *   -> Makes managing the list easy
 *   -> each level of recursion keeps its own link on the stack
 *
 * To avoid massive use of strcmp() ids are converted to uint16
 */
static int search(struct step_t *prev, int limit) {
	step_t next, *tmp;
	int count = 0, visits;

	next.prev = prev;

	for (int i = 0; i < cntLinks; i++) {
		if (links[i][0] == prev->id)
			next.id = links[i][1]; 
		else if (links[i][1] == prev->id)
			next.id = links[i][0];
		else
			continue;
		if (next.id == ID("start"))
			continue;
		if (next.id == ID("end")) {
			count++;
			continue;
		}
		if (next.id >> 8 < 'a')
			count += search(&next, limit);
		else {
			for (visits = 0, tmp = prev; tmp; tmp = tmp->prev)
			 	visits += tmp->id == next.id;
			if (visits > limit)
				continue;
			count += search(&next, limit && !visits);
		}
	}

	return count;
}

/*##########################
# Function to solve part A #
##########################*/
void get12a(char * f) {
	if (!getInput(f)) return;
	step_t step = {.prev = NULL, .id = ID("start")};
	printf("12a: %d\n", search(&step, 0));
}

/*##########################
# Function to solve part B #
##########################*/
void get12b(char *f) {
	step_t step = {.prev = NULL, .id = ID("start")};
	printf("12b: %d\n\n", search(&step, 1));
}
#undef ID

//######################################################################################
//######################################################################################
//######################################################################################
//######################################################################################
//######################################################################################
//## FIRST VERSION (took to long -> ~10s on -O3)                                      ##
//######################################################################################
//######################################################################################
//######################################################################################
//######################################################################################
//######################################################################################

// typedef struct node_t node_t;
// struct node_t {
// 	int visits;
// 	bool small;
// 	char id[6];
// 	int cntChild;
// 	node_t *children[10];
// };

// static int nodeCnt = 0, pathLen = 0, allCnt;
// static node_t nodes[128], *start, *end, *path[128];
// static uint64_t all_paths[500000];

// static uint64_t hash(node_t **nodes, int cnt) {
// 	uint64_t result = 5381;
// 	for(int i = 0; i < cnt; i++)
//         result = ((result << 5) + result) + (int)nodes[i];
// 	return result;
// }

// static node_t *get_or_create(const char *id) {
// 	for (int i = 0; i < nodeCnt; i++)
// 		if (strcmp(nodes[i].id, id) == 0)
// 			return &nodes[i];

// 	node_t *node = &nodes[nodeCnt++];
// 	strcpy(node->id, id);
// 	if (strcmp(id, "start") == 0)
// 		start = node;
// 	else if (strcmp(id, "end") == 0) 
// 		end = node;
// 	else
// 		node->small = (id[0] >= 'a') && (id[0] <= 'z') ? true : false;
	
// 	return node;
// }


// static int search_paths(node_t *node, node_t *dblNode) {

// 	int result = 0;

// 	if (node == end) {
// 		all_paths[allCnt++] = hash(path, pathLen);
// 		for (int k = 0; k < allCnt-1; k++)
// 			if(all_paths[allCnt-1] == all_paths[k]) {
// 				allCnt--;
// 				break;
// 			}
// 		return 1;
// 	}

// 	path[pathLen++] = node;

// 	node->visits++;

// 	for (int i = 0; i < node->cntChild; i++) {
// 		node_t *child = node->children[i];
// 		if (child == start)
// 			continue;
// 		else if (dblNode == child && child->visits > 1)
// 			continue;
// 		else if (dblNode != child && child->small && child->visits > 0)
// 			continue;


// 		bool can_visit = true;
// 		if (node->small && child->small) {
// 			can_visit = false;
// 			for (int k = 0; k < child->cntChild; k++) {
// 				if (!child->children[k]->small || child->children[k] == end) {
// 					can_visit = true;
// 					break;
// 				}
// 			}

// 			if (!can_visit && dblNode == node)
// 				can_visit = dblNode->visits == 1;
// 		}

// 		if (can_visit)
// 			result += search_paths(child, dblNode);
// 	}

// 	node->visits--;

// 	path[pathLen - 1] = NULL;
// 	pathLen--;

// 	return result;
// }


// /*##########################
// # Get input data from file #
// ##########################*/
// static bool getInput(char *f) {
// 	char aa[6], bb[6];

// 	FILE *file = fopen(f, "r");
// 	if (file == NULL) {
// 		printf("ERR: CAN NOT OPEN '%s'\n\n", f);
// 		return false;
// 	}
		
// 	while (fscanf(file, "%[^-]-%s\n", aa, bb) != EOF) {
// 		node_t *a = get_or_create(aa);
// 		node_t *b = get_or_create(bb);
// 		a->children[a->cntChild++] = b;
// 		b->children[b->cntChild++] = a;
// 	}

// 	fclose(file);
// 	return true;
// }


// /*##########################
// # Function to solve part A #
// ##########################*/
// void get12a(char * f) {
// 	if (!getInput(f)) return;
// 	printf("Solving takes a while (~10s)...\n");
// 	fflush(stdout);
// 	int result = 0;

// 	for (int i = 0; i < nodeCnt; i++)
// 		result = search_paths(start, &nodes[i]);

// 	printf("12a: %d\n", result);
	
// }

// /*##########################
// # Function to solve part B #
// ##########################*/
// void get12b(char *f) {
// 	printf("12b: %d\n\n", allCnt);
// }


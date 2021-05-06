/*#include <iostream>
#include "BSP.h"

int main() {
	Color yellow = Color(255, 255, 0);
	Color red = Color(255, 0, 0);
	Color blue = Color(0, 0, 255);

	Level lev = Level(3, 4);
	lev.forceAdd(1, yellow);
	lev.forceAdd(1, red);
	lev.forceAdd(1, blue);
	lev.forceAdd(1, red);
	lev.forceAdd(2, blue);
	lev.forceAdd(2, blue);
	lev.forceAdd(2, red);
	lev.forceAdd(2, yellow);
	lev.forceAdd(3, yellow);
	lev.forceAdd(3, red);
	lev.forceAdd(3, blue);
	lev.forceAdd(3, yellow);

	lev.attemptMove(2, 4);
	lev.attemptMove(3, 4);

	lev.attemptMove(1, 5);
	lev.attemptMove(2, 5);

	lev.attemptMove(1, 2);
	lev.attemptMove(3, 2);

	lev.attemptMove(1, 5);
	lev.attemptMove(3, 5);

	lev.attemptMove(1, 4);
	lev.attemptMove(3, 4);

	lev.printTubes();

	lev.freeMemory();
	return 0;
}*/
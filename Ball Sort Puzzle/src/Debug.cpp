#include <iostream>
#include "BSP.h"

int main() {
	Level lev = Level(4);

	lev.forceAdd(4, Color(5, 5, 5));


	std::cout << std::endl;
	lev.printTubes();
	std::cout << std::endl;
	lev.attemptMove(4, 3);
	lev.printTubes();

	std::cout << lev.checkAllTubes() << std::endl;

	lev.freeMemory();
	return 0;
}
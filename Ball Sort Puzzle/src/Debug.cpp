#include <iostream>
#include "BSP.h"

int main() {
	ColorStack cs = ColorStack(4);

	cs.push(Color(0, 255, 255));
	cs.push(Color(255, 0, 255));
	cs.push(Color(255, 255, 0));
	cs.push(Color(0, 0, 0));

	cs.printStack();

	cs.pop();

	cs.printStack();


	cs.freeStack();
	return 0;
}
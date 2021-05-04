#include "BSP.h"
#include <iostream>

void initLog() {
	log("Log initialized");
}

void log(const char* message) {
	std::cout << message << std::endl;
}
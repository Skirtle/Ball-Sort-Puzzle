#define _CRT_SECURE_NO_WARNINGS

// Includes
#include <GLFW/glfw3.h>
#include "BSP.h"
#include <iostream>
#include <ctime>

// Defines and constexprs
constexpr auto SEED = 5;


// Function prototypes

// Classes

int main(void) {
	int seed;
	if (SEED) {
		seed = SEED;
	}
	else {
		srand((unsigned int) time(NULL));
		seed = rand();
	}

	std::cout << "Seed: " << seed << std::endl;

	Level lev = Level(11, 4);
	
	populateLevel(lev);
	
	lev.printTubes();

	std::vector<std::vector<std::string>> allStates;
	
	
	GLFWwindow* window;
	// Initialize the library 
	if (!glfwInit()) return -1;
	// Create a windowed mode window and its OpenGL context 
	window = glfwCreateWindow(640, 640, "Ball Sort Puzzle", NULL, NULL);
	if (!window) {
		glfwTerminate();
		return -1;
	}
	// Make the window's context current 
	glfwMakeContextCurrent(window);
	// Set background color
	glClearColor(map(20, 0, 255, 0, 1), map(20, 0, 255, 0, 1), map(20, 0, 255, 0, 1), 0);
	// Loop until the user closes the window 
	while (!glfwWindowShouldClose(window)) {
		// Render here 
		glClear(GL_COLOR_BUFFER_BIT);

		/*time_t rawtime;
		struct tm timeinfo;
		time(&rawtime);
		localtime_s(&timeinfo, &rawtime);

		int from, to;
		from = rand() % lev.tubeCount + 1;
		to = rand() % lev.tubeCount + 1;

		if (!lev.checkAllTubes()) {

			if (lev.attemptMove(from, to)) {
				std::cout << "Moved from " << from << " to " << to << std::endl;
			}
		}*/

		lev.draw();


		// Swap front and back buffers 
		glfwSwapBuffers(window);
		// Poll for and process events 
		glfwPollEvents();
	}
	glfwTerminate();

	lev.freeMemory();
	return 0;
}
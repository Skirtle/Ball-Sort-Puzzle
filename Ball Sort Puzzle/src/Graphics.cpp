#define _CRT_SECURE_NO_WARNINGS

// Includes
#include <GLFW/glfw3.h>
#include "BSP.h"
#include <iostream>
#include <ctime>

// Defines and constptrs
#define YELLOW Color(255.0f, 255.0f, 0.0f)
#define RED Color(255.0f, 0.0f, 0.0f)
#define BLUE Color(0.0f, 0.0f, 255.0f)
#define GREEN Color(0.0f, 255.0f, 0.0f)
#define MAGENTA Color(128.0f, 0.0f, 128.0f)
#define ORANGE Color(255.0f, 69.0f, 0.0f)
#define CYAN Color(0.0f, 255.0f, 255.0f)
#define PI (float) acos(-1.0)
#define SEED 5
constexpr auto TUBE_Y_SIZE = 0.4f;
constexpr auto TUBE_X_SIZE = 0.1f;
constexpr auto BALL_RADIUS = 0.045f;

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

	Level lev = Level(7, 4);
	lev.forceAdd(1, CYAN);
	lev.forceAdd(1, YELLOW);
	lev.forceAdd(1, GREEN);
	lev.forceAdd(1, GREEN);

	lev.forceAdd(2, ORANGE);
	lev.forceAdd(2, RED);
	lev.forceAdd(2, BLUE);
	lev.forceAdd(2, RED);

	lev.forceAdd(3, MAGENTA);
	lev.forceAdd(3, YELLOW);
	lev.forceAdd(3, MAGENTA);
	lev.forceAdd(3, MAGENTA);

	lev.forceAdd(4, ORANGE);
	lev.forceAdd(4, YELLOW);
	lev.forceAdd(4, CYAN);
	lev.forceAdd(4, ORANGE);

	lev.forceAdd(5, BLUE);
	lev.forceAdd(5, CYAN);
	lev.forceAdd(5, YELLOW);
	lev.forceAdd(5, RED);

	lev.forceAdd(6, RED);
	lev.forceAdd(6, GREEN);
	lev.forceAdd(6, GREEN);
	lev.forceAdd(6, CYAN);

	lev.forceAdd(7, BLUE);
	lev.forceAdd(7, ORANGE);
	lev.forceAdd(7, BLUE);
	lev.forceAdd(7, MAGENTA);

	lev.printTubes();
	
	GLFWwindow* window;
	// Initialize the library 
	if (!glfwInit())
		return -1;
	// Create a windowed mode window and its OpenGL context 
	window = glfwCreateWindow(640, 640, "Ball Sort Puzzle", NULL, NULL);
	if (!window) {
		glfwTerminate();
		return -1;
	}
	// Make the window's context current 
	glfwMakeContextCurrent(window);
	glClearColor(map(20, 0, 255, 0, 1), map(20, 0, 255, 0, 1), map(20, 0, 255, 0, 1), 0);
	// Loop until the user closes the window 
	while (!glfwWindowShouldClose(window)) {
		// Render here 
		glClear(GL_COLOR_BUFFER_BIT);

		time_t rawtime;
		struct tm timeinfo;
		time(&rawtime);
		localtime_s(&timeinfo, &rawtime);

		int from, to;
		/*from = rand() % lev.tubeCount + 1;
		to = rand() % lev.tubeCount + 1;*/

		if (!lev.checkAllTubes()) {
			std::cin >> from;
			std::cin >> to;

			if (lev.attemptMove(from, to)) {
				std::cout << "Moved from " << from << " to " << to << std::endl;
			}
		}

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
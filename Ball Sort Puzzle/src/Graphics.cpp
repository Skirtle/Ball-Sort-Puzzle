#define _CRT_SECURE_NO_WARNINGS

// Includes
#include <GLFW/glfw3.h>
#include "BSP.h"
#include <iostream>
#include <ctime>

// Defines, constexprs, and globals
constexpr auto SEED = 0;
std::vector<std::vector<std::string>> allStates;
bool end = false;

// Function prototypes
std::string backtrack(Level& level, std::vector<std::vector<std::string>> visited, std::string moves);

int main(void) {
	int seed;
	if (SEED) seed = SEED;
	else {
		srand((unsigned int) time(NULL));
		seed = rand();
	}

	

	Level level = Level(11, 4); // 78
	//Level level = Level(5, 4);    // 8
	populateLevel(level);
	std::cout << "Seed: " << seed << std::endl;
	level.printTubes();

	std::string moves = "";

	moves = backtrack(level, allStates, "");

	std::cout << "Moves: " << moves << std::endl;
	
	
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
	glClearColor(map(28, 0, 255, 0, 1), map(28, 0, 255, 0, 1), map(28, 0, 255, 0, 1), 0);

	// Loop until the user closes the window 
	while (!glfwWindowShouldClose(window)) {
		// Render here 
		glClear(GL_COLOR_BUFFER_BIT);

		level.draw();
		
		// Swap front and back buffers 
		glfwSwapBuffers(window);
		// Poll for and process events 
		glfwPollEvents();
	}
	glfwTerminate();

	level.freeMemory();
	return 0;
}

std::string backtrack(Level& level, std::vector<std::vector<std::string>> visited, std::string move) {
	if (end) {
		return move;
	}

	if (level.checkAllTubes()) {
		end = true;
		return move;
	}

	for (int i = 1; i <= level.tubeCount; i++) {
		for (int j = 1; j <= level.tubeCount; j++) {

			if (end) return move;
			if (!level.checkValidMove(j, i)) continue; // check if valid move

			// do the move
			level.attemptMove(j, i);
			if (checkForState(visited, level.generateID())) { // if we've been in this state before...
				level.forceMove(i, j);
				continue;
			}

			move += std::to_string(j) + "->" + std::to_string(i) + ", ";

			visited.push_back(level.generateID());
			move = backtrack(level, visited, move);
		}
	}

	return move;
}
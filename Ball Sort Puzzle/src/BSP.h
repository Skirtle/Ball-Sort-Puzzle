#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <GLFW/glfw3.h>
#include <string>
#include <vector>

class Color {
private:
	float r, g, b;
	char symbol;
public:
	Color();
	Color(float red, float green, float blue);
	Color(float red, float green, float blue, char symbol);
	void setRed(float red);
	void setGreen(float green);
	void setBlue(float blue);
	void setColor(float red, float green, float blue);
	const bool isEqualTo(Color c);
	const float getRed() const;
	const float getGreen() const;
	const float getBlue() const;
	const char getSymbol();
	friend std::ostream& operator<<(std::ostream& out, const Color & c);
};

class ColorStack {
private:
	Color* arr;
public:
	int maxSize;
	int capacity;
	bool empty;

	ColorStack();
	ColorStack(int size);
	bool push(Color c);
	Color pop();
	const Color peek();
	const void printStack();
	void freeStack();
	bool isEmpty();
	bool isValid();
	std::string generateID();
};

class Level {
private:
	ColorStack* tubes;

public:
	int colorCount;
	int tubeCount;

	Level(int n, int stackSize);
	void freeMemory();
	void printTubes();
	void draw();
	bool forceAdd(int tube, Color c);
	bool forceMove(int oldTube, int newTube);
	bool attemptMove(int oldTube, int newTube);
	bool checkAllTubes();
	bool checkValidMove(int oldTube, int newTube);
	ColorStack getColorStack(int n);
	std::vector<std::string> generateID();
};

std::ostream& operator<<(std::ostream& os, Color const& c);
float map(float val, float oldStart, float oldEnd, float newStart, float newEnd);
void createTube(float x, float y);
void createLine(float x1, float y1, float x2, float y2);
void createCircle(float x, float y, float r, Color c);
void populateLevel(Level& lev);
bool compareIDs(std::vector<std::string> vec1, std::vector<std::string> vec2);
bool checkForState(std::vector<std::vector<std::string>> main, std::vector<std::string> vari);
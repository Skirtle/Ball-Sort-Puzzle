#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <iostream>

class Color {
private:
	float r, g, b;
public:
	Color();
	Color(float red, float green, float blue);
	void setRed(float red);
	void setGreen(float green);
	void setBlue(float blue);
	void setColor(float red, float green, float blue);
	const bool isEqualTo(Color c);
	const float getRed() const;
	const float getGreen() const;
	const float getBlue() const;
	friend std::ostream& operator<<(std::ostream& out, const Color & c);
};

class ColorStack {
private:
	Color* arr;
public:
	int maxSize;
	int capacity;
	bool empty;

	ColorStack(int size); bool push(Color c);
	Color pop();
	const Color peak();
	const void printStack();
	void freeStack();
	bool isEmpty();
};

class Level {
private:
	ColorStack* tubes;

public:
	int colorCount;

	Level(int n, int stackSize);
	void freeMemory();
	void printTubes();
	bool forceAdd(int tube, Color c);
	bool forceMove(int oldTube, int newTube);
	bool isTubeValid(int tube);
	bool attemptMove(int oldTube, int newTube);
	bool checkAllTubes();

};

std::ostream& operator<<(std::ostream& os, Color const& c);
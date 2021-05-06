#include "BSP.h"
#include <iostream>

std::ostream& operator<<(std::ostream &os, const Color &c) {
	return os << "(" << c.r << ", " << c.g << ", " << c.b << ")";
}


Color::Color() {
	setRed(255.0f);
	setGreen(255.0f);
	setBlue(255.0f);
}
Color::Color(float red, float green, float blue) {
	setColor(red, green, blue);
}
void Color::setRed(float red) {
	r = red;
}
void Color::setGreen(float green) {
	g = green;
}
void Color::setBlue(float blue) {
	b = blue;
}
void Color::setColor(float red, float green, float blue) {
	setRed(red);
	setGreen(green);
	setBlue(blue);
}
const bool Color::isEqualTo(Color c) {
	return r == c.r && g == c.g && b == c.b;
}
const float Color::getRed() const {
	return r;
}
const float Color::getGreen() const {
	return g;
}
const float Color::getBlue() const {
	return b;
}


ColorStack::ColorStack(int size) {
	if (size <= 0) size = 1;
	maxSize = size;
	arr = (Color*)malloc(size * sizeof(Color));

	if (!arr) {
		std::cout << "Could not initialize" << std::endl;
		free(arr);
	}

	capacity = 0;
	empty = true;
}
const void ColorStack::printStack() {
	for (int i = 0; i < capacity; i++) {
		const Color c = arr[i];
		std::cout << c;
		if (i != capacity - 1) {
			std::cout << ", ";
		}
	}
	std::cout << std::endl;
}
const Color ColorStack::peak() {
	return arr[capacity - 1];
}
Color ColorStack::pop() {
	Color c = arr[capacity - 1];
	capacity--;

	if (capacity == 0) empty = true;

	return c;
}
bool ColorStack::push(Color c) {
	if (capacity >= maxSize) return false;

	arr[capacity] = c;
	capacity++;
	empty = false;

	return true;
}
void ColorStack::freeStack() {
	free(arr);
}
bool ColorStack::isEmpty() {
	if (capacity == 0) empty = true;
	return empty;
}


Level::Level(int n) {
	colorCount = n;
	int tubeCount = n + 2;
	tubes = (ColorStack*) calloc(tubeCount, sizeof(ColorStack));

	if (tubes) {
		for (int i = 0; i < tubeCount; i++) {
			tubes[i] = ColorStack(n);
		}
	}
}
void Level::freeMemory() {
	for (int i = 0; i < colorCount + 2; i++) {
		tubes[i].freeStack();
	}
	free(tubes);
}
bool Level::forceAdd(int tube, Color c) {
	if (!tubes[tube - 1].push(c)) {
		std::cout << "Cannot add " << c << " to test tube " << tube << std::endl;
		return false;
	}
	else {
		std::cout << "Succesfully added " << c << " to test tube " << tube << std::endl;
		return true;
	}
}
bool Level::forceMove(int oldTube, int newTube) {
	return tubes[newTube - 1].push(tubes[oldTube - 1].pop());
}
bool Level::isTubeValid(int tube) {
	if (tubes[tube - 1].isEmpty()) return true;

	if (tubes[tube - 1].capacity != tubes[tube - 1].maxSize) {
		return false;
	}

	Color toComp = tubes[tube - 1].pop();
	Color* revColors = (Color*)malloc(sizeof(Color) * tubes[tube - 1].capacity);
	if (!revColors) {
		std::cout << "Could not allocate memory" << std::endl;
		return NULL;
	}

	revColors[0] = toComp;

	while (!tubes[tube - 1].isEmpty()) {
		Color c = tubes[tube - 1].pop();
		if (!toComp.isEqualTo(c)) {
			return false;
		}
	}

	for (int i = tubes[tube - 1].maxSize - 1; i >= 0; i--) {
		int index = -i + tubes[tube - 1].maxSize - 1;
		Color c = revColors[index];

		tubes[tube - 1].push(c);
	}

	free(revColors);
	return true;
}
void Level::printTubes() {
	for (int i = 0; i < colorCount + 2; i++) {
		std::cout << "Tube " << (i + 1) << ": ";
		tubes[i].printStack();
	}
}
bool Level::attemptMove(int oldTube, int newTube) {
	if (tubes[oldTube - 1].isEmpty() || tubes[newTube - 1].capacity >= tubes[newTube - 1].maxSize) {
		return false;
	}

	Color c1 = tubes[oldTube - 1].pop();
	Color c2 = tubes[newTube - 1].peak();

	if (c1.isEqualTo(c2)) {
		tubes[newTube - 1].push(c1);
	}
	else {
		tubes[oldTube - 1].push(c1);
		return false;
	}
	return true;
}
bool Level::checkAllTubes() {
	for (int i = 1; i < colorCount + 3; i++) {
		if (!isTubeValid(i)) {
			return false;
		}
	}
	return true;
}
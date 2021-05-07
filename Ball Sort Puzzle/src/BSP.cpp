#include "BSP.h"
#include <iostream>
#include <string>

#define YELLOW Color(255.0f, 255.0f, 0.0f)
#define RED Color(255.0f, 0.0f, 0.0f)
#define BLUE Color(0.0f, 0.0f, 255.0f)
#define GREEN Color(0.0f, 255.0f, 0.0f)
#define PI (float) acos(-1.0)
constexpr auto TUBE_Y_SIZE = 0.4f;
constexpr auto TUBE_X_SIZE = 0.1f;
constexpr auto BALL_RADIUS = 0.045f;

std::ostream& operator<<(std::ostream &os, const Color &c) {
	return os << "(" << c.r << ", " << c.g << ", " << c.b << ")";
}
float map(float val, float oldStart, float oldStop, float newStart, float newStop) {
	return newStart + (newStop - newStart) * ((val - oldStart) / (oldStop - oldStart));
}
void createTube(float x, float y) {
	createLine(x, y, x, y - TUBE_Y_SIZE);
	createLine(x, y - TUBE_Y_SIZE, x + TUBE_X_SIZE, y - TUBE_Y_SIZE);
	createLine(x + TUBE_X_SIZE, y, x + TUBE_X_SIZE, y - TUBE_Y_SIZE);
}
void createLine(float x1, float y1, float x2, float y2) {
	glBegin(GL_LINES);
	glVertex2f(x1, y1);
	glVertex2f(x2, y2);
	glEnd();
}
void createCircle(float x, float y, float r, Color c) {
	int i;
	int triangleAmount = 20; //# of triangles used to draw circle

	//GLfloat radius = 0.8f; //radius
	float twicePi = 2.0f * PI;

	glBegin(GL_TRIANGLE_FAN);
	glColor3f(c.getRed(), c.getGreen(), c.getBlue());
	glVertex2f(x, y); // center of circle
	for (i = 0; i <= triangleAmount; i++) {
		glVertex2f(
			x + (r * (GLfloat)cos(i * twicePi / triangleAmount)),
			y + (r * (GLfloat)sin(i * twicePi / triangleAmount))
		);
	}
	glColor3f(255, 255, 255);
	glEnd();
}

Color::Color() {
	setRed(1.0f);
	setGreen(1.0f);
	setBlue(1.0f);
}
Color::Color(float red, float green, float blue) {
	red = map(red, 0.0f, 255.0f, 0.0f, 1.0f);
	green = map(green, 0.0f, 255.0f, 0.0f, 1.0f);
	blue = map(blue, 0.0f, 255.0f, 0.0f, 1.0f);
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

ColorStack::ColorStack() {
	ColorStack(4);
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
	int i = 0;
	for (i = 0; i < capacity; i++) {
		const Color c = arr[i];
		std::cout << c;
		if (i != capacity - 1) {
			std::cout << ", ";
		}
	}

	if (i == 0) std::cout << "EMPTY";
	std::cout << std::endl;
}
const Color ColorStack::peek() {
	if (isEmpty()) return Color(-1, -1, -1);
	return arr[capacity - 1];
}
Color ColorStack::pop() {
	Color c = arr[capacity - 1];
	capacity--;

	if (capacity == 0) empty = true;

	return c;
}
bool ColorStack::push(Color c) {
	if (capacity >= maxSize) {
		capacity = maxSize;
		return false;
	}

	arr[capacity] = c;
	capacity++;

	empty = false;

	return true;
}
void ColorStack::freeStack() {
	free(arr);
}
bool ColorStack::isEmpty() {
	if (capacity <= 0) {
		empty = true;
		capacity = 0;
	}
	else {
		empty = false;
	}
	return empty;
}
ColorStack Level::getColorStack(int n) {
	return tubes[n - 1];
}
bool ColorStack::isValid() {
	if (isEmpty() || empty || capacity == 0) {
		return true;
	}

	if (capacity < maxSize) {
		return false;
	}

	bool isValid = true;
	Color compColor = peek();
	int cap = capacity;
	ColorStack reversed = ColorStack(capacity);

	// NULL color, first check if empty failed.
	// if this ever happens, gotta debug
	if (compColor.isEqualTo(Color(-1, -1, -1))) return true;

	for (int i = 0; i < cap; i++) {
		Color popped = pop();
		reversed.push(popped);
		if (!popped.isEqualTo(compColor)) {
			isValid = false;
		}
	}

	for (int i = 0; i < cap; i++) {
		Color popped = reversed.pop();
		push(popped);
	}

	reversed.freeStack();
	return isValid;
}


Level::Level(int n, int stackSize) {
	colorCount = n;
	tubeCount = n + 2;
	tubes = (ColorStack*) calloc(tubeCount, sizeof(ColorStack));

	if (tubes) {
		for (int i = 0; i < tubeCount; i++) {
			tubes[i] = ColorStack(stackSize);
		}
	}
}
void Level::freeMemory() {
	for (int i = 0; i < colorCount + 2; i++) {
		tubes[i].freeStack();
	}
	free(tubes);
}
void Level::printTubes() {
	for (int i = 0; i < colorCount + 2; i++) {
		std::cout << "Tube " << (i + 1) << ": ";
		tubes[i].printStack();
	}
}
void Level::draw() {
	float x = -0.5f;
	float y = TUBE_Y_SIZE / 2.0f;

	x = -(2.0f / colorCount);
	float dx = x / 2.0f;

	x = -0.9f + (TUBE_X_SIZE / 2.0f);
	dx = 1.8f / tubeCount;

	for (int s = 0; s < tubeCount; s++) {
		createTube(x, y);
		ColorStack tempStack = ColorStack(tubes[s].capacity);

		int cap = tubes[s].capacity;
		int i = 0;

		for (i = 0; i < cap; i++) {
			tempStack.push(tubes[s].pop());
		}

		for (i = 0; i < cap; i++) {
			Color color = tempStack.pop();
			tubes[s].push(color);
			float xCoord, yCoord;
			xCoord = x + (TUBE_X_SIZE / 2.0f);
			yCoord = y - (TUBE_Y_SIZE - BALL_RADIUS * ((2 * i) + 1));
			createCircle(xCoord, yCoord, BALL_RADIUS, color);
		}

		tempStack.freeStack();
		x += dx;
	}
}
bool Level::forceAdd(int tube, Color c) {
	if (!tubes[tube - 1].push(c)) {
		//std::cout << "Cannot add " << c << " to test tube " << tube << std::endl;
		return false;
	}
	else {
		//std::cout << "Succesfully added " << c << " to test tube " << tube << std::endl;
		return true;
	}
}
bool Level::forceMove(int oldTube, int newTube) {
	if (oldTube == newTube) return false;
	return tubes[newTube - 1].push(tubes[oldTube - 1].pop());
}
bool Level::attemptMove(int oldTube, int newTube) {
	if (!checkValidMove(oldTube, newTube)) {
		return false;
	}

	/*else if (tubes[oldTube - 1].isEmpty() || tubes[newTube - 1].capacity >= tubes[newTube - 1].maxSize || oldTube == newTube) {
		return false;
	*/

	Color c1 = tubes[oldTube - 1].peek();
	Color c2 = tubes[newTube - 1].peek();

	if (c1.isEqualTo(c2) || tubes[newTube - 1].isEmpty()) {
		tubes[newTube - 1].push(tubes[oldTube - 1].pop());
		return true;
	}
	return false;
}
bool Level::checkAllTubes() {
	for (int i = 0; i < tubeCount; i++) {
		if (!tubes[i].isValid()) {
			return false;
		}
	}
	return true;
}
bool Level::checkValidMove(int oldTube, int newTube) {
	if (tubes[oldTube - 1].isEmpty() || tubes[newTube - 1].capacity >= tubes[newTube - 1].maxSize || oldTube == newTube) {
		return false;
	}
	else if (tubes[newTube - 1].isEmpty()) {
		return true;
	}

	Color c1 = tubes[oldTube - 1].peek();
	Color c2 = tubes[newTube - 1].peek();

	return c1.isEqualTo(c2);
}
std::string Level::generateID() {
	std::string s = "";
	
	return s;
}
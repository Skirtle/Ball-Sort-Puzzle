#include "BSP.h"
#include <iostream>
#include <string>
#include <vector>

#define YELLOW Color(255.0f, 255.0f, 0.0f, 'y')
#define RED Color(255.0f, 0.0f, 0.0f, 'r')
#define BLUE Color(0.0f, 0.0f, 255.0f, 'b')
#define GREEN Color(0.0f, 255.0f, 0.0f, 'g')
#define MAGENTA Color(128.0f, 0.0f, 128.0f, 'm')
#define ORANGE Color(255.0f, 69.0f, 0.0f, 'o')
#define CYAN Color(0.0f, 255.0f, 255.0f, 'c')
#define DARK_TURQ Color(4, 92, 90, 'T')
#define PINK Color(255, 105, 180, 'p')
#define DARK_GREEN Color(0, 100, 0, 'G')
#define WHITE Color(250, 250, 250, 'w')
#define PI (float) acos(-1.0)
constexpr auto TUBE_Y_SIZE = 0.4f;
constexpr auto TUBE_X_SIZE = 0.1f;
constexpr auto BALL_RADIUS = 0.045f;

std::ostream& operator<<(std::ostream &os, const Color &c) {
	return os << c.symbol;
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
bool compareIDs(std::vector<std::string> vec1, std::vector<std::string> vec2) {
	if (vec1.size() != vec2.size()) return false;

	for (unsigned int i = 0; i < vec1.size(); i++) {
		for (unsigned int j = 0; j < vec2.size(); j++) {
			// this is an already checked stack
			if (vec2.at(j) == "****") continue;

			if (vec2.at(j) == vec1.at(i)) {
				vec2.at(j) = "****";
				break;
			}
		}
	}

	for (unsigned int i = 0; i < (int)vec2.size(); i++) {
		if (vec2.at(i) != "****") {
			return false;
		}
	}

	return true;
}
bool checkForState(std::vector<std::vector<std::string>> main, std::vector<std::string> vari) {
	for (unsigned int i = 0; i < main.size(); i++) {
		if (compareIDs(main.at(i), vari)) return true;
	}
	return false;
}
void populateLevel(Level& lev) {
	lev.forceAdd(1, BLUE);
	lev.forceAdd(1, YELLOW);
	lev.forceAdd(1, DARK_TURQ);
	lev.forceAdd(1, PINK);

	lev.forceAdd(2, GREEN);
	lev.forceAdd(2, DARK_GREEN);
	lev.forceAdd(2, MAGENTA);
	lev.forceAdd(2, YELLOW);

	lev.forceAdd(3, GREEN);
	lev.forceAdd(3, DARK_GREEN);
	lev.forceAdd(3, GREEN);
	lev.forceAdd(3, DARK_TURQ);

	lev.forceAdd(4, CYAN);
	lev.forceAdd(4, BLUE);
	lev.forceAdd(4, ORANGE);
	lev.forceAdd(4, MAGENTA);

	lev.forceAdd(5, RED);
	lev.forceAdd(5, ORANGE);
	lev.forceAdd(5, DARK_TURQ);
	lev.forceAdd(5, CYAN);

	lev.forceAdd(6, CYAN);
	lev.forceAdd(6, MAGENTA);
	lev.forceAdd(6, MAGENTA);
	lev.forceAdd(6, BLUE);

	lev.forceAdd(7, PINK);
	lev.forceAdd(7, WHITE);
	lev.forceAdd(7, WHITE);
	lev.forceAdd(7, DARK_TURQ);

	lev.forceAdd(8, YELLOW);
	lev.forceAdd(8, ORANGE);
	lev.forceAdd(8, PINK);
	lev.forceAdd(8, RED);

	lev.forceAdd(9, BLUE);
	lev.forceAdd(9, CYAN);
	lev.forceAdd(9, RED);
	lev.forceAdd(9, ORANGE);

	lev.forceAdd(10, PINK);
	lev.forceAdd(10, RED);
	lev.forceAdd(10, WHITE);
	lev.forceAdd(10, YELLOW);

	lev.forceAdd(11, DARK_GREEN);
	lev.forceAdd(11, WHITE);
	lev.forceAdd(11, GREEN);
	lev.forceAdd(11, DARK_GREEN);
	/*lev.forceAdd(1, GREEN);
	lev.forceAdd(1, YELLOW);
	lev.forceAdd(1, BLUE);
	lev.forceAdd(1, BLUE);

	lev.forceAdd(2, GREEN);
	lev.forceAdd(2, YELLOW);
	lev.forceAdd(2, GREEN);
	lev.forceAdd(2, BLUE);

	lev.forceAdd(3, RED);
	lev.forceAdd(3, YELLOW);
	lev.forceAdd(3, RED);
	lev.forceAdd(3, YELLOW);

	lev.forceAdd(4, GREEN);
	lev.forceAdd(4, MAGENTA);
	lev.forceAdd(4, MAGENTA);
	lev.forceAdd(4, RED);

	lev.forceAdd(5, MAGENTA);
	lev.forceAdd(5, MAGENTA);
	lev.forceAdd(5, RED);
	lev.forceAdd(5, BLUE);*/
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
Color::Color(float red, float green, float blue, char sym) {
	red = map(red, 0.0f, 255.0f, 0.0f, 1.0f);
	green = map(green, 0.0f, 255.0f, 0.0f, 1.0f);
	blue = map(blue, 0.0f, 255.0f, 0.0f, 1.0f);
	setColor(red, green, blue);
	symbol = sym;
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
const char Color::getSymbol() {
	return symbol;
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
std::string ColorStack::generateID() {
	std::string s = "";

	int cap = capacity;
	ColorStack revStack = ColorStack(cap);

	for (int i = 0; i < cap; i++) {
		Color c = pop();
		revStack.push(c);
	}

	for (int i = 0; i < cap; i++) {
		Color c = revStack.pop();
		push(c);
		s += c.getSymbol();
	}

	for (int i = 0; i < 4 - cap; i++) {
		s += "N";
	}

	revStack.freeStack();
	return s;
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
	bool oldValidAndFull = tubes[oldTube - 1].capacity == tubes[oldTube - 1].maxSize && tubes[oldTube - 1].isValid();

	if (oldTube == newTube || tubes[oldTube - 1].isEmpty() 
		|| tubes[newTube - 1].capacity == tubes[newTube - 1].maxSize 
		|| oldValidAndFull) return false;
	if (tubes[newTube - 1].isEmpty()) return true;

	Color c1 = tubes[oldTube - 1].peek();
	Color c2 = tubes[newTube - 1].peek();

	return c1.getSymbol() == c2.getSymbol();
}
std::vector<std::string> Level::generateID() {
	std::vector<std::string> strVector;

	for (int i = 0; i < tubeCount; i++) {
		strVector.push_back(tubes[i].generateID());
	}

	return strVector;
}

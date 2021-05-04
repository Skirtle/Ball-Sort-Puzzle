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
	return arr[capacity];
}
Color ColorStack::pop() {
	Color c = arr[capacity];
	capacity--;

	return c;
}
bool ColorStack::push(Color c) {
	if (capacity == maxSize) return false;

	arr[capacity] = c;
	capacity++;

	return true;
}
void ColorStack::freeStack() {
	free(arr);
}
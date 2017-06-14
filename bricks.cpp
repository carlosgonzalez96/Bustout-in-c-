#include "bricks.h"
#include "ofMain.h"

const char RED = 'r';
const char BLUE = 'b';
const char GREEN = 'g';
const char PURPLE = 'p';
const char ORANGE = 'o';
const char GREY = 'z';

Brick::Brick() {
	
}

Brick::Brick(int x, int y, float w, float h, char kind, int gone) {
	this->x = x;
	this->y = y;
	this->w = w;
	this->h = h;
	this->gone = gone;
	if (kind == RED) {
		this->points = 100;
		this->color = ofColor(255, 0, 0);
		this->type = 1;
	}
	else if (kind == BLUE) {
		this->points = 200;
		this->color = ofColor(0, 0, 255);
		this->type = 2;
	}
	else if (kind == GREEN) {
		this->points = 300;
		this->color = ofColor(0, 255, 0);
		this->type = 3;
	}
	else if (kind == PURPLE) {
		this->points = 500;
		this->color = ofColor(96, 0, 193);
		this->type = 4;
	}
	else if (kind == ORANGE) {
		this->points = 1000;
		this->color = ofColor(255, 123, 0);
		this->type = 5;
	}
	else if (kind == GREY) {
		this->points = -500;
		this->color = ofColor(158, 158, 158);
		this->type = 6;
	}
}

void Brick::drawBricks() {
		ofSetColor(color);
		ofDrawRectangle(x, y, w, h);
}

void Brick::destroy() {
	destroyed = true;
}
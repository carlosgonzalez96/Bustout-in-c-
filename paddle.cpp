#include "paddle.h"
#include "ofMain.h"

Paddle::Paddle() {

}

Paddle::Paddle(float x, float y, float w, float h, float v, ofColor color) {
	this->w = w;
	this->h = h;
	this->x = x;
	this->y = y;
	this->v = v;
	this->color = color;
}

void Paddle::setSize(int lvl) {
	w -= (lvl * 4);
}
void Paddle::drawPaddle() {
	ofSetColor(color);
	ofDrawRectangle(x, y, w, h);
}

void Paddle::movePaddle() {
	// paddle doesnt go outside edges
	if (x <= 0) {
		x = 0;
	}
	else if (x >= ofGetWindowWidth() - w) {
		x = ofGetWindowWidth() - w;
	}

	//Mouse tracking
	if (ofGetMouseX() < x) {
		x -= 10;
	}

	if (ofGetMouseX() > x) {
		x += 10;
	}
}

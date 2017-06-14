#pragma once
#include "ofMain.h"
class Paddle {
public:
	float x;
	float y;
	float w;
	float h;
	float v;
	ofColor color;

	Paddle();
	Paddle(float x, float y, float w, float h, float v, ofColor color);

	void drawPaddle();
	void movePaddle();
	void setSize(int lvl);
};
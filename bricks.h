#pragma once
#include "ofMain.h"
class Brick {
public:
	bool destroyed;
	int x;
	int y;
	int gone;
	float w;
	float h;
	ofColor color;
	int points;
	int type;


	Brick();
	Brick(int x, int y, float w, float h, char kind, int gone);
	void drawBricks();
	void destroy();
};
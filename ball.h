#pragma once
#include "ofMain.h"
#include "bricks.h"
class Ball {
public:
	int lives;
	int score;
	ofVec2f pos, vel, accel;
	ofColor color;

	Ball();
	Ball(int lives, int score, ofColor color);
	void drawBall();
	void moveBall();
	void ballBounce(float px, float py, float pw, float ph);
	void resetBall();
	void bounce();
	bool hits(Brick* brick);
};

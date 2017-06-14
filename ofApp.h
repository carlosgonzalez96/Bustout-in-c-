#pragma once

#include "ofMain.h"
#include "paddle.h"
#include "ball.h"
#include "bricks.h"

class ofApp : public ofBaseApp {

public:
	int level;
	void prepareBricks();
	vector<Brick*> bricks;
	Ball* ball;
	Paddle* paddle;
	Brick* brick;
	void setup();
	void update();
	void draw();
	ofImage title;
	ofImage bgHome;
	ofImage difficulty;
	ofImage lost;
	ofImage won;
	ofTrueTypeFont tryAgin;
	ofTrueTypeFont next;
	ofTrueTypeFont ballsLeft;
	ofSoundPlayer jungleMusic;
	ofSoundPlayer ticks;
	ofSoundPlayer dino1;
	ofSoundPlayer dino2;
	ofSoundPlayer dino3;
	ofSoundPlayer dino4;
	ofSoundPlayer dino5;

	void updateGameState();
	void drawStartScreen();
	void drawGameScreen();
	void drawGameOverScreen();
	void drawWinScreen();
	void keyPressed(int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y);
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void mouseEntered(int x, int y);
	void mouseExited(int x, int y);
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);

};

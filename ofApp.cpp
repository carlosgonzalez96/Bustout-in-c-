#include "ofApp.h"
#include "paddle.h"
#include "ball.h"
#include "bricks.h"

const int START_SCREEN = 0;
const int GAME_SCREEN = 1;
const int GAME_OVER_SCREEN = 2;
const int WIN_SCREEN = 3;

int gameState = START_SCREEN;
//--------------------------------------------------------------
void ofApp::setup() {
	ofSetBackgroundColor(0);
	title.load("bustouttitle.png");
	bgHome.load("bg-home-1.jpg");
	difficulty.load("difficulty.png");
	lost.load("youlost.png");
	won.load("youwon.png");
	tryAgin.load("BRLNSDB.ttf", 32);
	next.load("BRLNSDB.ttf", 32);
	ballsLeft.load("BRLNSDB.ttf", 32);
	jungleMusic.loadSound("concrete_jungle.mp3");
	ticks.loadSound("tick.mp3");
	dino1.loadSound("dino1.mp3");
	dino2.loadSound("dino2.mp3");
	dino3.loadSound("dino3.mp3");
	dino4.loadSound("dino4.mp3");
	dino5.loadSound("dino5.mp3");
	jungleMusic.play();

	ball = new Ball(3, 0, ofColor(247, 230, 0));
	ball->pos.set(ofGetWidth() / 2, ofGetHeight() / 2);
	ball->vel.set(4, 3);

	paddle = new Paddle((ofGetWidth() / 2) - 100, (ofGetHeight() / 2) + 450, 300, 50, 0, ofColor(255));
}

//--------------------------------------------------------------
void ofApp::update() {
	if (gameState == GAME_SCREEN) {
		updateGameState();
	}
	
}
//--------------------------------------------------------------
void ofApp::updateGameState() {
	//moves the ball and bounces off walls
	ball->moveBall();
	//paddle is movable with mouse
	paddle->movePaddle();
	//sfx on paddle
	if ((ball->pos.x - 30) <= (paddle->x + paddle->w)) {
		if (ball->pos.y < (paddle->y + paddle->h)) {
			if (ball->pos.y >(paddle->y)) {
				ticks.play();
			}
		}
	}
	//bounces off bricks
	for (int i = 0; i < bricks.size(); ++i) {
		if ((ball->pos.y - 30) <= (bricks[i]->y + bricks[i]->h)) {
			if ((ball->pos.y) >= (bricks[i]->y + (bricks[i]->h / 2))) {
				if ((ball->pos.x) <= ((bricks[i]->x + (bricks[i]->w)) + 1)) {
					if ((ball->pos.x) >= (bricks[i]->x) - 1) {
						if (bricks[i]->gone > 0) {
							ball->vel.y *= -1;
							ball->pos.y = ((bricks[i]->y + bricks[i]->w) + 30);
							ball->score += bricks[i]->points;
							bricks[i]->gone = 0;
							return;
						}
					}
				}
			}
		}
	}
}


//--------------------------------------------------------------
void ofApp::draw() {
	if (gameState == START_SCREEN) {
		drawStartScreen();
	}
	else if (gameState == GAME_SCREEN) {
		drawGameScreen();
		jungleMusic.stop();
	}
	else if (gameState == GAME_OVER_SCREEN) {
		drawGameOverScreen();
	}
	else if (gameState == WIN_SCREEN) {
		drawWinScreen();
	}

}
void ofApp::drawStartScreen() {
	ofDrawBitmapString("Start Screen", ofGetWidth() / 2, ofGetHeight() / 2);
	bgHome.draw((ofGetWidth() / 2) - 960, (ofGetHeight() / 2) - 540);
	title.draw((ofGetWidth() / 2) - 198, (ofGetHeight() / 2) - 400);
	difficulty.draw((ofGetWidth() / 2) - 219, (ofGetHeight() / 2) - 50);

}
void ofApp::drawGameScreen() {
	//removes a block when hit by the ball'
	for (int i = 0; i < bricks.size(); ++i) {
		if (!bricks.at(i)->destroyed && ball->hits(bricks.at(i))) {
			bricks.at(i)->destroy();
			if (bricks.at(i)->type == 1) {
				dino1.play();
			}
			else if (bricks.at(i)->type == 2) {
				dino2.play();
			}
			else if (bricks.at(i)->type == 3) {
				dino3.play();
			}
			else if (bricks.at(i)->type == 4) {
				dino4.play();
			}
			else if (bricks.at(i)->type == 5) {
				dino5.play();
			}
			else if (bricks.at(i)->type == 6) {
				dino1.play();
			}
			ball->bounce();
			break;
		}
	}

	//draw bricks
	for (int i = 0; i < bricks.size(); ++i) {
		/*if(!bricks[i]->destroyed)*/bricks.at(i)->drawBricks();
	}

	//ball left system
	ofSetColor(225);
	std::string balls = "Balls left: ";
	balls += ofToString(ball->lives);
	ballsLeft.drawString(balls, 50, 50);
	if (ball->lives <= 0) {
		gameState = GAME_OVER_SCREEN;
	}

	//score system
	ofSetColor(225);
	std::string scoreKeeper = "Score: ";
	scoreKeeper += ofToString(ball->score);
	ballsLeft.drawString(scoreKeeper, ofGetWidth() - 200, 50);

	//bounce ball from paddle
	ball->ballBounce(paddle->x, paddle->y, paddle->w, paddle->h);

	//draws paddle and ball
	ball->drawBall();
	paddle->drawPaddle();

}
void ofApp::drawGameOverScreen() {
	bgHome.draw((ofGetWidth() / 2) - 960, (ofGetHeight() / 2) - 540);
	lost.draw((ofGetWidth() / 2) - 250, (ofGetHeight() / 2) - 192);
	tryAgin.drawString("PRESS M FOR MENU", ofGetWidth() / 2 - 220, ofGetHeight() / 2 + 220);

}
void ofApp::drawWinScreen() {
	bgHome.draw((ofGetWidth() / 2) - 960, (ofGetHeight() / 2) - 540);
	won.draw((ofGetWidth() / 2) - 250, (ofGetHeight() / 2) - 205);
	next.drawString("PRESS M FOR MENU", ofGetWidth() / 2 - 200, ofGetHeight() / 2 + 250);
}
void ofApp::prepareBricks() {
	bricks.clear();
	string fileName = ofToString(level) + ".txt";
	vector<string> lines;
	ofBuffer buffer = ofBufferFromFile(fileName);

	for (auto line : buffer.getLines()) {
		lines.push_back(line);
	}
	for (int i = 0; i < lines.size(); ++i) {
		string row = lines[i];
		for (int j = 0; j < row.size(); ++j) {
			char code = row[j];
			cout << code;
			if (code == ' ') continue;
			brick = new Brick(j * ofGetWidth()/row.size(), (i * ofGetHeight()/10), ofGetWidth() / row.size(), 50, code, 1);
			bricks.push_back(brick);
		}
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
	if (key == OF_KEY_SHIFT) {
		gameState = (gameState + 1) % 4;
	}
	if (gameState == GAME_OVER_SCREEN || gameState == WIN_SCREEN) {
		if (key == 'm') {
			gameState = START_SCREEN;
		}
	}
	if (gameState == START_SCREEN) {
		if (key >= '1' && key <= '5') {
			level = key - 48;
		}
		ball->score = 0;
		ball->lives = 3;
		prepareBricks();
		paddle->setSize(level); 
		gameState = GAME_SCREEN;

	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {

}

void ofApp::mouseMoved(int x, int y) {

}

void ofApp::mouseDragged(int x, int y, int button) {

}

void ofApp::mousePressed(int x, int y, int button) {

}

void ofApp::mouseReleased(int x, int y, int button) {

}

void ofApp::mouseEntered(int x, int y) {

}

void ofApp::mouseExited(int x, int y) {

}

void ofApp::windowResized(int w, int h) {

}

void ofApp::gotMessage(ofMessage msg) {

}

void ofApp::dragEvent(ofDragInfo dragInfo) {

}

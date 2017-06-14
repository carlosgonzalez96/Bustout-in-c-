#include "ball.h"
#include "bricks.h"
Ball::Ball() {

}

Ball::Ball(int lives, int score, ofColor color) {
	this->color = color;
	this->lives = lives;
	this->score = score;
}

void Ball::drawBall() {
	ofSetColor(color);
	ofDrawCircle(pos.x, pos.y, 30);
	ofSetCircleResolution(60);
}
void Ball::moveBall() {
	pos += vel;

	//top and bottom bounderies
	if (pos.y <= 30) {
		pos.y = 30;
		vel.y *= -1;
	}
	else if (pos.y >= ofGetWindowHeight() - 30) {
		//pos.y = ofGetWindowHeight() - 30;
		//vel.y *= -1;
		resetBall();
		--lives;
	}
	//side bounderies
	if (pos.x <= 30) {
		pos.x = 30;
		vel.x *= -1;
	}
	else if (pos.x >= ofGetWindowWidth() - 30) {
		pos.x = ofGetWindowWidth() - 30;
		vel.x *= -1;
	}
}
void Ball::ballBounce(float px, float py, float pw, float ph) {
	if ((pos.x - 30) <= (px + pw)) {
		if (pos.y < (py + ph)) {
			if (pos.y >(py)) {
				vel.y *= -1;
				++score;
			}
		}
	}
}
void Ball::resetBall() {
	pos.set(ofGetWidth() / 2, ofGetHeight() / 2);
}
void Ball::bounce() {
	vel.rotate(ofRandom(-45, 45));
	vel *= -1;
}
bool Ball::hits(Brick* brick) {
	if (pos.x <= brick->x + brick->w && pos.y <= brick->y + brick->h) {
		return true;
	}
}
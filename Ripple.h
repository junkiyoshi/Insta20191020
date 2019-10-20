#pragma once
#include "ofMain.h"

class Ripple
{
public:

	Ripple();
	Ripple(glm::vec2 location);
	void update();
	void draw();
	bool isDead();
private:

	glm::vec2 location;
	float radius;
	ofMesh mesh;
};
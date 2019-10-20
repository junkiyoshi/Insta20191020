#include "Ripple.h"

//--------------------------------------------------------------
Ripple::Ripple() : Ripple(glm::vec2()) {

}

//--------------------------------------------------------------
Ripple::Ripple(glm::vec2 location) {

	this->location = location;
	this->radius = 0;
}

//--------------------------------------------------------------
void Ripple::update() {

	this->mesh.clear();

	this->radius += 1;
	auto len = radius / 25 + 1;
	for (auto deg = 0; deg < 360; deg += 1) {

		auto out_radius = radius + len;
		auto in_location = this->location + glm::vec2(radius * cos(deg * DEG_TO_RAD), radius * sin(deg * DEG_TO_RAD));
		auto out_location = this->location + glm::vec2(out_radius * cos(deg * DEG_TO_RAD), out_radius * sin(deg * DEG_TO_RAD));

		ofColor in_color, out_color;
		float alpha = this->radius < 250 ? 255 : ofMap(this->radius, 250, 300, 255, 0);
		in_color.setHsb(ofMap(ofNoise(in_location.x * 0.001, in_location.y * 0.001, ofGetFrameNum() * 0.005), 0, 1, 0, 255), 200, 255, alpha);
		out_color.setHsb(ofMap(ofNoise(out_location.x * 0.001, out_location.y * 0.001, ofGetFrameNum() * 0.005), 0, 1, 0, 255), 200, 255, alpha);

		mesh.addVertex(ofPoint(in_location));
		mesh.addColor(in_color);
		mesh.addVertex(ofPoint(out_location));
		mesh.addColor(out_color);
	}

	for (auto i = 0; i < mesh.getVertices().size(); i += 2) {

		auto index_0 = i;
		auto index_1 = (i + 1) % mesh.getVertices().size();
		auto index_2 = (i + 2) % mesh.getVertices().size();
		auto index_3 = (i + 3) % mesh.getVertices().size();

		mesh.addIndex(index_0);
		mesh.addIndex(index_1);
		mesh.addIndex(index_2);

		mesh.addIndex(index_3);
		mesh.addIndex(index_1);
		mesh.addIndex(index_2);
	}
}

//--------------------------------------------------------------
void Ripple::draw() {

	this->mesh.draw();
}

//--------------------------------------------------------------
bool Ripple::isDead() {

	return this->radius > 300;
}
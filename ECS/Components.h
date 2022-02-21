#pragma once

#include "ComponentManager.h"

class TransformComponent : public Component {
private:
	int xpos;
	int ypos;

public:
	int x() { return xpos; }
	int y() { return ypos; }

	TransformComponent(std::string txt) { std::cout << txt << std::endl; }

	void init() override {
		xpos = 10;
		ypos = 10;
	}

	void setPos(int x, int y) {
		xpos = x;
		ypos = y;
	}
};
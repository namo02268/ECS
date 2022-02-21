#pragma once

#include "Component.h"

class TrasformComponent : public Component {
public:
	int xpos = 0;
	int ypos = 0;

public:
	void init() override {
		std::cout << "init Transfrom" << std::endl;
	}
};

class ColliderComponent : public Component {
public:
	bool collider = true;

public:
	void init() override {
		std::cout << "init Collider" << std::endl;
	}
};
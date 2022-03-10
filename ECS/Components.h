#pragma once

#include "Component.h"
#include "EntityHandle.h"

class TransformComponent : public Component {
public:
	float xpos = 5;
	float ypos = 5;
	TransformComponent(int xpos, int ypos) {
		std::cout << "Transform" << std::endl;
		this->xpos = xpos;
		this->ypos = ypos;
//		std::cout << this->xpos << std::endl;
	}
};

class ColliderComponent : public Component {
public:
	bool collider = true;
};

class RendererComponent : public Component {
public:
	int test = 1;
};
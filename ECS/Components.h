#pragma once

#include "Component.h"
#include "EntityHandle.h"

class TransformComponent : public Component {
public:
	TransformComponent() { std::cout << "Transform" << std::endl; }
	int xpos = 0;
	int ypos = 0;
};

class ColliderComponent : public Component {
public:
	bool collider = true;
};

class RendererComponent : public Component {
public:
	int test = 1;
};
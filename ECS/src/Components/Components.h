#pragma once

#include "ECS/Component.h"
#include "ECS/EntityHandle.h"

namespace ECS {
	class TransformComponent : public Component {
	public:
		float xpos = 0.0f;
		float ypos = 0.0f;
		TransformComponent(int xpos, int ypos) {
//			std::cout << "Transform" << std::endl;
			this->xpos = xpos;
			this->ypos = ypos;
		}
	};

	class PhysicComponent : public Component {
	public:
		float position = 1.0f;
		float velocity = 1.0f;
		float acceleration = 1.0f;
	};

	class ColliderComponent : public Component {
	public:
		bool collider = true;
	};

	class RendererComponent : public Component {
	public:
		int test = 1;
	};
}

#pragma once

#include "ECS/Component.h"

namespace ECS {
	struct TransformComponent : public Component {
	public:
		float x = 1.0f;
		float y = 1.0f;

	public:
		TransformComponent() {}
		TransformComponent(float x, float y) : x(x), y(y) {}
	};
}
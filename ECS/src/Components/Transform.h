#pragma once

#include "ECS/Component.h"

namespace ECS {
	struct TransformComponent : public Component {
		TransformComponent(float x = 0.0f, float y = 0.0f) : x(x), y(y) {}
		TransformComponent() {}

		float x;
		float y;
	};
}
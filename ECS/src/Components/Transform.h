#pragma once

#include "ECS/Component.h"

namespace ECS {
	struct TransformComponent : public Component {
		TransformComponent(float x, float y) : x(x), y(y) {}
		TransformComponent() {}

		float x = 1.0f;
		float y = 1.0f;
	};
}
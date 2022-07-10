#pragma once

#include "ECS/Component.h"

namespace ECS {
	class TransformComponent : public Component {
	public:
		float x = 1.0f;
		float y = 1.0f;

	public:
		TransformComponent() {}
		TransformComponent(float x, float y) : x(x), y(y) {}
	};

	class PhysicComponent : public Component {
	public:
		float vx = 1.0f;
		float vy = 1.0f;
		float ax = 1.0f;
		float ay = 1.0f;

	public:
		PhysicComponent() {}
		PhysicComponent(float vx, float vy, float ax, float ay) : vx(vx), vy(vy), ax(ax), ay(ay) {}
	};

	class ColliderComponent : public Component {
	public:
		bool collider = true;
	};

	class RendererComponent : public Component {
	public:
		int test = 1;
		double test2;
		double test3;
		double test4;
		double test5;
		double test6;
	};
}

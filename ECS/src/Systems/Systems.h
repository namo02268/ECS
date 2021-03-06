#pragma once

#include "ECS/Scene.h"
#include "ECS/System.h"
#include "Components/Transform.h"

namespace ECS {
	class TransformSystem : public System {
	public:
		TransformSystem() {
			auto family = getComponentTypeID<TransformComponent>();
			m_requiredComponent[family] = true;
		}

		void init() override {
			for (auto& e : m_entityArray) {
				auto tansformComponent = m_parentScene->getComponent<TransformComponent>(e);
			}
		}

		void update(float dt) override {

		}

		void draw() override {

		}
	};

	struct CollisionEvent : public Event {
	public:
		CollisionEvent() { std::cout << "Called" << std::endl; }
		~CollisionEvent() { std::cout << "Terminate" << std::endl; }
	};

	class CombatSystem : public System {
	public:
		void init() override {
			m_eventHandler->subscribe(this, &CombatSystem::onCollisionEvent);
		}
		void update(float dt) override {

		}

		void draw() override {

		}
		void onCollisionEvent(CollisionEvent* collision) {
			std::cout << "Recieved" << std::endl;
		}
	};

	class PhysicsSystem : public System {
	public:
		void init() override {
		}
		void update(float dt) override {
			CollisionEvent event;
			m_eventHandler->publish(&event);
		}
		void draw() override {

		}
	};
}

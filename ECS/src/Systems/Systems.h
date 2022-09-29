#pragma once

#include "ECS/ECS.h"
#include "ECS/System.h"
#include "Components/Transform.h"

namespace ECS {
	class TransformSystem : public System {
	public:
		TransformSystem() {
			auto family = GetComponentTypeID<TransformComponent>();
			m_requiredComponent[family] = true;
		}

		void Init() override {
		}

		void Update(float dt) override {
			for (auto& e : m_entityArray) {
				auto trans = m_parentScene->GetComponent<TransformComponent>(e);
				auto parent = m_parentScene->GetComponent<Relationship>(e)->parent;
				if (parent) {
					trans->x += m_parentScene->GetComponent<TransformComponent>(parent)->x;
				}
				trans->x += trans->y;
			}
		}

		void Draw() override {

		}
	};

	struct CollisionEvent : public Event {
	public:
		CollisionEvent() { std::cout << "Called" << std::endl; }
		~CollisionEvent() { std::cout << "Terminate" << std::endl; }
	};

	class CombatSystem : public System {
	public:
		void Init() override {
			m_eventHandler->Subscribe(this, &CombatSystem::onCollisionEvent);
		}
		void Update(float dt) override {

		}

		void Draw() override {

		}
		void onCollisionEvent(CollisionEvent* collision) {
			std::cout << "Recieved" << std::endl;
		}
	};

	class PhysicsSystem : public System {
	public:
		void Init() override {
		}
		void Update(float dt) override {
			CollisionEvent event;
			m_eventHandler->Publish(&event);
		}
		void Draw() override {

		}
	};
}

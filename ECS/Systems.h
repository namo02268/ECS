#pragma once

#include "Scene.h"
#include "System.h"

class TransformSystem : public System {
public:
	TransformSystem() {
		auto family = getComponentTypeID<TransformComponent>();
		m_requiredComponent[family] = true;
		family = getComponentTypeID<RendererComponent>();
		m_requiredComponent[family] = true;
	}

	void init() override {
		for (auto& e : m_entityArray) {
			auto& tansformComponent = parentScene->getComponent<TransformComponent>(e);
			std::cout << "id : " << e.GetID() << std::endl;
			std::cout << "xpos : " << tansformComponent.xpos << std::endl;
			std::cout << "ypos : " << tansformComponent.ypos << std::endl;
		}
	}

	void update() override {

	}

	void draw() override {

	}
};
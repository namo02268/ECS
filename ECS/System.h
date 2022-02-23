#pragma once

#include <vector>
#include <bitset>

#include "Entity.h"
#include "ECS_def.h"
#include "Components.h"

class System {
protected:
	std::vector<Entity> m_entityArray;
	std::bitset<MAX_COMPONENTS_FAMILY> m_componentFamily;

public:
	virtual ~System() {}

	virtual void init() {}
	virtual void update() {}
	virtual void draw() {}

	void addEntity(Entity& e) {
		m_entityArray.push_back(e);
	}

	void removeEntity(Entity& e) {
		for (auto itr = m_entityArray.begin(); itr != m_entityArray.end(); ++itr) {
			Entity e_itr = *itr;
			if (e_itr.GetID() == e.GetID()) {
				m_entityArray.erase(itr);
			}
		}
	}
};

class TransformSystem : public System {
public:
	TransformSystem() {
		auto family = getComponentTypeID<TransformComponent>();
		m_componentFamily[family] = true;
	}
};
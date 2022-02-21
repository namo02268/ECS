#pragma once

#include <iostream>
#include <array>
#include <map>

#include "IdGenerator.h"

constexpr unsigned int MAX_COMPONENTS = 32;
constexpr unsigned int MAX_ENTITYS = 32;
using ComponentInstance = unsigned int;
using EntityInstance = unsigned int;

using Entity = EntityID;

class EntityManager {
public:
	Entity create() { return getEntityID(); }
};

class Component {
public:
	virtual void init() {}
	virtual void update() {}
	virtual void draw() {}

	virtual ~Component() {}
};

template<typename ComponentType>
class ComponentManager {
private:
	std::array<std::unique_ptr<ComponentType>, MAX_COMPONENTS> m_componentArray;
	std::map<Entity, ComponentInstance> entityMap;
	ComponentInstance m_newInstance = 1;

public:
	ComponentInstance addComponent(Entity e) {
		ComponentType* c = new ComponentType();
		std::unique_ptr<ComponentType> uPtr(c);
		uPtr->init();
		m_componentArray.at(m_newInstance) = std::move(uPtr);
		entityMap.emplace(e, m_newInstance);
		return m_newInstance++;
	}

	void test() {
		for (const auto& map : entityMap) {
			std::cout << "entity : " << map.first << std::endl;
			std::cout << "component : " << map.second << std::endl;
		}
	}
};


class TrasformComponent : public Component {
public:
	void init() override {
		std::cout << "Transfrom" << std::endl;
	}
};

class ColliderComponent : public Component {
public:
	void init() override {
		std::cout << "Collider" << std::endl;
	}
};

class World {
private:
	template<typename ComponentType>
	ComponentManager<ComponentType> getComponentManager<ComponentType>();
};
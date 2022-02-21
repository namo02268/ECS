#pragma once

#include <iostream>
#include <vector>
#include <array>
#include <map>

#include "IdGenerator.h"

constexpr unsigned int MAX_COMPONENTS_ARRRAY = 64;
constexpr unsigned int MAX_COMPONENTS_FAMILY = 64;
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

class BaseComponentManager {
public:
	virtual ~BaseComponentManager() {}
	virtual void addComponent() {}
};

template<typename ComponentType>
class ComponentManager : public BaseComponentManager {
private:
	std::array<std::unique_ptr<ComponentType>, MAX_COMPONENTS_ARRRAY> m_componentArray;
	std::map<Entity, ComponentInstance> entityMap;
	ComponentInstance m_newInstance = 1;

public:
	void addComponent(Entity e) {
		ComponentType* c = new ComponentType();
		std::unique_ptr<ComponentType> uPtr(c);
		uPtr->init();
		m_componentArray.at(m_newInstance) = std::move(uPtr);
		entityMap.emplace(e, m_newInstance);
		m_newInstance++;
	}

	ComponentType& getComponent(Entity e) {
		ComponentInstance instance = entityMap[e];
		return *m_componentArray[instance];
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
	int xpos = 0;
	int ypos = 0;

public:
	void init() override {
		std::cout << "init Transfrom" << std::endl;
	}
};

class ColliderComponent : public Component {
public:
	bool collider = true;

public:
	void init() override {
		std::cout << "init Collider" << std::endl;
	}
};

class Scene {
private:
	// bit array of component managers ID
	std::bitset<MAX_COMPONENTS_FAMILY> m_componentFamily;
	// array of component managers
	std::vector<std::unique_ptr<BaseComponentManager>> m_componentManagers;

public:
	// TODO : [Add] addComponentFamily function
	template<typename ComponentType>
	void addComponent(Entity e) {
		auto family = getComponentTypeID<ComponentType>();
		// if the component manager already exists
		if (m_componentFamily[family]) {
			static_cast<ComponentManager<ComponentType>&>(*m_componentManagers[family]).addComponent(e);
		}
		else {
			ComponentManager<ComponentType>* m = new ComponentManager<ComponentType>();
			std::unique_ptr<ComponentManager<ComponentType>> uPtr(m);
			m_componentManagers.emplace_back(std::move(uPtr));
			m_componentFamily[family] = true;
			m->addComponent(e);
		}
	}

	// TODO : [Add] error handling
	template<typename ComponentType>
	ComponentType& getComponent(Entity e) {
		auto family = getComponentTypeID<ComponentType>();
		return static_cast<ComponentManager<ComponentType>&>(*m_componentManagers[family]).getComponent(e);
	}

	// TODO : [Add] remove component method
};
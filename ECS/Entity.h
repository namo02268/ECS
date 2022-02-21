#pragma once


#include <iostream>
#include <vector>
#include <array>
#include <bitset>

#include "IdGenerator.h"

class Component;
class Entity;

constexpr size_t maxComponents = 32;
using ComponentBitSet = std::bitset<maxComponents>;
using ComponentArray = std::array<Component*, maxComponents>;

class Component {
public:
	Entity* entity;

	virtual void init() {}
	virtual void update() {}
	virtual void draw() {}

	virtual ~Component() {}
};

template

class Entity {
private:
	bool active = true;
	std::vector<std::unique_ptr<Component>> m_components;
	EntityID m_id;

	ComponentArray componentArray;
	ComponentBitSet componentBitSet;

public:
	Entity() : m_id(getEntityID()) {}

	void update() {
		for (auto& c : m_components) c->update();
	}
	void draw() {
		for (auto& c : m_components) c->draw();
	}

	EntityID getID() { return m_id; }

	bool isActive() const { return active; }
	void destroy() { active = false; }

	template<typename T>
	bool hasComponent() const {
		return componentBitSet[getComponentTypeID<T>()];
	}

	template<typename T, typename... TArgs>
	T& addComponent(TArgs&&... mArgs) {
		T* c = new T(std::forward<TArgs>(mArgs)...);
		c->entity = this;
		std::unique_ptr<Component> uPtr(c);
		m_components.emplace_back(std::move(uPtr));

		componentArray[getComponentTypeID<T>()] = c;
		componentBitSet[getComponentTypeID<T>()] = true;

		c->init();
		return *c;
	}

	template<typename T>
	T& getComponent() {
		auto ptr = componentArray[getComponentTypeID<T>()];
		return *static_cast<T*>(ptr);
	}
};

class EntityManager {
private:
	std::vector<std::unique_ptr<Entity>> entities;

public:
	void update() {
		for (auto& e : entities) e->update();
	}
	void draw() {
		for (auto& e : entities) e->draw();
	}

	Entity& addEntity() {
		Entity* e = new Entity();
		std::unique_ptr<Entity> uPtr(e);
		entities.emplace_back(std::move(uPtr));
		return *e;
	}
};
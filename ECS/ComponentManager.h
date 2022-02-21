#pragma once

#include <iostream>
#include <vector>
#include <array>
#include <bitset>

constexpr size_t MAX_COMPONENTS = 32;
using EntityBitSet = std::bitset<MAX_COMPONENTS>;
using EntityArray = std::array<Entity*, MAX_COMPONENTS>;

class Entity {
public:
	unsigned int m_id = 0;
};

class Component {
public:
	virtual void init() {}
	virtual void update() {}
	virtual void draw() {}

	virtual ~Component() {}
};

template <typename ComponentType>
class ComponentManager {
private:
	std::vector<std::unique_ptr<ComponentType>> componentData;
	EntityArray entityArray;
	EntityBitSet entityBitSet;

public:
	ComponentManager() {};

	ComponentType& addComponent(Entity entity) {

	}


};
#pragma once

#include <bitset>

#include "ECS_def.h"

class Entity {
private:
	EntityID m_id;
public:
	std::bitset<MAX_COMPONENTS_FAMILY> m_componentFamily;

public:
	Entity(EntityID id) : m_id(id) {}
	EntityID GetID() { return m_id; }
};
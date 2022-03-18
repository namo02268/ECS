#pragma once
#include <string>
#include <sstream>
#include <iomanip>
#include "ECS_def.h"

class Entity {
private:
	EntityID m_id;
public:
	std::string name;

public:
	Entity(EntityID id) : m_id(id) {}
	~Entity() = default;
	inline const EntityID GetID() const { return m_id; }
};
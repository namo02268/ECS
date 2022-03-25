#pragma once

#include "ECS/Entity.h"
#include "ECS/IdGenerator.h"

class EntityManager {
public:
	~EntityManager() = default;

	Entity createEntity() { return Entity(getEntityID()); }
	void destroyEnitity(Entity e) {}
};
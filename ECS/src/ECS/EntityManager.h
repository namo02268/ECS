#pragma once

#include "ECS/Entity.h"
#include "ECS/IdGenerator.h"

namespace ECS {
	class EntityManager {
	public:
		~EntityManager() = default;

		// TODO : When the ID is greater than MAX_ENTITIES
		Entity createEntity() { return Entity(getEntityID()); }
		void destroyEnitity(Entity e) {}
	};
}

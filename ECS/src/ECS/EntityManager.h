#pragma once

#include "ECS/Entity.h"
#include "ECS/IdGenerator.h"

namespace ECS {
	class EntityManager {
	public:
		~EntityManager() = default;

		// TODO : When the ID is greater than MAX_ENTITIES
		Entity CreateEntity() { return Entity(GetEntityID()); }
		void DestroyEnitity(Entity e) {}
	};
}

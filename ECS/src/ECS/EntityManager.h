#pragma once

#include "ECS/Entity.h"
#include "ECS/IdGenerator.h"

namespace ECS {
	class EntityManager {
	public:
		EntityManager() = default;
		~EntityManager() = default;

		Entity CreateEntity() {
			return Entity(GetEntityID());
		}

		void DestroyEnitity(Entity e) {}
	};
}

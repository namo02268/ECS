#pragma once
#include <unordered_map>
#include <array>

#include "ECS/Entity.h"
#include "ECS/ECS_def.h"

namespace ECS {
	class EntityMap {
	private:
		std::array<ComponentInstance, MAX_ENTITIES> m_entityToInstance;
		std::array<EntityID, MAX_COMPONENTS> m_instanceToEntity;

	public:
		~EntityMap() = default;

		Entity getEntity(ComponentInstance i) { return m_instanceToEntity[i]; }
		ComponentInstance getInstance(Entity e) { return m_entityToInstance[e.GetID()]; }

		void add(Entity& e, ComponentInstance i) {
			auto id = e.GetID();
			m_entityToInstance[id] = i;
			m_instanceToEntity[i] = id;
		}

		void update(Entity& e, ComponentInstance i) {
			m_entityToInstance[e.GetID()] = i;
			m_instanceToEntity[i] = e.GetID();
		}
	};
}
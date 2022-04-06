#pragma once
#include <unordered_map>
#include <array>

#include "ECS/Entity.h"
#include "ECS/ECS_def.h"

namespace ECS {
	class EntityMap {
	private:
		std::unordered_map<EntityID, ComponentInstance> m_entityToInstance;
		std::array<EntityID, MAX_ENTITIES> m_instanceToEntity;

	public:
		~EntityMap() = default;

		Entity getEntity(ComponentInstance i) { return m_instanceToEntity[i]; }
		ComponentInstance getInstance(Entity e) { return m_entityToInstance[e.GetID()]; }

		void add(Entity& e, ComponentInstance i) {
			m_entityToInstance.insert({ e.GetID(), i });
			m_instanceToEntity[i] = e.GetID();
		}

		void update(Entity& e, ComponentInstance i) {
			m_entityToInstance[e.GetID()] = i;
			m_instanceToEntity[i] = e.GetID();
		}
		void remove(Entity& e) { m_entityToInstance.erase(e.GetID()); }
	};
}
#pragma once
#include <unordered_map>
#include <array>

#include "ECS/Entity.h"
#include "ECS/ECS_def.h"

namespace ECS {
	class EntityComponentMap {
	private:
		ComponentInstanceID m_entityToInstance[MAX_ENTITIES];
		EntityID m_instanceToEntity[MAX_COMPONENTS];

	public:
		~EntityComponentMap() {}

		EntityID getEntity(ComponentInstanceID i) { return m_instanceToEntity[i]; }
		ComponentInstanceID getInstance(EntityID e) { return m_entityToInstance[e]; }

		void add(EntityID e, ComponentInstanceID i) {
			auto id = e;
			m_entityToInstance[id] = i;
			m_instanceToEntity[i] = id;
		}

		void update(EntityID e, ComponentInstanceID i) {
			m_entityToInstance[e] = i;
			m_instanceToEntity[i] = e;
		}
	};
}
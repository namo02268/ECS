#pragma once
#include <unordered_map>
#include <array>

#include "ECS/Entity.h"
#include "ECS/ECS_def.h"

namespace ECS {
	class SparseSet {
	private:
		std::array<ComponentInstance, MAX_ENTITIES> m_sparse;
		std::array<EntityID, MAX_COMPONENTS> m_dense;

	public:
		~SparseSet() = default;

		Entity getEntity(ComponentInstance i) { return m_dense[i]; }
		ComponentInstance getInstance(Entity e) { return m_sparse[e]; }

		void add(Entity& e, ComponentInstance i) {
			auto id = e;
			m_sparse[id] = i;
			m_dense[i] = id;
		}

		void update(Entity& e, ComponentInstance i) {
			m_sparse[e] = i;
			m_dense[i] = e;
		}
	};
}
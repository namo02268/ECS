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

		Entity getEntity(const ComponentInstance i) const { return m_dense[i]; }
		ComponentInstance getInstance(const Entity e) const { return m_sparse[e]; }

		void add(const Entity e, const ComponentInstance i) {
			m_sparse[e] = i;
			m_dense[i] = e;
		}

		void update(const Entity e, const ComponentInstance i) {
			m_sparse[e] = i;
			m_dense[i] = e;
		}
	};
}
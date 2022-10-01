#pragma once
#include <array>

#include "ECS/Entity.h"
#include "ECS/ECS_def.h"

namespace ECS {
	class SparseSet {
	private:
		std::array<ID, MAX_ENTITIES> m_sparse;
		std::array<ID, MAX_COMPONENTS> m_dense;

	public:
		SparseSet() = default;
		~SparseSet() = default;

		EntityID GetEntity(const ComponentInstance i) const { return m_dense[i]; }
		ComponentInstance GetInstance(const EntityID e) const { return m_sparse[e]; }

		void Add(const EntityID e, const ComponentInstance i) {
			m_sparse[e] = i;
			m_dense[i] = e;
		}

		void Update(const EntityID e, const ComponentInstance i) {
			m_sparse[e] = i;
			m_dense[i] = e;
		}
	};
}
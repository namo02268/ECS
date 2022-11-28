#pragma once

#include "ECS/ECS_def.h"

namespace ECS {
	class Archetype {
	private:
		ArcheID m_id = 0;
		ComponentFamily m_family;

	public:
		ArcheID GetID() const { return m_id; }
		ComponentFamily GetFamily() const { return m_family; }

		void AddComponent(const FamilyID family) { m_family.set(family); }
		void RemoveComponent(const FamilyID family) { m_family.reset(family); }
	};
}

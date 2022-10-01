#pragma once
#include "ECS/ECS_def.h"

namespace ECS {
	class Entity {
	private:
		EntityID m_id = INVALID;

	public:
		static const EntityID INVALID = 0;

		Entity(EntityID id) : m_id(id) {}
		virtual ~Entity() = default;

		EntityID GetID() { return this->m_id; }
	};
}

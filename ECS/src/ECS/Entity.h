#pragma once
#include <string>
#include <sstream>
#include <iomanip>
#include "ECS/ECS_def.h"

namespace ECS {
	class Entity {
	private:
		EntityID m_id;
		// child? EntityID m_child;
		// next?  EntityID m_next;

	public:
		Entity(EntityID id) : m_id(id) {}
		~Entity() = default;
		EntityID GetID() { return m_id; }
	};
}

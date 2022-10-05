#pragma once

#include "ECS/ECS_def.h"

namespace ECS {
	class Archetype {
	private:
		ArcheID m_id;

	public:
		ArcheID GetID() const { return m_id; }
	};
}

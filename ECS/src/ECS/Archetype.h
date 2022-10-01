#pragma once

#include <cstddef>
#include <bitset>

#include "ECS/ECS_def.h"

namespace ECS {
	class Archetype {
	private:
		using ArcheID = std::bitset<MAX_COMPONENTS_FAMILY>;
		ArcheID m_id;
	};

}

#pragma once

#include "ECS/ECS_def.h"

namespace ECS {
	class IDGenerator {
	public:
		static EntityID getID() noexcept {
			static EntityID entityID = 1;
			return entityID++;
		}

		template<class T>
		static ComponentTypeID getTypeID() {
			static const ComponentTypeID typeID = getID();
			return typeID | COMPONENT;
		}
	};

}


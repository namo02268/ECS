#pragma once

#include "ECS/ECS_def.h"

namespace ECS {
	inline EntityID getEntityID() {
		static EntityID entityID = 0;
		return entityID++;
	}

	template<class T>
	inline ComponentTypeID getComponentTypeID() {
		static ComponentTypeID typeID = getEntityID();
		return typeID;
	}
}

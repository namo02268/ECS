#pragma once

#include <typeindex>
#include <typeinfo>
#include "ECS/ECS_def.h"

namespace ECS {
	inline EntityID GetEntityID() {
		static EntityID entityID = 1;
		return entityID++;
	}

	inline ComponentTypeID GetComponentTypeID() {
		static ComponentTypeID componentID = 0;
		return componentID++;
	}

	template <typename T> inline ComponentTypeID GetComponentTypeID() noexcept {
		static ComponentTypeID typeID = GetComponentTypeID();
		return typeID;
	}

	inline EventTypeID GetEventTypeID() {
		static EventTypeID eventID = 0;
		return eventID++;
	}

	template <typename T> inline EventTypeID GetEventTypeID() noexcept {
		static EventTypeID typeID = GetEventTypeID();
		return typeID;
	}
}

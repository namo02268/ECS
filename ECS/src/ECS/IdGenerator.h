#pragma once

#include <typeindex>
#include <typeinfo>
#include "ECS/ECS_def.h"

namespace ECS {
	class Family {
	private:
		static inline FamilyID m_identifier = 0;

	public:
		template<typename>
		static inline const FamilyID Type = m_identifier++;
	};

	inline EntityID GetEntityID() {
		static EntityID entityID = 1;
		return entityID++;
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

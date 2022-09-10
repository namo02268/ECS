#pragma once

#include <bitset>
#include <cstdint>

namespace ECS {
	using EntityID = std::int32_t;
	using ComponentTypeID = std::int32_t;
	using ComponentInstance = std::int32_t;
	using EventTypeID = std::int32_t;

	constexpr std::int32_t MAX_ENTITIES = 100000;
	constexpr std::int32_t MAX_COMPONENTS_FAMILY = 32;
	constexpr std::int32_t MAX_COMPONENTS = 100000;

	using ComponentFamily = std::bitset<MAX_COMPONENTS_FAMILY>;
}
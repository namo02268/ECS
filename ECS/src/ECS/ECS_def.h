#pragma once

#include <bitset>
#include <cstdint>

namespace ECS {
	using ID = std::int32_t;
	using EntityID = ID;
	using FamilyID = ID;
	using ComponentInstance = ID;
	using EventTypeID = ID;
	using ArcheID = ID;

	constexpr std::size_t MAX_ENTITIES = 1000;
	constexpr std::size_t MAX_COMPONENTS_FAMILY = 32;
	constexpr std::size_t MAX_COMPONENTS = 1000;

	using ComponentFamily = std::bitset<MAX_COMPONENTS_FAMILY>;
}
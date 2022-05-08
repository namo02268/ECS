#pragma once

#include <bitset>
#include <cstdint>

using EntityID = std::int32_t;
using ComponentTypeID = std::int32_t;
using ComponentInstance = std::int32_t;
using EventTypeID = std::int32_t;

constexpr std::int32_t MAX_ENTITIES = 1100000;
constexpr std::int32_t MAX_COMPONENTS_FAMILY = 32;
constexpr std::int32_t MAX_COMPONENTS = 1100000;

using ComponentFamily = std::bitset<MAX_COMPONENTS_FAMILY>;

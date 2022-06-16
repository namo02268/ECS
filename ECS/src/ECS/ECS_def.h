#pragma once

using EntityID = std::uint32_t;
using ComponentTypeID = EntityID;
using ComponentInstanceID = EntityID;

constexpr EntityID MAX_ENTITIES = (1ull << 16) - 1;
constexpr EntityID MAX_COMPONENTS = MAX_ENTITIES;

constexpr EntityID INSTANCEOF = 1ull << 31;
constexpr EntityID CHILDOF = 1ull << 30;

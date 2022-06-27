#pragma once

using EntityID = std::uint32_t;
using ComponentTypeID = EntityID;
using ComponentInstanceID = EntityID;
using EventTypeID = EntityID;

constexpr EntityID MAX_ENTITIES = (1ull << 16) - 1;
constexpr EntityID MAX_COMPONENTS = MAX_ENTITIES;

constexpr EntityID INSTANCE = 1ull << 31;
constexpr EntityID CHILD = 1ull << 30;

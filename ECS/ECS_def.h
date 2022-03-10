#pragma once

#include <bitset>

constexpr unsigned int MAX_COMPONENTS_FAMILY = 32;
constexpr unsigned int MAX_COMPONENTS_ARRRAY = 128;

using ComponentInstance = unsigned int;
using EntityID = unsigned int;
using ComponentTypeID = unsigned int;
using EventTypeID = unsigned int;
using ComponentFamily = std::bitset<MAX_COMPONENTS_FAMILY>;
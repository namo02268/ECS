#include <iostream>
#include <cstdint>
#include <bitset>

#include <array>
#include <unordered_map>

using EntityID = std::uint64_t;
using ComponentTypeID = EntityID;
using ComponentInstanceID = EntityID;

constexpr EntityID MAX_ENTITY = (1ull << 62) - 1;
constexpr EntityID INSTANCEOF = 1ull << 63;
constexpr EntityID CHILDOF = 1ull << 62;

inline EntityID getEntityID() {
	static EntityID entityID = 0;
	return entityID++;
}

template<typename T>
inline ComponentTypeID getComponentTypeID() {
	static ComponentTypeID typeID = getEntityID();
	return typeID;
}

class A {

};

class B {

};

int main() {
	EntityID Player = getEntityID() | INSTANCEOF;

	// Bit Test
	std::cout << "Bit Test" << std::endl;
	std::cout << MAX_ENTITY << std::endl;
	std::cout << static_cast<std::bitset<64>>(MAX_ENTITY) << std::endl;
	std::cout << static_cast<std::bitset<64>>(INSTANCEOF) << std::endl;
	std::cout << static_cast<std::bitset<64>>(CHILDOF) << std::endl;
	std::cout << static_cast<std::bitset<64>>(Player) << std::endl;
	std::cout << static_cast<std::bitset<64>>(UINT32_MAX) << std::endl;
	std::cout << static_cast<std::bitset<64>>(UINT64_MAX) << std::endl;
	if (Player & INSTANCEOF) {
		std::cout << "INSTANCE" << std::endl;
	}
	std::cout << UINT64_MAX << std::endl;

	// Component Type Test
	EntityID Player1 = getEntityID();
	ComponentTypeID CA = getComponentTypeID<A>();
	ComponentTypeID CB = getComponentTypeID<B>();
	ComponentTypeID CA2 = getComponentTypeID<A>();
	EntityID Player2 = getEntityID();
	EntityID CB2 = getComponentTypeID<B>();

	std::cout << "Component Type Test" << std::endl;
	std::cout << "Player1 : " << Player1 << std::endl;
	std::cout << "CA      : " << CA << std::endl;
	std::cout << "CB      : " << CB << std::endl;
	std::cout << "CA      : " << CA2 << std::endl;
	std::cout << "Player2 : " << Player2 << std::endl;
	std::cout << "CB      : " << CB2 << std::endl;

	return 0;
}
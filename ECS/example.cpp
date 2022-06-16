#include <iostream>

#include "ECS/IdGenerator.h"
#include "ECS/ComponentManager.h"

class A {

};

class B {

};

int main() {
	auto Player = ECS::getEntityID();
	auto ComponentA = ECS::getComponentTypeID<A>();
	auto ComponentB = ECS::getComponentTypeID<B>();

	auto Player2 = ECS::getEntityID();
	std::cout << Player2 << std::endl;
	auto ComponentA2 = ECS::getComponentTypeID<A>();
	std::cout << ComponentA2 << std::endl;

	return 0;
}
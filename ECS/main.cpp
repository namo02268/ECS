#include <iostream>
#include <bitset>

#include "Entity.h"
#include "Components.h"

int main()
{
	EntityManager manager;

	auto& entity = manager.addEntity();
	entity.addComponent<TransformComponent>("test");

	std::cout << entity.hasComponent<TransformComponent>() << std::endl;

}
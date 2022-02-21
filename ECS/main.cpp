#include <iostream>
#include <bitset>

#include "ComponentManager.h"

int main() {

	EntityManager Emanager;
	ComponentManager<TrasformComponent> Tmanager;
	ComponentManager<ColliderComponent> Cmanager;

	auto E1 = Emanager.create();
	auto E2 = Emanager.create();

	Tmanager.addComponent(E1);
	Tmanager.addComponent(E2);

	std::cout << "--------------" << std::endl;

	Cmanager.addComponent(E2);

	std::cout << "--------------" << std::endl;

	Cmanager.test();
	Tmanager.test();
}
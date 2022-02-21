#include <iostream>
#include <bitset>

#include "ComponentManager.h"

int main() {
	EntityManager entityManger;
	Entity e1 = entityManger.create();
	Entity e2 = entityManger.create();

	Scene scene;
	scene.addComponent<TrasformComponent>(e1);
	std::cout << "----------" << std::endl;
	scene.addComponent<TrasformComponent>(e2);
	std::cout << "----------" << std::endl;
	scene.addComponent<ColliderComponent>(e1);

	std::cout << "----------" << std::endl;
	scene.getComponent<TrasformComponent>(e1).xpos = 10;

	std::cout << scene.getComponent<TrasformComponent>(e1).xpos << std::endl;
	std::cout << scene.getComponent<TrasformComponent>(e2).xpos << std::endl;

}
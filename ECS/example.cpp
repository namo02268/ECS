#include <iostream>
#include <bitset>

#include "ECS/Scene.h"
#include "ECS/Component.h"

struct Trans : public ECS::Component {
	Trans(int x, int y) : x(x), y(y) {}
	int x = 0;
	int y = 0;
};

struct B : public ECS::Component {

};

int main() {
	ECS::Scene ecs;
	auto Player = ecs.createEntity();
	auto Player2 = ecs.createEntity();

	ecs.addComponent(Player, Trans(2, 2));
	ecs.addComponent(Player2, Trans(2, 2));

	std::cout << ecs.getComponent<Trans>(Player) << std::endl;
	std::cout << ecs.getComponent<Trans>(Player2) << std::endl;

	ecs.destroyEntity(Player);

	auto Player3 = ecs.createEntity();
	ecs.addComponent(Player3, Trans(2, 2));
	std::cout << ecs.getComponent<Trans>(Player2) << std::endl;
	std::cout << ecs.getComponent<Trans>(Player3) << std::endl;


	return 0;
}
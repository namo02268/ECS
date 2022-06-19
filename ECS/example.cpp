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

	ecs.addComponent(Player2, Trans(2, 2));
	ecs.addComponent(Player, Trans(2, 2));
	ecs.addComponent(Player, B());

	std::cout << ecs.getComponent<Trans>(Player2) << std::endl;
	std::cout << ecs.getComponent<Trans>(Player) << std::endl;

	auto& index = ecs.getEntityIndex(Player);

	for (auto& i : index) {
		std::cout << static_cast<std::bitset<32>>(i) << std::endl;
	}
	auto Player3 = ecs.createEntity();
	ecs.addComponent(Player3, Trans(2, 2));

	ecs.removeComponent<Trans>(Player);
	ecs.destroyEntity(Player);

	return 0;
}
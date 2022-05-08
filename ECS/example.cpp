#include <iostream>
#include <bitset>

#include "ECS/Scene.h"
#include "Components/Components.h"
#include "Systems/Systems.h"
#include "ECS/EventHandler.h"

using namespace ECS;

auto entityManager = std::make_unique<EntityManager>();
auto eventHandler = std::make_unique<EventHandler>();
Scene scene(std::move(entityManager), std::move(eventHandler));


class Player {
public:
	TransformComponent trans;
	PhysicComponent physic;
	ColliderComponent collision;
	RendererComponent render;
};

std::vector<Entity> entityArray;
std::vector<Player> playerArray;

void testOOP(float dt) {
	float sum = 0.0f;

	for (auto& p : playerArray) {
		sum += p.trans.x + p.physic.vx * dt + p.physic.ax * dt * dt;
	}
	std::cout << sum << std::endl;
}

void testDOP(float dt) {
	float sum = 0.0f;
	for (auto& e : entityArray) {
		auto trans = scene.getComponent<TransformComponent>(e);
		auto physic = scene.getComponent<PhysicComponent>(e);
		sum += trans->x + physic->vx * dt + physic->ax * dt * dt;
	}
	std::cout << sum << std::endl;
}

int main() {
	int entitySize = 1000000;
	entityArray.reserve(entitySize);
	float dt = 0.1f;

	for (int i = 0; i < entitySize; ++i) {
		auto entity = scene.createEntity();
		scene.addComponent(entity, TransformComponent(1.0f, 1.0f));
		scene.addComponent(entity, PhysicComponent(1.0f, 1.0f, 1.0f, 1.0f));
		entityArray.push_back(entity);
	}

	playerArray.reserve(entitySize);

	for (int i = 0; i < entitySize; ++i) {
		auto p = Player();
		playerArray.push_back(p);
	}

	testDOP(dt);

	testOOP(dt);

	/*
	auto tSystem = std::make_unique<TransformSystem>();
	scene.addSystem(std::move(tSystem));

	auto combatSystem = std::make_unique<CombatSystem>();
	scene.addSystem(std::move(combatSystem));
	auto physicsSystem = std::make_unique<PhysicsSystem>();
	scene.addSystem(std::move(physicsSystem));

	auto e1 = scene.createEntity();
	auto e2 = scene.createEntity();
	auto e3 = scene.createEntity();

	scene.addComponent(e1, RendererComponent());
	scene.addComponent(e1, TransformComponent(10, 10));
	scene.addComponent(e2, RendererComponent());
	scene.addComponent(e3, RendererComponent());
	scene.addComponent(e3, TransformComponent(300, 30));

	scene.iterateAll<TransformComponent>([](TransformComponent* c) {
		c->xpos += c->ypos;
		}
	);
	scene.init();
	scene.update(1.0);
	*/
}


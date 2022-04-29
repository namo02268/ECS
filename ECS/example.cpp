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

std::vector<Entity> entityArray;

void testIterateAll(float dt) {
	float sum = 0.0f;
	scene.iterateAll<PhysicComponent>([&](PhysicComponent* c) {
			sum += c->position + c->velocity * dt + c->acceleration * dt * dt;
		}
	);
	std::cout << sum << std::endl;
}

void testGet(float dt) {
	float sum = 0.0f;
	for (auto& e : entityArray) {
		auto c = scene.getComponent<PhysicComponent>(e);
		sum += c->position + c->velocity * dt + c->acceleration * dt * dt;
	}
	std::cout << sum << std::endl;
}

int main() {
	int entitySize = 1000000;
	entityArray.reserve(entitySize);

	for (int i = 0; i < entitySize; ++i) {
		auto entity = scene.createEntity();
		scene.addComponent<PhysicComponent>(entity, PhysicComponent());
		entityArray.push_back(entity);
	}

	testIterateAll(0.1f);

	testGet(0.1f);

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

	scene.addComponent<RendererComponent>(e1, RendererComponent());
	scene.addComponent<TransformComponent>(e1, TransformComponent(10, 10));
	scene.addComponent<RendererComponent>(e2, RendererComponent());
	scene.addComponent<RendererComponent>(e3, RendererComponent());
	scene.addComponent<TransformComponent>(e3, TransformComponent(300, 30));

	scene.iterateAll<TransformComponent>([](TransformComponent* c) {
		c->xpos += c->ypos;
		}
	);
	scene.init();
	scene.update(1.0);
	*/
}


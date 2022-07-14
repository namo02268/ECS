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

const int N = 1000000;

struct Position {
	float x = 1.0f;
	float y = 1.0f;
	float z = 1.0f;
};

struct Vertex {
	float vertex[64];
};

class ECSPosition : public Component {
public:
	float x = 1.0f;
	float y = 1.0f;
	float z = 1.0f;
};

class ECSVertex : public Component {
	float vertex[64];
};

std::vector<Entity> entityArray;


struct SphereAoS {
	Position position;
	Vertex vert;
};

SphereAoS sphereAoS[N];

struct SphereSoA {
	Position position[N];
	Vertex vert[N];
};

SphereSoA sphereSoA;

void testAoS() {
	float sum = 0;
	for (int i = 0; i < N; i++) {
		sum += sphereAoS[i].position.x * sphereAoS[i].position.y * sphereAoS[i].position.z / 100;
	}
	std::cout << sum << std::endl;
}

void testSoA() {
	float sum = 0;
	for (int i = 0; i < N; i++) {
		sum += sphereSoA.position[i].x * sphereSoA.position[i].y * sphereSoA.position[i].z / 100;
	}
	std::cout << sum << std::endl;
}

void testECS() {
	float sum = 0;
	for (auto& e : entityArray) {
		auto pos = scene.getComponent<ECSPosition>(e);
		sum += pos->x * pos->y * pos->z / 100;
	}
	std::cout << sum << std::endl;
}

void testIterateAll() {
	float sum = 0;
	scene.iterateAll<ECSPosition>([&](ECSPosition* c) {
		sum += c->x * c->y * c->z / 100;
		});
	std::cout << sum << std::endl;
}

int main() {
	entityArray.reserve(N);
	for (int i = 0; i < N; ++i) {
		auto entity = scene.createEntity();
		scene.addComponent(entity, ECSPosition());
		scene.addComponent(entity, ECSVertex());
		entityArray.push_back(entity);
	}

	testAoS();
	testSoA();
	testECS();
	testIterateAll();



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


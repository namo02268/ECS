#include <iostream>

#include "ECS/ECS.h"
#include "Components/Transform.h"
#include "Components/Relationship.h"

#include "Systems/Systems.h"
#include "ECS/EventHandler.h"

#include "ECS/Pool.h"

struct Position {
	Position(float x, float y, float z) : x(x), y(x), z(z) { std::cout << "This is Construct" << std::endl; }
	~Position() { std::cout << "This is Destruct" << std::endl; }
	float x = 0;
	float y = 0;
	float z = 0;
};

int main() {
	ECS::ComponentManager<Position> manager;
	manager.AddComponent(0, 0, 0);

	/*
	Pool<Position, 1024> pool;
	std::cout << "------------Total Size Test------------" << std::endl;
	std::cout << pool.GetTotalSize() << std::endl;

	std::cout << "------------Add Test------------" << std::endl;
	std::cout << pool.Add(1, 1, 1) << std::endl;
	std::cout << pool.Add(2, 2, 2) << std::endl;
	std::cout << pool.Add(3, 3, 3) << std::endl;
	std::cout << pool.Add(4, 4, 4) << std::endl;
	std::cout << pool.Get(2)->x << std::endl;

	std::cout << "------------Remove Test------------" << std::endl;
	pool.Remove(0);
	std::cout << pool.Get(0)->x << std::endl;
	std::cout << pool.Get(1)->x << std::endl;
	std::cout << pool.Get(2)->x << std::endl;
	*/
}


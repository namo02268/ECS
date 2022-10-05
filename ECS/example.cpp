#include <iostream>

#include "ECS/ECS.h"
#include "ECS/Pool.h"
#include "ECS/SparseSet.h"

struct Position {
	Position(float x, float y, float z) : x(x), y(x), z(z) { std::cout << "This is Construct" << std::endl; }
	~Position() { std::cout << "This is Destruct" << std::endl; }
	float x = 0;
	float y = 0;
	float z = 0;
};

int main() {
	ECS::EntityManager e_manager;
	ECS::ComponentManager<Position> c_manager;

	auto entity1 = e_manager.CreateEntity();
	auto entity2 = e_manager.CreateEntity();
	auto entity3 = e_manager.CreateEntity();
	auto entity4 = e_manager.CreateEntity();
	std::cout << entity1.GetID() << std::endl;
	std::cout << entity2.GetID() << std::endl;
	std::cout << entity3.GetID() << std::endl;
	std::cout << entity4.GetID() << std::endl;

	std::cout << "------------Add Test------------" << std::endl;
	c_manager.Add(entity1.GetID(), 1, 1, 1);
	c_manager.Add(entity2.GetID(), 2, 2, 2);
	c_manager.Add(entity3.GetID(), 3, 3, 3);
	c_manager.Add(entity4.GetID(), 4, 4, 4);

	std::cout << "------------Get Test------------" << std::endl;
	std::cout << c_manager.Get(entity1.GetID())->x << std::endl;
	std::cout << c_manager.Get(entity2.GetID())->x << std::endl;
	std::cout << c_manager.Get(entity3.GetID())->x << std::endl;
	std::cout << c_manager.Get(entity4.GetID())->x << std::endl;

	std::cout << "------------Remove Test------------" << std::endl;
	c_manager.Remove(entity2.GetID());
	c_manager.Add(entity2.GetID(), 5, 5, 5);
	std::cout << c_manager.Get(entity1.GetID())->x << std::endl;
	std::cout << c_manager.Get(entity2.GetID())->x << std::endl;
	std::cout << c_manager.Get(entity3.GetID())->x << std::endl;
	std::cout << c_manager.Get(entity4.GetID())->x << std::endl;
}


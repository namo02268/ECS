#pragma once

#include <array>
#include <map>

#include "Entity.h"

constexpr unsigned int MAX_COMPONENTS_ARRRAY = 64;
constexpr unsigned int MAX_COMPONENTS_FAMILY = 64;
constexpr unsigned int MAX_ENTITYS = 32;
using ComponentInstance = unsigned int;
using EntityInstance = unsigned int;

class BaseComponentManager {
public:
	virtual ~BaseComponentManager() {}
	virtual void addComponent() {}
};

template<typename ComponentType>
class ComponentManager : public BaseComponentManager {
private:
	std::array<std::unique_ptr<ComponentType>, MAX_COMPONENTS_ARRRAY> m_componentArray;
	std::map<Entity, ComponentInstance> entityMap;
	ComponentInstance m_newInstance = 1;

public:
	void addComponent(Entity e) {
		ComponentType* c = new ComponentType();
		std::unique_ptr<ComponentType> uPtr(c);
		uPtr->init();
		m_componentArray.at(m_newInstance) = std::move(uPtr);
		entityMap.emplace(e, m_newInstance);
		m_newInstance++;
	}

	ComponentType& getComponent(Entity e) {
		ComponentInstance instance = entityMap[e];
		return *m_componentArray[instance];
	}

	void test() {
		for (const auto& map : entityMap) {
			std::cout << "entity : " << map.first << std::endl;
			std::cout << "component : " << map.second << std::endl;
		}
	}
};

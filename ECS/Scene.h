#pragma once

#include <bitset>
#include <vector>
#include "ComponentManager.h"
#include "EntityManager.h"
#include "EntityHandle.h"

class EntityHandle;

class Scene {
private:
	// entity manager
	std::unique_ptr<EntityManager> m_entityManager;
	// bit array of component managers ID
	std::bitset<MAX_COMPONENTS_FAMILY> m_componentFamily;
	// array of component managers
	std::vector<std::unique_ptr<BaseComponentManager>> m_componentManagers;

public:
	// constructor
	explicit Scene(std::unique_ptr<EntityManager> entityManager) 
		: m_entityManager(std::move(entityManager)) {};

	EntityHandle createEntity() { return { m_entityManager->createEntity(), this }; }

	// TODO : [Add] addComponentFamily function
	template<typename ComponentType>
	void addComponent(Entity& e) {
		auto family = getComponentTypeID<ComponentType>();
		// if the component manager already exists
		if (m_componentFamily[family]) {
			static_cast<ComponentManager<ComponentType>&>(*m_componentManagers[family]).addComponent(e);
		}
		else {
			ComponentManager<ComponentType>* m = new ComponentManager<ComponentType>();
			std::unique_ptr<ComponentManager<ComponentType>> uPtr(m);
			m_componentManagers.emplace_back(std::move(uPtr));
			m_componentFamily[family] = true;
			m->addComponent(e);
		}
	}

	// TODO : [Add] error handling
	template<typename ComponentType>
	ComponentType& getComponent(Entity e) {
		auto family = getComponentTypeID<ComponentType>();
		return static_cast<ComponentManager<ComponentType>&>(*m_componentManagers[family]).getComponent(e);
	}

	// TODO : [Add] remove component method
};
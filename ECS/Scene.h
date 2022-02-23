#pragma once

#include <iostream>
#include <bitset>
#include <vector>
#include "ComponentManager.h"
#include "EntityManager.h"
#include "ECS_def.h"

class Scene {
private:
	// entity manager
	std::unique_ptr<EntityManager> m_entityManager;
	// entity mask
	std::map<Entity, std::bitset<MAX_COMPONENTS_FAMILY>> entityMasks;
	// bit array of component managers ID
	std::bitset<MAX_COMPONENTS_FAMILY> m_componentFamily;
	// array of component managers
	std::vector<std::unique_ptr<BaseComponentManager>> m_componentManagers;

public:
	// constructor
	explicit Scene(std::unique_ptr<EntityManager> entityManager) 
		: m_entityManager(std::move(entityManager)) {};

	// create the entity
	Entity createEntity() { return m_entityManager->createEntity(); }

	// TODO : [Add] addComponentFamily function
	template<typename ComponentType>
	void addComponent(const Entity& e) {
		auto family = getComponentTypeID<ComponentType>();
		// if the component manager already exists
		if (m_componentFamily[family]) {
			static_cast<ComponentManager<ComponentType>&>(*m_componentManagers[family]).addComponent(e);
		}
		else {
			auto m = std::make_unique<ComponentManager<ComponentType>>();
			m->addComponent(e);
			m_componentManagers.emplace_back(std::move(m));
			m_componentFamily[family] = true;
		}
	}

	template<typename ComponentType>
	void removeComponent(const Entity& e) {
		auto family = getComponentTypeID<ComponentType>();
		static_cast<ComponentManager<ComponentType>&>(*m_componentManagers[family]).removeComponent(e);
	}

	// TODO : [Add] error handling
	template<typename ComponentType>
	ComponentType& getComponent(const Entity& e) {
		auto family = getComponentTypeID<ComponentType>();
		return static_cast<ComponentManager<ComponentType>&>(*m_componentManagers[family]).getComponent(e);
	}

	// TODO : [Add] remove component method
};

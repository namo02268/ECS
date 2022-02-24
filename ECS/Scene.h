#pragma once

#include <iostream>
#include <vector>
#include "ComponentManager.h"
#include "EntityManager.h"
#include "ECS_def.h"
#include "System.h"

class Scene {
private:
	// entity manager
	std::unique_ptr<EntityManager> m_entityManager;
	// entity mask
	std::map<Entity, std::bitset<MAX_COMPONENTS_FAMILY>> entityMasks;
	// bit array of component managers ID
	ComponentFamily m_componentFamily;
	// array of component managers
	std::vector<std::unique_ptr<BaseComponentManager>> m_componentManagers;
	// systems
	std::vector<std::unique_ptr<System>> systems;

public:
	// constructor
	explicit Scene(std::unique_ptr<EntityManager> entityManager) 
		: m_entityManager(std::move(entityManager)) {};

	// create the entity
	Entity createEntity() { return m_entityManager->createEntity(); }

	void addSystem(std::unique_ptr<System> system) {
		system->parentScene = this;
		systems.push_back(std::move(system));
	}

	void init() {
		for (auto& system : systems)
			system->init();
	}

	// TODO : [Add] addComponentFamily function
	template<typename ComponentType>
	void addComponent(Entity& e) {
		auto family = getComponentTypeID<ComponentType>();
		e.m_componentMap[family] = true;

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

		updateComponentMap(e, family);
	}

	template<typename ComponentType>
	void removeComponent(Entity& e) {
		auto family = getComponentTypeID<ComponentType>();
		e.m_componentMap[family] = false;
		static_cast<ComponentManager<ComponentType>&>(*m_componentManagers[family]).removeComponent(e);
		updateComponentMap(e, family);
	}

	// TODO : [Add] error handling
	template<typename ComponentType>
	ComponentType& getComponent(const Entity& e) {
		auto family = getComponentTypeID<ComponentType>();
		return static_cast<ComponentManager<ComponentType>&>(*m_componentManagers[family]).getComponent(e);
	}

	void updateComponentMap(Entity& e, ComponentTypeID family) {
		for (auto& system : systems) {
			auto componentMap = e.m_componentMap;
			auto requiredComponent = system->m_requiredComponent;
			if (requiredComponent[family]) {
				auto andbit = requiredComponent & componentMap;
				if (andbit == system->m_requiredComponent) {
					system->addEntity(e);
				}
				else {
					system->removeEntity(e);
				}

			}
		}
	}
};

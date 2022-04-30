#pragma once

#include <iostream>
#include <vector>

#include "ECS/ComponentManager.h"
#include "ECS/EntityManager.h"
#include "ECS/ECS_def.h"
#include "ECS/System.h"
#include "ECS/EventHandler.h"

namespace ECS
{
	class Scene {
	private:
		// entity manager
		std::unique_ptr<EntityManager> m_entityManager;
		// entity array
		std::vector<Entity> m_allEntityArray;
		// event handler
		std::unique_ptr<EventHandler> m_eventHandler;
		// ComponentMask
		std::array<ComponentFamily, MAX_ENTITIES> m_componentMask;
		// bit array of component managers ID
		ComponentFamily m_componentFamily;
		// array of component managers
		std::array<std::unique_ptr<BaseComponentManager>, MAX_COMPONENTS_FAMILY> m_componentManagers;
		// systems
		std::vector<std::unique_ptr<System>> m_systems;

	public:
		Scene(std::unique_ptr<EntityManager> entityManager, std::unique_ptr<EventHandler> eventHandler)
			: m_entityManager(std::move(entityManager)), m_eventHandler(std::move(eventHandler)) {};
		Scene(const Scene&) = delete;
		Scene& operator=(const Scene&) = delete;
		~Scene() = default;

		//---------------------------------------------Entity---------------------------------------------//
		Entity createEntity() {
			Entity e = m_entityManager->createEntity();
			m_allEntityArray.emplace_back(e);
			return e;
		}

		void destroyEntity(Entity e) {
			for (auto itr = m_allEntityArray.begin(); itr != m_allEntityArray.end(); ++itr) {
				Entity e_itr = *itr;
				if (e_itr.GetID() == e.GetID()) {
					m_allEntityArray.erase(itr);
					return;
				}
			}

			for (auto& system : m_systems) {
				system->removeEntity(e);
			}
			m_entityManager->destroyEnitity(e);
		}

		std::vector<Entity>& getAllEntityArray() {
			return m_allEntityArray;
		}

		//---------------------------------------------System---------------------------------------------//
		void addSystem(std::unique_ptr<System> system) {
			system->m_parentScene = this;
			system->m_eventHandler = m_eventHandler.get();
			m_systems.push_back(std::move(system));
		}

		void init() {
			for (const auto& system : m_systems)
				system->init();
		}

		void update(float dt) {
			for (const auto& system : m_systems)
				system->update(dt);
		}

		void draw() {
			for (const auto& system : m_systems)
				system->draw();
		}

	//---------------------------------------------Component---------------------------------------------//
	template<typename ComponentType>
	void addComponent(Entity& e, ComponentType&& c) {
		auto family = getComponentTypeID<ComponentType>();
		auto id = e.GetID();
		if (!m_componentMask[id][family]) {
			m_componentMask[id][family] = true;
			// if the component manager didn't exists
			if (!m_componentFamily[family]) {
				m_componentManagers[family] = std::make_unique<ComponentManager<ComponentType>>();
				m_componentFamily[family] = true;
			}

			static_cast<ComponentManager<ComponentType>&>(*m_componentManagers[family]).addComponent(e, std::forward<ComponentType>(c));
			updateComponentMap(e, family);
		}
		else {
			std::cout << typeid(ComponentType).name() << " is already attached! Entity ID:" << id << std::endl;
		}
	}

	template<typename ComponentType>
	void removeComponent(const Entity& e) {
		auto family = getComponentTypeID<ComponentType>();
		if (m_componentMask[e.GetID()][family]) {
			m_componentMask[e.GetID()][family] = false;
			static_cast<ComponentManager<ComponentType>&>(*m_componentManagers[family]).removeComponent(e);
			updateComponentMap(e, family);
		}
		else {
			std::cout << typeid(ComponentType).name() << " does not exist! Entity ID:" << e.GetID() << std::endl;
		}
	}

	template<typename ComponentType>
	ComponentType* getComponent(const Entity& e) {
		auto family = getComponentTypeID<ComponentType>();
		return static_cast<ComponentManager<ComponentType>&>(*m_componentManagers[family]).getComponent(e);
	}

	template<typename ComponentType>
	void iterateAll(const std::function<void(ComponentType* c)> lambda) {
		auto family = getComponentTypeID<ComponentType>();
		static_cast<ComponentManager<ComponentType>&>(*m_componentManagers[family]).iterateAll(lambda);
	}

	ComponentFamily getComponentMask(Entity& e) {
		return m_componentMask[e.GetID()];
	}

	private:
		void updateComponentMap(Entity& e, ComponentTypeID family) {
			for (const auto& system : m_systems) {
				auto& componentMap = m_componentMask[e.GetID()];
				auto requiredComponent = system->m_requiredComponent;
				if (requiredComponent[family]) {
					if ((requiredComponent & componentMap) == system->m_requiredComponent)
						system->addEntity(e);
					else
						system->removeEntity(e);
				}
			}
		}
	};
}

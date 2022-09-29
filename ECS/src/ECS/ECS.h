#pragma once

#include <iostream>
#include <vector>

#include "ECS/ComponentManager.h"
#include "ECS/EntityManager.h"
#include "ECS/ECS_def.h"
#include "ECS/System.h"
#include "ECS/EventHandler.h"

#include "Components/Relationship.h"

namespace ECS
{
	class ECS {
	private:
		// entity manager
		std::unique_ptr<EntityManager> m_entityManager = std::make_unique<EntityManager>();
		// array of component managers
		std::array<std::unique_ptr<IComponentManager>, MAX_COMPONENTS_FAMILY> m_componentManagers;
		// event handler
		std::unique_ptr<EventHandler> m_eventHandler;

		// entity array
		std::vector<Entity> m_allEntityArray;
		// ComponentMask
		std::array<ComponentFamily, MAX_ENTITIES> m_componentMask;
		// bit array of component managers ID
		ComponentFamily m_componentFamily;
		// systems
		std::vector<std::unique_ptr<System>> m_systems;

	public:
		ECS() {
			m_eventHandler = std::make_unique<EventHandler>();
		};

		ECS(const ECS&) = delete;
		ECS& operator=(const ECS&) = delete;
		~ECS() = default;

		//---------------------------------------------Entity---------------------------------------------//
		Entity CreateEntity() {
			Entity e = m_entityManager->CreateEntity();
			m_allEntityArray.emplace_back(e);
			AddComponent<Relationship>(e, Relationship());
			return e;
		}

		void DestroyEntity(Entity e) {
			auto id = e;
			auto& mask = m_componentMask[id];

			for (int i = 0; i < MAX_COMPONENTS_FAMILY; i++) {
				if (mask[i]) {
					m_componentManagers[i]->OnDestroyEntity(e);
				}
			}

			for (auto itr = m_allEntityArray.begin(); itr != m_allEntityArray.end(); ++itr) {
				Entity e_itr = *itr;
				if (e_itr == e) {
					m_allEntityArray.erase(itr);
					return;
				}
			}

			for (auto& system : m_systems) {
				system->RemoveEntity(e);
			}
			m_entityManager->DestroyEnitity(e);
		}

		std::vector<Entity>& GetAllEntityArray() {
			return m_allEntityArray;
		}

		//---------------------------------------------System---------------------------------------------//
		void AddSystem(std::unique_ptr<System> system) {
			system->m_parentScene = this;
			system->m_eventHandler = m_eventHandler.get();
			m_systems.push_back(std::move(system));
		}

		void Init() {
			for (const auto& system : m_systems)
				system->Init();
		}

		void Update(float dt) {
			for (const auto& system : m_systems)
				system->Update(dt);
		}

		void Draw() {
			for (const auto& system : m_systems)
				system->Draw();
		}

		//---------------------------------------------Component---------------------------------------------//
		template<typename ComponentType>
		void AddComponent(Entity& e, ComponentType&& c) {
			auto family = GetComponentTypeID<ComponentType>();
			auto id = e;
			if (!m_componentMask[id][family]) {
				m_componentMask[id][family] = true;
				// if the component manager didn't exists
				if (!m_componentFamily[family]) {
					m_componentManagers[family] = std::make_unique<ComponentManager<ComponentType>>();
					m_componentFamily[family] = true;
				}

				static_cast<ComponentManager<ComponentType>&>(*m_componentManagers[family]).AddComponent(e, std::forward<ComponentType>(c));
				UpdateComponentMask(e, family);
			}
			else {
				std::cout << typeid(ComponentType).name() << " is already attached! Entity ID:" << id << std::endl;
			}
		}

		template<typename ComponentType>
		void RemoveComponent(Entity& e) {
			auto family = GetComponentTypeID<ComponentType>();
			if (m_componentMask[e][family]) {
				m_componentMask[e].reset(family);
				static_cast<ComponentManager<ComponentType>&>(*m_componentManagers[family]).RemoveComponent(e);
				UpdateComponentMask(e, family);
			}
			else {
				std::cout << typeid(ComponentType).name() << " does not exist! Entity ID:" << e << std::endl;
			}
		}

		template<typename ComponentType>
		ComponentType* GetComponent(const Entity& e) {
			auto family = GetComponentTypeID<ComponentType>();
			return static_cast<ComponentManager<ComponentType>&>(*m_componentManagers[family]).GetComponent(e);
		}

		template<typename ComponentType>
		void IterateAll(const std::function<void(ComponentType* c)> lambda) {
			auto family = GetComponentTypeID<ComponentType>();
			static_cast<ComponentManager<ComponentType>&>(*m_componentManagers[family]).IterateAll(lambda);
		}

		ComponentFamily GetComponentMask(Entity& e) {
			return m_componentMask[e];
		}

	private:
		void UpdateComponentMask(Entity& e, ComponentTypeID family) {
			for (const auto& system : m_systems) {
				auto& mask = m_componentMask[e];
				auto requiredComponent = system->m_requiredComponent;
				if (requiredComponent[family]) {
					if ((requiredComponent & mask) == system->m_requiredComponent)
						system->AddEntity(e);
					else
						system->RemoveEntity(e);
				}
			}
		}
	};
}

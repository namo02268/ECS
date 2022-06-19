#pragma once

#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>

#include "ECS/ComponentManager.h"
#include "ECS/EntityManager.h"
#include "ECS/ECS_def.h"
#include "ECS/System.h"

namespace ECS
{
	class Scene {
	private:
		// entity manager
		std::unique_ptr<EntityManager> m_entityManager;
		// entity index
		std::unordered_map<EntityID, std::vector<ComponentTypeID>> m_entityIndex;
		// component managers
		std::unordered_map<ComponentTypeID, std::unique_ptr<IComponentManager>> m_componentManagers;

	public:
		Scene() {
			m_entityManager = std::make_unique<EntityManager>();
		}
		Scene(const Scene&) = delete;
		Scene& operator=(const Scene&) = delete;
		~Scene() = default;

		//---------------------------------------------Entity---------------------------------------------//
		Entity createEntity() {
			Entity e = m_entityManager->createEntity();
			std::vector<ComponentTypeID> type;
			m_entityIndex.emplace(e, type);
			return e;
		}

		void destroyEntity(Entity e) {
			for (auto& type : m_entityIndex[e]) {
				if (type & COMPONENT) {
					std::cout << type << std::endl;
				}
			}
			m_entityIndex.erase(e);
			m_entityManager->destroyEnitity(e);
		}

		std::vector<ComponentTypeID>& getEntityIndex(Entity e) {
			return m_entityIndex[e];
		}

		//---------------------------------------------Component---------------------------------------------//
		template<class ComponentType>
		void addComponent(Entity e, ComponentType&& c) {
			auto type = IDGenerator::getTypeID<ComponentType>();
			m_componentManagers.try_emplace(type, std::make_unique<ComponentManager<ComponentType>>());

			if (!hasComponent<ComponentType>(e)) {
				static_cast<ComponentManager<ComponentType>&>(*m_componentManagers[type]).addComponent(e, std::forward<ComponentType>(c));
				m_entityIndex[e].push_back(type);
			}
			else {
				std::cout << typeid(ComponentType).name() << " is already attached! Entity ID:" << e << std::endl;
			}
		}

		template<class ComponentType>
		bool hasComponent(Entity e) {
			auto& type = m_entityIndex[e];
			for (auto c : type) {
				if (c == IDGenerator::getTypeID<ComponentType>())
					return true;
			}
			return false;
		}

		template<class ComponentType>
		ComponentType* getComponent(Entity e) {
			auto type = IDGenerator::getTypeID<ComponentType>();
			return static_cast<ComponentManager<ComponentType>&>(*m_componentManagers[type]).getComponent(e);
		}

		template<class ComponentType>
		void removeComponent(Entity e) {
			auto type = IDGenerator::getTypeID<ComponentType>();
			if (hasComponent<ComponentType>(e)) {
				static_cast<ComponentManager<ComponentType>&>(*m_componentManagers[type]).removeComponent(e);
				auto& index = m_entityIndex[e];
				index.erase(std::remove(index.begin(), index.end(), type), index.end());
			}
		}
	};
}

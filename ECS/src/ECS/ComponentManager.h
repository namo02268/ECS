#pragma once

#include <functional>
#include <unordered_map>

#include "ECS/SparseSet.h"
#include "ECS/Pool.h"
#include "ECS/ECS_def.h"

namespace ECS {
	class IComponentManager {
	public:
		virtual ~IComponentManager() {}
		virtual void OnDestroyEntity(EntityID e) = 0;
	};

	template<typename ComponentType>
	class ComponentManager : public IComponentManager {
	private:
		Pool<ComponentType, MAX_COMPONENTS> m_pool;
		SparseSet<ID> m_sparseSet{ MAX_ENTITIES, MAX_COMPONENTS };
		std::size_t m_size = 0;
		std::unordered_map<ArcheID, void*> m_archMap;

	public:
		ComponentManager() = default;
		ComponentManager(const ComponentManager&) = delete;
		ComponentManager& operator = (const ComponentManager&) = delete;
		~ComponentManager() {
			for (int i = 0; i < m_size; ++i)
				m_pool.Destroy(i);
		}

		struct Component_Iterator {
		public:
			using iterator_category = std::random_access_iterator_tag;
			using difference_type = std::ptrdiff_t;
			using value_type = ComponentType;
			using pointer = ComponentType*;
			using reference = ComponentType&;

			Component_Iterator(pointer ptr) : m_ptr(ptr) {}

			reference operator*() const { return *m_ptr; }
			pointer operator->() { return m_ptr; }

			auto operator++() { m_ptr++; return *this; }
			auto operator++(int) { auto tmp = *this; ++(*this); return tmp; }
			auto operator--() { m_ptr--; return *this; }
			auto operator--(int) { auto tmp = *this; --(*this); return tmp; }

			auto operator+=(const difference_type offset) { m_ptr += offset; return *this; }
			auto operator+(const difference_type offset) const { auto tmp = *this; return tmp += offset; }
			auto operator-=(const difference_type offset) { return *this += -offset; }
			auto operator-(const difference_type offset)const { auto tmp = *this; return tmp -= offset; }
			auto operator-(const Component_Iterator& right) const { return m_ptr - right.m_ptr; }

			auto operator[](const difference_type offset) const { return *(*this + offset); }

			bool operator<(const Component_Iterator& right) const { return m_ptr < right.m_ptr; }
			bool operator>(const Component_Iterator& right) const { return right < *this; }
			bool operator<=(const Component_Iterator& right) const { return !(right < *this); }
			bool operator>=(const Component_Iterator& right) const { return !(*this < right); }

			friend bool operator==(const Component_Iterator& a, const Component_Iterator& b) { return a.m_ptr == b.m_ptr; }
			friend bool operator!=(const Component_Iterator& a, const Component_Iterator& b) { return a.m_ptr != b.m_ptr; }
		private:
			pointer m_ptr;
		};

		Component_Iterator begin() { return Component_Iterator(m_pool.Get(0)); }
		Component_Iterator end() { return Component_Iterator(m_pool.Get(m_size)); }

		template<typename ... Args>
		ComponentType* Add(EntityID e, Args && ... args) {
			auto ptr = m_pool.Get(m_size);
			::new(ptr) ComponentType(std::forward<Args>(args) ...);
			m_sparseSet.Insert(e, m_size);
			m_size++;
			return ptr;
		}

		void SetArchType(EntityID e) {

		}

		ComponentType* Get(EntityID e) {
			assert(m_size > m_sparseSet.GetDense(e) && "n must be smaller than current size");
			return m_pool.Get(m_sparseSet.GetDense(e));
		}

		void Remove(EntityID e) {
			auto instance = m_sparseSet.GetDense(e);
			auto lastInstance = m_size - 1;
			auto lastEntityID = m_sparseSet.GetSparse(lastInstance);

			assert(m_size > instance && "n must be smaller than current size");

			m_pool.Destroy(e);

			if (instance != lastInstance) {
				this->Move(lastInstance, instance);
				m_sparseSet.Insert(lastEntityID, instance);
			}
			m_size--;
		}

		void OnDestroyEntity(EntityID e) override {
			Remove(e);
		}

		void IterateAll(const std::function<void(ComponentType* c)> lambda) {
		}

	private:
		void Move(std::size_t from, std::size_t to) {
			*(m_pool.Get(to)) = *(m_pool.Get(from));
		}
	};
}

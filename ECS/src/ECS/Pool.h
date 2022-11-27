#pragma once

#include <cstddef>
#include <cassert>
#include <stdint.h>
#include <stdlib.h>

#include <iterator>

namespace ECS {
	template<typename T, std::size_t chunkSize = 1024>
	class Pool {
	protected:
		void* m_ptr = nullptr;
		std::size_t m_chunkSize;
		std::size_t m_elementSize;
		std::size_t m_totalSize;
		std::size_t m_size;

	public:
		Pool() : m_elementSize(sizeof(T)), m_chunkSize(chunkSize) {
			std::cout << "Initialize Component Pool..." << std::endl;
			m_size = 0;
			m_totalSize = m_elementSize * m_chunkSize;
			m_ptr = malloc(m_totalSize);
		}
		virtual ~Pool() {
			free(m_ptr);
		}

		inline T* Get(const std::size_t n) {
			assert(m_chunkSize > n && "n must be smaller than chunk size");
			return static_cast<T*>(m_ptr) + n;
		}

		inline void Destroy(std::size_t n) {
			assert(m_chunkSize > n && "n must be smaller than chunk size");
			(static_cast<T*>(m_ptr) + n)->~T();
		}

		std::size_t GetChunkSize() const { return this->m_chunkSize; }
		std::size_t GetTotalSize() const { return this->m_totalSize; }
	};
}

#pragma once

#include <vector>
#include <cassert>
#include <type_traits>

namespace ECS {
	template<typename T>
	class SparseSet {
	private:
		std::vector<T> m_sparse;
		std::vector<T> m_dense;

		std::size_t m_size;
		std::size_t m_sparseMax;
		std::size_t m_denseMax;

	public:
		SparseSet(std::size_t sparseMax, std::size_t denseMax) {
			m_sparseMax = sparseMax;
			m_denseMax = denseMax;
			m_sparse.resize(m_sparseMax, 0);
			m_dense.resize(m_denseMax, 0);
		}
		SparseSet(const SparseSet&) = delete;
		SparseSet& operator=(const SparseSet&) = delete;
		~SparseSet() = default;

		using iterator = typename std::vector<T>::const_iterator;
		using const_iterator = typename std::vector<T>::const_iterator;

		iterator begin() { return m_dense.begin(); }
		const_iterator begin() const { return m_dense.begin(); }
		iterator end() { return m_dense.begin() + m_size; }
		const_iterator end() const { return m_dense.begin() + m_size; }

		size_t Size() const { return m_size; }
		size_t SparseMax() const { return m_sparseMase; }
		size_t DenseMax() const { return m_denseMax; }

		inline T GetSparse(const std::size_t dense) const {
			assert(m_denseMax > dense && "dense must be smaller than dense max");
			return m_dense[dense];
		}

		inline T GetDense(const std::size_t sparse) const {
			assert(m_sparseMax > sparse && "sparse must be smaller than sparse max");
			return m_sparse[sparse];
		}

		void Insert(const T sparse, const T dense) {
			assert(m_sparseMax > sparse && m_denseMax > dense && "sparse or dense must be smaller than sparse or dense max");
			m_sparse[sparse] = dense;
			m_dense[dense] = sparse;
		}
	};
}
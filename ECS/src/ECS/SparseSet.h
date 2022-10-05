#pragma once

#include <vector>
#include <cassert>

namespace ECS {
	template<typename T>
	class SparseSet {
	private:
		std::vector<T> m_sparse;
		std::vector<T> m_dense;

		std::size_t m_sparseMax;
		std::size_t m_denseMax;

	public:
		SparseSet(std::size_t sparseMax, std::size_t denseMax) {
			m_sparseMax = sparseMax;
			m_denseMax = denseMax;
			m_sparse.resize(m_sparseMax, 0);
			m_dense.resize(m_denseMax, 0);
		}

		~SparseSet() = default;

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
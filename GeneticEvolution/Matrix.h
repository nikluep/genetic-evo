#pragma once

#include <cstddef>
#include <vector>
#include <functional>


template<class T, std::size_t DIM_COL, std::size_t DIM_ROW>
class Matrix {
public:
	explicit Matrix(const std::function<T()>& randomSource);


	const std::vector<T>& operator[](std::size_t index) const;
	std::vector<T>& operator[](std::size_t index);

	void mult(const std::vector<T>& vector, std::vector<T>& result) const;

private:
	std::vector<std::vector<T>> m_data;
};



template<class T, std::size_t DIM_COL, std::size_t DIM_ROW>
inline Matrix<T, DIM_COL, DIM_ROW>::Matrix(const std::function<T()>& randomSource)
	: m_data(DIM_COL)
{
	for (auto& row : m_data) {
		row.reserve(DIM_ROW);

		for (std::size_t i{}; i < DIM_ROW; ++i) {
			row.push_back(randomSource());
		}
	}
}


template<class T, std::size_t DIM_COL, std::size_t DIM_ROW>
inline const std::vector<T>& Matrix<T, DIM_COL, DIM_ROW>::operator[](std::size_t index) const
{
	return m_data[index];
}

template<class T, std::size_t DIM_COL, std::size_t DIM_ROW>
inline std::vector<T>& Matrix<T, DIM_COL, DIM_ROW>::operator[](std::size_t index)
{
	return m_data[index];
}


/*
 Matrix multiplication of MxN * Nx1 = Mx1
 */
template<class T, std::size_t DIM_COL, std::size_t DIM_ROW>
inline void Matrix<T, DIM_COL, DIM_ROW>::mult(const std::vector<T>& vector, std::vector<T>& result) const
{
	std::size_t i{};
	for (const auto& row : m_data) {
		result[i] = T{};
		for (std::size_t j{}; j < DIM_ROW; ++j) {
			result[i] += row[j] * vector[j];
		}
		++i;
	}
}

#pragma once

#include <cstddef>
#include <vector>
#include <functional>

/**
A basic 2D-Matrix class on a vector basis.

\tparam T Basic element type
\tparam DIM_COL Dimension of columns
\tparam DIM_ROW Dimension of rows
*/
template<class T, std::size_t DIM_COL, std::size_t DIM_ROW>
class Matrix {
public:
	/**
	Construct a randomly initialized Matrix.

	\param randomSource A callable to produce random numbers of the desired distribution
	*/
	explicit Matrix(const std::function<T()>& randomSource);

	/**
	Constant access to the Matrix's rows.
	
	\param index Row index
	\returns Row of elements
	*/
	const std::vector<T>& operator[](std::size_t index) const;

	/**
	Access to the Matrix's rows.

	\param index Row index
	\returns Row of elements
	*/
	std::vector<T>& operator[](std::size_t index);


	/**
	Multiply the Matrix with another vector. Requires that the dimensions match.

	\param[in] vector a vector of size DIM_COL
	\param[out] result a preallocated vector of size DIM_COL to store the result
	*/
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

template<class T, std::size_t DIM_COL, std::size_t DIM_ROW>
inline void Matrix<T, DIM_COL, DIM_ROW>::mult(const std::vector<T>& vector, std::vector<T>& result) const
{
	/*
	Matrix multiplication, each output element is the sum of element-wise products along each row.
	*/
	std::size_t i{};
	for (const auto& row : m_data) {

		result[i] = T{};
		for (std::size_t j{}; j < DIM_ROW; ++j) {
			result[i] += row[j] * vector[j];
		}
		++i;

	}
}

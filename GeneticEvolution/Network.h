#pragma once

#include <vector>
#include <cstddef>
#include <cstdint>
#include <functional>
#include <algorithm>

#include "Matrix.h"
#include "random.h"

template<std::size_t SIZE_IN, std::size_t SIZE_HIDDEN, std::size_t SIZE_OUT, std::size_t NUM_HIDDEN>
class Network
{
public:
	//TODO: Copy/move constructors
	explicit Network();

	/*
	 Feed forward the input through the network. Store the result in output.
	*/
	void forward(const std::vector<float>& input, std::vector<float>& output) const noexcept;

	/*
	 Modify/Overwrite the weights
	 //TODO: Specify interface
	*/
	void update() noexcept {};

private:
	Matrix<float, SIZE_HIDDEN, SIZE_IN> m_inputLayer;
	std::vector< Matrix<float, SIZE_HIDDEN, SIZE_HIDDEN>> m_hiddenLayers;
	Matrix<float, SIZE_OUT, SIZE_HIDDEN> m_outputLayer;
};


template<std::size_t SIZE_IN, std::size_t SIZE_HIDDEN, std::size_t SIZE_OUT, std::size_t NUM_HIDDEN>
inline Network<SIZE_IN, SIZE_HIDDEN, SIZE_OUT, NUM_HIDDEN>::Network()
	: m_inputLayer(getRandomFloat), m_hiddenLayers(), m_outputLayer(getRandomFloat)
{
	m_hiddenLayers.reserve(NUM_HIDDEN);
	for (std::size_t i{}; i < NUM_HIDDEN; ++i) {
		m_hiddenLayers.emplace_back(getRandomFloat);
	}
}

/*
 Feed forward the input through the network. Avoid reallocation/copies by swapping between two intermediate result vectors.
 Store the final result in a preallocated vector.
*/
template<std::size_t SIZE_IN, std::size_t SIZE_HIDDEN, std::size_t SIZE_OUT, std::size_t NUM_HIDDEN>
inline void Network<SIZE_IN, SIZE_HIDDEN, SIZE_OUT, NUM_HIDDEN>::forward(const std::vector<float>& input, std::vector<float>& output) const noexcept
{
	std::vector<float> currentState(SIZE_HIDDEN);
	std::vector<float> nextState(SIZE_HIDDEN);
	m_inputLayer.mult(input, currentState);

	auto* pCurrent = &currentState;
	auto* pNext = &nextState;

	for (const auto& hidden : m_hiddenLayers) {
		hidden.mult(*pCurrent, *pNext);
		std::swap(pCurrent, pNext);
	}

	m_outputLayer.mult(*pCurrent, output);
}

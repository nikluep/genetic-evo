#pragma once

#include <vector>
#include <cstddef>
#include <cstdint>
#include <functional>
#include <algorithm>

#include "Matrix.h"
#include "random.h"


/**
A Neural Network consisting of an input layer, multiple hidden layers and an output layer.

\tparam SIZE_IN Input dimensions
\tparam SIZE_HIDDEN Hidden layer dimensions
\tparam SIZE_OUT Output dimensions
\tparam NUM_HIDDEN Number of hidden layers
*/
template<std::size_t SIZE_IN, std::size_t SIZE_HIDDEN, std::size_t SIZE_OUT, std::size_t NUM_HIDDEN>
class Network
{
public:
	/**
	Construct a Network.

	\todo Copy/Move constructors
	*/
	explicit Network();

	/**
	 Feed forward the input through the Network.

	 \param input[in] Input vector of size SIZE_IN
	 \param output[out] Preallocated vector of size SIZE_OUT to store the result in
	*/
	void forward(const std::vector<float>& input, std::vector<float>& output) const noexcept;

	/**
	 Modify/Overwrite the weights
	 \todo Specify interface
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

template<std::size_t SIZE_IN, std::size_t SIZE_HIDDEN, std::size_t SIZE_OUT, std::size_t NUM_HIDDEN>
inline void Network<SIZE_IN, SIZE_HIDDEN, SIZE_OUT, NUM_HIDDEN>::forward(const std::vector<float>& input, std::vector<float>& output) const noexcept
{
	// Avoid repeated allocation by reusing/swapping two buffers
	std::vector<float> currentState(SIZE_HIDDEN);
	std::vector<float> nextState(SIZE_HIDDEN);
	auto* pCurrent = &currentState;
	auto* pNext = &nextState;


	m_inputLayer.mult(input, currentState);

	for (const auto& hidden : m_hiddenLayers) {
		hidden.mult(*pCurrent, *pNext);
		std::swap(pCurrent, pNext);
	}

	m_outputLayer.mult(*pCurrent, output);
}

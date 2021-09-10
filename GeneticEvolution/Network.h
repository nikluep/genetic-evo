#pragma once
#include <array>
#include <cstddef>
#include <cstdint>
#include <functional>

//TODO: Temporary until proper implementation
template<std::size_t W, std::size_t H>
using Matrix = std::array< std::array<float, W>, H>;

template<std::size_t SIZE_IN, std::size_t SIZE_HIDDEN, std::size_t SIZE_OUT, std::size_t NUM_HIDDEN>
class Network
{
public:
	//TODO: Copy/move constructors
	explicit constexpr Network() noexcept = default;

	/*
	 Feed forward the input through the network. Store the result in output.
	*/
	void forward(const std::array<float, SIZE_IN>& input, std::array<float, SIZE_OUT>& output) const noexcept;

	/*
	 Modify/Overwrite the weights
	 //TODO: Specify interface
	*/
	void update() noexcept {};

private:
	Matrix<SIZE_IN, SIZE_HIDDEN> m_inputLayer;
	std::array< Matrix<SIZE_HIDDEN, SIZE_HIDDEN>, NUM_HIDDEN> m_hiddenLayers;
	Matrix<SIZE_HIDDEN, SIZE_OUT> m_outputLayer;
};

template<std::size_t SIZE_IN, std::size_t SIZE_HIDDEN, std::size_t SIZE_OUT, std::size_t NUM_HIDDEN>
inline void Network<SIZE_IN, SIZE_HIDDEN, SIZE_OUT, NUM_HIDDEN>::forward(const std::array<float, SIZE_IN>& input, std::array<float, SIZE_OUT>& output) const noexcept
{
	//TODO: Implement
}

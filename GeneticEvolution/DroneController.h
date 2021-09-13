#pragma once

#include <vector>

#include "Network.h"


constexpr auto NETWORK_INPUT_DIM = 10;
constexpr auto NETWORK_HIDDEN_DIM = 100;
constexpr auto NETWORK_OUTPUT_DIM = 3;
constexpr auto NETWORK_HIDDEN_COUNT = 3;

class DroneController
{
public:
	DroneController() = default;

	void prepareActions();
	void performActions();

	void updateNetwork();

private:
	Network<NETWORK_INPUT_DIM, NETWORK_HIDDEN_DIM, NETWORK_OUTPUT_DIM, NETWORK_HIDDEN_COUNT> m_network;
	std::vector<float> m_actions;
};


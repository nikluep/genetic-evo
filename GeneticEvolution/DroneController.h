#pragma once

#include <vector>

#include "Network.h"

/*
Specify the Network's dimensions
*/
constexpr auto NETWORK_INPUT_DIM = 10;
constexpr auto NETWORK_HIDDEN_DIM = 100;
constexpr auto NETWORK_OUTPUT_DIM = 3;
constexpr auto NETWORK_HIDDEN_COUNT = 3;

/**
Controller to decide how a drone is supposed to act to reach its goal.
*/
class DroneController
{
public:
	/**
	Default-construct a DroneController.
	*/
	DroneController() = default;

	/**
	Pre-analyze a Drone's state to decide what to do and save the decision for later execution.
	*/
	void prepareActions();

	/**
	Execute the previously prepared actions.
	*/
	void performActions();

	/**
	Update the underlying Neural Network.
	*/
	void updateNetwork();

private:
	Network<NETWORK_INPUT_DIM, NETWORK_HIDDEN_DIM, NETWORK_OUTPUT_DIM, NETWORK_HIDDEN_COUNT> m_network;
	std::vector<float> m_actions;
};


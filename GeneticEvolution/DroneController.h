#pragma once

#include <vector>

#include "Network.h"
#include "Drone.h"

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
	DroneController(Drone& drone);

	/**
	Analyze a Drone's state to decide what to do .
	*/
	void act();

	/**
	Update the underlying Neural Network.
	*/
	void updateNetwork();

	/**
	Get the controlled drone.

	\returns Drone that is controlled
	*/
	const Drone& getDrone() const { return m_drone; }

private:
	Network<NETWORK_INPUT_DIM, NETWORK_HIDDEN_DIM, NETWORK_OUTPUT_DIM, NETWORK_HIDDEN_COUNT> m_network;
	Drone& m_drone;
};


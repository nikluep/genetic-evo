#pragma once

#include <cstddef>
#include <vector>

#include <SFML/Graphics/RenderWindow.hpp>

#include "Drone.h"
#include "DroneController.h"


/**
Window Stage to manage the execution of the simulation.
*/
class Stage
{
public:
	/**
	Construct a Stage.

	\param droneCount Number of drones to simulate
	\param genTarget Number of generations to simulate
	*/
	explicit Stage(std::size_t droneCount, unsigned genTarget);

	/**
	Initialize the Stage with a window to draw in.

	\param Window to contain the Stage
	*/
	void init(sf::RenderWindow& window);

	/**
	Execute the simulation.
	*/
	void run();

private:
	sf::RenderWindow* m_window;
	std::vector<Drone> m_drones;
	std::vector<DroneController> m_controllers;
	const unsigned m_genTarget;
};


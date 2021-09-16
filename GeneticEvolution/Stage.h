#pragma once

#include <cstddef>
#include <vector>
#include <chrono>

#include <SFML/Graphics/RenderWindow.hpp>

#include "Drone.h"
#include "DroneController.h"
#include "Optimizer.h"


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
	explicit Stage(std::size_t droneCount, unsigned generationTarget);

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

	/**
	Handle all types of keyboard, mouse and other input.

	\returns Signals if the main loop should continue
	*/
	bool handleEvents();

	/**
	Check if any drones reached their target.
	*/
	void checkTargetProgress();

	/**
	Create a random target

	\returns a random target inside the window

	\todo implement
	*/
	sf::Vector2f getRandomTarget() const;

	/**
	Ensure a stable framerate.

	\param frameStart Starttime of the current frame
	*/
	void vsync(std::chrono::time_point<std::chrono::system_clock> frameStart) const;


	sf::RenderWindow* m_window;

	std::vector<Drone> m_drones;
	std::vector<DroneController> m_controllers;
	Optimizer m_optimizer;
};


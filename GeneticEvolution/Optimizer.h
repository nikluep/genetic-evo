#pragma once

#include <vector>
#include <chrono>

#include "DroneController.h"



class Optimizer
{	
public:
	/**
	Create an optimizer for a set of controller.

	\param controllers DroneController to optimize
	\param generationTarget Number of generations to train for
	*/
	explicit Optimizer(std::vector<DroneController>& controllers, unsigned generationTarget) noexcept;

	/**
	Start the optimization process.
	*/
	void start();

	/**
	Check progress of current generation.

	\returns Signals if the current generation is complete and a next one started
	*/
	bool doGenerationStep();

	/**
	Select best performing controllers, replicate/transform them and kill of the others. 
	*/
	void evolve();

	/**
	Signals if the generation target has been hit.

	\returns True if current generation < generation target
	*/
	bool isTraining() const { return m_generation < m_generationTarget; };

private:
	std::vector<DroneController>& m_controllers;	

	unsigned m_generation;
	const unsigned m_generationTarget;
	std::chrono::time_point<std::chrono::system_clock> m_generationStart;
};


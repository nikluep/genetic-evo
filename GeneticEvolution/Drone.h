#pragma once

#include <chrono>

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/CircleShape.hpp>

#include "Booster.h"


/**
Drone powered by two Boosters controlled by a DroneController.
*/
class Drone
	: public sf::Drawable, public sf::Transformable
{
public:	
	/**
	Default-construct a Drone.
	*/
	Drone();
	
	/**
	Draw the Drone.
	*/
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	/**
	Calculate new state based on actions during the last tick.

	\param dt Duration of the last tick in ms.
	*/
	void doPhysicsUpdate(std::chrono::duration<float, std::milli> dt);

	/**
	Reset the Drone's entire state and move to a default position.

	\param position Desired initial position
	*/
	void reset(const sf::Vector2f& position);

	/**
	Access the left Booster.

	\returns Left Booster
	*/
	Booster& getLeftBooster() noexcept { return m_boosterLeft; }
	
	/**
	Access the right Booster.

	\returns Right Booster
	*/
	Booster& getRightBooster() noexcept { return m_boosterRight; }

	/**
	Get the Drone's current velocity.

	\returns Velocity in pixels/s
	*/
	const sf::Vector2f& getVelocity() const noexcept { return m_velocity; }

	/**
	Get distance to the current target location.

	\returns Distance in pixel
	*/
	sf::Vector2f getDistanceToTarget() const noexcept { return getPosition() - m_target; }

	/**
	Set a new target location.

	\param target New target location
	*/
	void setTarget(const sf::Vector2f& target) noexcept { m_target = target; }

	/**
	Add a point.
	*/
	void score() { ++m_score; }

	/**
	Get the Controller's score.

	\returns Current score
	*/
	unsigned getScore() const { return m_score; }

private:
	sf::Vector2f m_velocity;
	float m_angularVelocity;

	sf::Vector2f m_target;
	unsigned m_score;

	sf::CircleShape m_body;
	Booster m_boosterLeft;
	Booster m_boosterRight;
};


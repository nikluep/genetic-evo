#pragma once

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/CircleShape.hpp>

#include "Booster.h"


/**
Drone powered by two Boosters controlled by a DroneController.
*/
class Drone
	: public sf::Drawable
{
public:	
	/**
	Default-construct a Drone.
	*/
	Drone() = default;
	
	/**
	Draw the Drone.
	*/
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	/**
	Calculate new state based on actions during the last tick.

	\param dt Duration of the last tick in ms.
	\todo switch to standard's time utils.
	*/
	void doPhysicsUpdate(float dt);

	/**
	Reset the Drone's entire state.
	*/
	void reset();

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
	Get the Drone's rotation.

	\returns Angles from upright orientation
	*/
	float getRotation() const noexcept { return m_rotation; }

	/**
	Get distance to the current target location.

	\returns Distance in pixel
	*/
	sf::Vector2f getDistanceToTarget() const noexcept { return m_position-m_target; }

	/**
	Set a new target location.

	\param target New target location
	*/
	void setTarget(const sf::Vector2f& target) noexcept { m_target = target; };

private:
	sf::Vector2f m_position;
	sf::Vector2f m_velocity;
	float m_rotation;
	sf::Vector2f m_target;

	sf::CircleShape m_body;
	Booster m_boosterLeft;
	Booster m_boosterRight;
};


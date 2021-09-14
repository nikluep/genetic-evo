#pragma once

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/System/Vector2.hpp>


/**
A Drone's source of power.
*/
class Booster
	: private sf::Drawable
{
	friend class Drone;
public:
	/**
	Default-construct a Booster.
	*/
	Booster() = default;

	/**
	Set the angle the Booster is pointing at relative to its underlying base direction.

	\param angle New angle
	*/
	void setAngle(float angle) noexcept { m_angle = angle; };

	/**
	Set the Booster's power level.

	\param power New power level
	*/
	void setPower(float power) noexcept { m_power = power; };

private:
	/**
	Draw the Booster.
	*/
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	/**
	Set the position in absolute coordinates. Intended to be used by the owning Drone.

	\param position New absolute position
	*/
	void setPosition(const sf::Vector2f& position) noexcept;

	/**
	Set the base direction based on the absolute rotation. Intended to be used by the owning Drone.

	\param rotation Absolute rotation of owning Drone
	*/
	void setRotation(float rotation) noexcept;

	float m_angle;
	float m_power;
	sf::Vector2f m_direction;

	sf::RectangleShape m_shape;
};

#pragma once

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/System/Vector2.hpp>


/**
A Drone's source of power.
*/
class Booster
	: private sf::Drawable, private sf::Transformable
{
	friend class Drone;
public:

	/**
	Maximal absolute angle the Booster can rotate from its initial position.
	*/
	static constexpr float ANGLE_BOUNDS{ 25.f };

	/**
	Construct a Booster at the specified position.

	\param position Anker-point of the Booster
	*/
	Booster(const sf::Vector2f& position);

	/**
	Set the angle the Booster is pointing at relative to its underlying base direction.

	\param angle New angle
	*/
	void setAngle(float angle) noexcept;

	/**
	Set the Booster's power level.

	\param power New power level
	*/
	void setPower(float power) noexcept { m_power = power; }

private:
	/**
	Draw the Booster.
	*/
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	/**
	Reset the Booster's control state.
	*/
	void resetControls();

	float m_power;
	sf::RectangleShape m_shape;
};

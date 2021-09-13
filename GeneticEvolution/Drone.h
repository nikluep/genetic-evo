#pragma once

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

class Booster 
	: private sf::Drawable
{
	friend class Drone;
public:
	Booster() = default;

	void setAngle(float angle) noexcept { m_angle = angle; };
	void setPower(float power) noexcept { m_power = power; };

private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	void setPosition(const sf::Vector2f& position) noexcept;
	void setRotation(float rotation) noexcept;

	float m_angle;
	float m_power;
	sf::Vector2f m_direction;

	sf::RectangleShape m_shape;
};

class Drone
	: public sf::Drawable
{
public:
	Drone() = default;
	
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	void doPhysicsUpdate(float dt);
	void reset();

	Booster& getLeftBooster() noexcept { return m_boosterLeft; }
	Booster& getRightBooster() noexcept { return m_boosterRight; }

	const sf::Vector2f& getVelocity() const noexcept { return m_velocity; }
	float getRotation() const noexcept { return m_rotation; }
	sf::Vector2f getDistanceToTarget() const noexcept { return m_position-m_target; }

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


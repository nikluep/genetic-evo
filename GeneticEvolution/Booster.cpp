#include "Booster.h"

#include <algorithm>

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Color.hpp>

// booster graphics config
const sf::Vector2f SIZE{ 10.f, 45.f };
const sf::Color BASE_COLOR{ 0, 0, 255, 255 };

// booster physics config
const sf::Vector2f UNIT_DOWN{ 0.f, -1.f };
constexpr auto FULL_POWER = 12.f / 50; // pixels/seconds^2

Booster::Booster(const sf::Vector2f& position)
	: m_power(), m_shape(SIZE)
{
	setOrigin(SIZE.x / 2, SIZE.y * 0.3f);
	setPosition(position);
	m_shape.setFillColor(BASE_COLOR);
}

void Booster::setAngle(float angle) noexcept
{
	setRotation(std::clamp(angle, -ANGLE_BOUNDS, ANGLE_BOUNDS));
}

void Booster::setPower(float power) noexcept
{
	m_power = std::clamp(power, 0.f, 1.f);
}

void Booster::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(m_shape, states);
}

void Booster::resetControls()
{
	setRotation(0.f);
	m_power = 0.f;
}

sf::Vector2f Booster::getForce() const
{
	// unit vector times power output
	return getTransform() * UNIT_DOWN * m_power * FULL_POWER;
}

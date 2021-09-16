#include "Booster.h"

#include <algorithm>

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Color.hpp>

// booster graphics config
const sf::Vector2f SIZE{ 10.f, 45.f };
const sf::Color BASE_COLOR{ 0, 0, 255, 255 };

// booster physics config
const sf::Vector2f UNIT_UP{ 0.f, -1.f };
constexpr auto FULL_POWER = 9.81f * 100.f * 1.8f; // pixels/seconds^2, overshooting gravity by 80% (each!)

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
	// force = unit vector times power output
	// note that the transform includes translation, so transforming a point does not equal transforming a direction
	const auto direction = getTransform() * UNIT_UP - getTransform() * sf::Vector2f{ 0.f, 0.f };
	return direction * m_power * FULL_POWER;
}

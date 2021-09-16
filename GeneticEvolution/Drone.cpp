#include "Drone.h"

#include <cmath>

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Color.hpp>

// body graphics config
constexpr auto BODY_RADIUS = 20.f;
constexpr auto BODY_X_SCALE = 2.5f;
constexpr auto BODY_RESOLUTION = 30u;
const sf::Color BODY_COLOR{ 0, 100, 255, 255 };

// booster positions
const sf::Vector2f BOOSTER_POS_LEFT{ 0.f, BODY_RADIUS };
const sf::Vector2f BOOSTER_POS_RIGHT{ 2*BODY_RADIUS*BODY_X_SCALE, BODY_RADIUS };

// physics config
// downwards acceleration, in terms of pixels / seconds^2
const sf::Vector2f GRAVITY{ 0.f, 9.81f * 100.f };

Drone::Drone()
	:
		m_velocity(), m_angularVelocity(), m_target(), m_score(),
		m_body(BODY_RADIUS, BODY_RESOLUTION), m_boosterLeft(BOOSTER_POS_LEFT), m_boosterRight(BOOSTER_POS_RIGHT)
{
	setOrigin(BODY_RADIUS, BODY_RADIUS);
	m_body.setScale(BODY_X_SCALE, 1.f);
	m_body.setFillColor(BODY_COLOR);
}

void Drone::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	/*
	All subsequent draws are happening inside the local frame of reference. 
	For details, see https://www.sfml-dev.org/documentation/2.5.1/classsf_1_1Transformable.php.
	*/
	states.transform *= getTransform();

	target.draw(m_body, states);
	target.draw(m_boosterLeft, states);
	target.draw(m_boosterRight, states);
}



void Drone::doPhysicsUpdate(std::chrono::duration<float> dt)
{
	// quick helper functions
	const auto getTangentForce = [](const auto& f) {
		return sf::Vector2f{ 0.f, f.y };
	};
	const auto magnitude = [](const auto& v) {
		return std::sqrtf(v.x * v.x + v.y * v.y);
	};

	// basic booster output
	const auto forceLeft = m_boosterLeft.getForce();
	const auto forceRight = m_boosterRight.getForce();

	// movement
	const auto dv = (forceLeft + forceRight + GRAVITY) * dt.count();
	m_velocity += dv;

	// rotation
	// sum up tangential force vectors, calculate angular velocity delta
	const auto angularForce = magnitude(getTangentForce(forceRight) - getTangentForce(forceLeft));
	m_angularVelocity += angularForce * dt.count();

	// execute
	move(m_velocity * dt.count());
	rotate(m_angularVelocity * dt.count());
}

void Drone::reset(const sf::Vector2f& position)
{
	m_velocity = {};
	m_angularVelocity = 0.f;
	m_target = {};
	m_score = 0;

	setPosition(position);
	setRotation(0.f);

	m_boosterLeft.resetControls(); 
	m_boosterRight.resetControls();
}

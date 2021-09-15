#include "Stage.h"

#include <SFML/Graphics.hpp>

Stage::Stage(std::size_t droneCount, unsigned genTarget)
	: m_window(nullptr), m_drones(droneCount), m_controllers(droneCount), m_genTarget(genTarget)
{
}

void Stage::init(sf::RenderWindow& window)
{
	m_window = &window;
}

void Stage::run()
{

    m_drones[0].reset({ 500.f, 500.f });
    m_drones[0].rotate(45.f);    

    m_drones[1].reset({ 700.f, 500.f });
    m_drones[1].rotate(-15.f);
    m_drones[1].getLeftBooster().setAngle(7.f);
    m_drones[1].getRightBooster().setAngle(-Booster::ANGLE_BOUNDS);

    while (m_window->isOpen())
    {
        sf::Event event;
        while (m_window->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                m_window->close();
        }

        m_window->clear();
        m_window->draw(m_drones[0]);
        m_window->draw(m_drones[1]);
        m_window->display();
    }
}

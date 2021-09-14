#include "Stage.h"

#include <SFML/Graphics.hpp>

Stage::Stage(std::size_t droneCount, unsigned genTarget)
	: m_window(nullptr), m_drones(droneCount), m_genTarget(genTarget)
{
}

void Stage::init(sf::RenderWindow& window)
{
	m_window = &window;
}

void Stage::run()
{
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    while (m_window->isOpen())
    {
        sf::Event event;
        while (m_window->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                m_window->close();
        }

        m_window->clear();
        m_window->draw(shape);
        m_window->display();
    }
}

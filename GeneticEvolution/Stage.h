#pragma once

#include <cstddef>
#include <vector>

#include <SFML/Graphics/RenderWindow.hpp>


class Stage
{
public:
	explicit Stage(std::size_t shipCount, unsigned genTarget);

	void init(sf::RenderWindow& window);

	void run();

private:
	sf::RenderWindow* m_window;
	std::vector<void*> m_ships;
	const unsigned m_genTarget;
};


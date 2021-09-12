#include <iostream>
#include <vector>

#include <SFML/Graphics.hpp>

#include "Network.h"

int main()
{
    Network<10, 100, 3, 2> net;
    std::vector<float> input{ 2.0f, 2.2f, 1.1f, 1.0, -1.f, 2.0f, 2.2f, 1.1f, 1.0, -1.f };
    std::vector<float> result(3);
    net.forward(input, result);

    for (const auto& res : result) {
        std::cout << res << '\n';
    }
    std::cout << std::endl;

    sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(shape);
        window.display();
    }

    return 0;
}
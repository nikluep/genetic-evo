#include <iostream>
#include <vector>

#include <SFML/Graphics.hpp>

#include "Network.h"
#include "Stage.h"

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
    
    Stage stage(100, 3000);
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "Genetic Drone Evolution");
    stage.init(window);
    stage.run();


    return 0;
}
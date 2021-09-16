#include <iostream>
#include <vector>

#include <SFML/Graphics.hpp>

#include "Network.h"
#include "Stage.h"

int main()
{
    Stage stage(3, 3000);
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "Genetic Drone Evolution");
    stage.init(window);
    stage.run();


    return 0;
}
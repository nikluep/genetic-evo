#include "Stage.h"

#include <cmath>
#include <thread>

#include <SFML/Graphics.hpp>

#include "random.h"


constexpr auto TARGET_SIZE = 2.5f;
constexpr auto TARGET_SIZE_SQRD = TARGET_SIZE*TARGET_SIZE;

using namespace std::chrono_literals;
constexpr auto TARGET_FRAMETIME = 1s / 120;

Stage::Stage(std::size_t droneCount, unsigned generationTarget)
	: 
        m_window(nullptr), 
        m_drones(droneCount), m_controllers(), 
        m_optimizer(m_controllers, generationTarget)
{
    m_controllers.reserve(droneCount);
    for (std::size_t i{}; i < droneCount; ++i) {
        m_controllers.emplace_back(m_drones[i]);
    }
}

void Stage::init(sf::RenderWindow& window)
{
	m_window = &window;
}

void Stage::run()
{
    // start the first generation
    const sf::Vector2f startPos = { static_cast<float>(m_window->getSize().x) / 2, static_cast<float>(m_window->getSize().y) / 2 };
    for (auto& drone : m_drones) {
        drone.reset(startPos);
        drone.setTarget(getRandomTarget());
    }
    
    auto frameStart = std::chrono::system_clock::now();
    m_optimizer.start();
    
    // run the main loop
    while (handleEvents()) {
        
        // advance generation every predefined timestep
        if (m_optimizer.doGenerationStep()) {
            m_optimizer.evolve();

            for (auto& drone : m_drones) {
                drone.reset(startPos);
                drone.setTarget(getRandomTarget());
            }
        }

        // controls
        for (auto& controller : m_controllers) {
            controller.act();
        }

        // stable fps
        vsync(frameStart);

        // physics
        auto frameEnd = std::chrono::system_clock::now();
        for (auto& drone : m_drones) {
            drone.doPhysicsUpdate(frameEnd - frameStart);
        }
        frameStart = frameEnd;

        // visuals
        m_window->clear();
        for (const auto& drone : m_drones) {
            m_window->draw(drone);
        }
        m_window->display();
    }
}

bool Stage::handleEvents()
{
    sf::Event event;
    while (m_window->pollEvent(event)) {

        // window closed
        if (event.type == sf::Event::Closed) {
            return false;
        }
    }
    return true;
}

void Stage::checkTargetProgress()
{
    const auto magnitudeSqrd = [](const auto& v) {
        return v.x * v.x + v.y * v.y;
    };

    for (auto& drone : m_drones) {
        const auto targetDistance = drone.getDistanceToTarget();

        // increase score when target is reached
        if (std::abs(magnitudeSqrd(targetDistance)) < TARGET_SIZE_SQRD) {

            drone.score();
            drone.setTarget(getRandomTarget());
        }
    }
}

sf::Vector2f Stage::getRandomTarget() const
{
    return { getRandomFloat() * m_window->getSize().x, getRandomFloat() * m_window->getSize().y };
}

void Stage::vsync(std::chrono::time_point<std::chrono::system_clock> frameStart) const
{
    const auto frameTime = std::chrono::system_clock::now() - frameStart;
    const auto sleepTime = TARGET_FRAMETIME - frameTime;
    if (sleepTime.count() > 0) {
        std::this_thread::sleep_for(sleepTime);
    }
}



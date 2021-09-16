#include "Optimizer.h"

// generation config
using namespace std::chrono_literals;
constexpr auto TIME_PER_GENERATION = 30ms;

Optimizer::Optimizer(std::vector<DroneController>& controllers, unsigned generationTarget) noexcept
    : m_controllers(controllers), m_generation(), m_generationTarget(generationTarget), m_generationStart()
{
}

void Optimizer::start()
{
    m_generation = 0;
    m_generationStart = std::chrono::system_clock::now();
}

bool Optimizer::doGenerationStep()
{
    const auto now = std::chrono::system_clock::now();
    if (now - m_generationStart > TIME_PER_GENERATION) {
        ++m_generation;
        m_generationStart = now;
        return true;
    }

    return false;
}

void Optimizer::evolve()
{
}

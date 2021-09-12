#pragma once
#include <random>


static std::mt19937 gen(1337);
static std::uniform_real_distribution<float> distr(-1.f, 1.f);

extern float getRandomFloat() {
	return distr(gen);
}
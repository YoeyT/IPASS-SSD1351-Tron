#pragma once
#include "bike.hpp"
#include "game.hpp"
#include "wall.hpp"
#include <time.h>

class AIBike : public bike
{
private:

public:
    AIBike(uint8_t locationx, uint8_t locationy, color color = color(0xF800), char direction = 'N');

    void MakeDecision(const bike& otherPlayer, const std::array<wall, 4>& borderWalls);
};
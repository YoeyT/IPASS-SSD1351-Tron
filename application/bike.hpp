#pragma once
#include "gameObject.hpp"
#include "wall.hpp"
#include "gameLogic.hpp"
#include <array>

class bike : public gameObject
{
protected:
    const std::array<std::array<color, 5>, 5> bitMap;

    //dynamic memory is not available on the arduino due, so this will do to save the trail
    std::array<wall, 50> bikeTrail = {{
        wall(0, 0, 0, 0, 0, false),
        wall(0, 0, 0, 0, 0, false),
        wall(0, 0, 0, 0, 0, false),
        wall(0, 0, 0, 0, 0, false),
        wall(0, 0, 0, 0, 0, false),
        wall(0, 0, 0, 0, 0, false),
        wall(0, 0, 0, 0, 0, false),
        wall(0, 0, 0, 0, 0, false),
        wall(0, 0, 0, 0, 0, false),
        wall(0, 0, 0, 0, 0, false),
        wall(0, 0, 0, 0, 0, false),
        wall(0, 0, 0, 0, 0, false),
        wall(0, 0, 0, 0, 0, false),
        wall(0, 0, 0, 0, 0, false),
        wall(0, 0, 0, 0, 0, false),
        wall(0, 0, 0, 0, 0, false),
        wall(0, 0, 0, 0, 0, false),
        wall(0, 0, 0, 0, 0, false),
        wall(0, 0, 0, 0, 0, false),
        wall(0, 0, 0, 0, 0, false),
        wall(0, 0, 0, 0, 0, false),
        wall(0, 0, 0, 0, 0, false),
        wall(0, 0, 0, 0, 0, false),
        wall(0, 0, 0, 0, 0, false),
        wall(0, 0, 0, 0, 0, false),
        wall(0, 0, 0, 0, 0, false),
        wall(0, 0, 0, 0, 0, false),
        wall(0, 0, 0, 0, 0, false),
        wall(0, 0, 0, 0, 0, false),
        wall(0, 0, 0, 0, 0, false),
        wall(0, 0, 0, 0, 0, false),
        wall(0, 0, 0, 0, 0, false),
        wall(0, 0, 0, 0, 0, false),
        wall(0, 0, 0, 0, 0, false),
        wall(0, 0, 0, 0, 0, false),
        wall(0, 0, 0, 0, 0, false),
        wall(0, 0, 0, 0, 0, false),
        wall(0, 0, 0, 0, 0, false),
        wall(0, 0, 0, 0, 0, false),
        wall(0, 0, 0, 0, 0, false),
        wall(0, 0, 0, 0, 0, false),
        wall(0, 0, 0, 0, 0, false),
        wall(0, 0, 0, 0, 0, false),
        wall(0, 0, 0, 0, 0, false),
        wall(0, 0, 0, 0, 0, false),
        wall(0, 0, 0, 0, 0, false),
        wall(0, 0, 0, 0, 0, false),
        wall(0, 0, 0, 0, 0, false),
        wall(0, 0, 0, 0, 0, false),
        wall(0, 0, 0, 0, 0, false)
    }};
    uint8_t bikeTrailIterator = 0;

    //the direction is dictaten by a char, and the velocity is an unsigned integer
    char direction;
    uint8_t velocity = 3;

public:
    bike(uint8_t locationx, uint8_t locationy, color color = color(0xF800), char direction = 'S');

    void Draw(SSD1351& screen) override;

    void ReadAndMove(const bool& upKey, const bool& downKey, const bool& leftKey, const bool& rightKey);

    std::array<wall, 50> GetBikeTrail() const;

    uint8_t GetBikeTrailIterator() const;
};
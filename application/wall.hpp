#pragma once
#include "gameObject.hpp"

class wall : public gameObject
{
private:
    color wallColor;

    bool isActive;
public:
    wall(uint8_t locationx, uint8_t locationy, uint8_t endLocationx, uint8_t endLocationy, color wallColor, bool isActive = true);

    void Draw(SSD1351& screen) override;
};
#include "wall.hpp"

wall::wall(uint8_t locationx, uint8_t locationy, uint8_t endLocationx, uint8_t endLocationy, color wallColor, bool isActive) :
    gameObject(locationx, locationy, endLocationx, endLocationy),
    wallColor(wallColor),
    isActive(isActive)
{}

void wall::Draw(SSD1351& screen)
{
    if(isActive)
    {
        screen.DrawFastRectangle(locationx, locationy, endLocationx, endLocationy, wallColor);
    }
}
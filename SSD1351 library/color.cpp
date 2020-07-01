#include "color.hpp"

///@file

color::color(uint8_t red, uint8_t green, uint8_t blue)
{
    color16 = 0x0000;

    //check if red, green or blue are too big
    red = red > 31 ? 31 : red;
    green = green > 63 ? 63 : green;
    blue = blue > 31 ? 31 : blue;

    //shift all colors in
    color16 |= red;
    color16 = color16 << 6;
    color16 |= green;
    color16 = color16 << 5;
    color16 |= blue;
}

color::color(uint16_t color16) :
    color16(color16)
{}


uint16_t color::GetColor() const
{
    return color16;
}

uint8_t color::GetFirstByte() const
{
    return 0x00 | (color16 >> 8);
}

uint8_t color::GetSecondByte() const
{
    return 0x00 | color16;
}
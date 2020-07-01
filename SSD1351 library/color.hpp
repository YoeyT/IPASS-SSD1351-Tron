#pragma once
#include "hwlib.hpp"

///@file

///\brief
///16-bit color ADT
///\details
///This ADT takes in 5 bits of red and blue and takes in 6 bits of green for a total of 16 bits.
///This ADT makes it easy to express colors on the SSD1351.
class color
{
private:
    ///\brief
    ///the actual color
    uint16_t color16;
public:
    ///\brief
    ///constructor with seperate color initializations
    ///\details
    ///Initializes each color individualy.
    color(uint8_t red, uint8_t green, uint8_t blue);

    ///\brief
    ///constructor with one whole color initialization
    ///\details
    ///Initializes the color with one 16-bit integer.
    color(uint16_t color16);

    ///\brief
    ///getter for the entire 16-bit color
    uint16_t GetColor() const;

    ///\brief
    ///getter for the first byte of the 16-bit color
    ///\details
    ///This makes it easy to break the color up for two 8-bit transactions.
    uint8_t GetFirstByte() const;

    ///\brief
    ///getter for the second byte of the 16-bit color
    ///\details
    ///This makes it easy to break the color up for two 8-bit transactions.
    uint8_t GetSecondByte() const;
};
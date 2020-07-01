#pragma once
#include "hwlib.hpp"
#include "SSD1351.hpp"

class gameObject
{
protected:
    uint8_t locationx, locationy, endLocationx, endLocationy;
private:
    
public:
    //game objects have fixed sizes, so no end location has to be given
    gameObject(uint8_t locationx, uint8_t locationy, uint8_t endLocationx, uint8_t endLocationy);

    virtual void Draw(SSD1351& screen) {};

    uint8_t GetLocationx() const;

    uint8_t GetLocationy() const;

    uint8_t GetEndLocationx() const;

    uint8_t GetEndLocationy() const;
};
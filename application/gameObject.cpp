#include "gameObject.hpp"

gameObject::gameObject(uint8_t locationx, uint8_t locationy, uint8_t endLocationx, uint8_t endLocationy) :
    locationx(locationx),
    locationy(locationy),
    endLocationx(endLocationx),
    endLocationy(endLocationy)
{}

uint8_t gameObject::GetLocationx() const
{
    return locationx;
}

uint8_t gameObject::GetLocationy() const
{
    return locationy;
}

uint8_t gameObject::GetEndLocationx() const
{
    return endLocationx;
}

uint8_t gameObject::GetEndLocationy() const
{
    return endLocationy;
}
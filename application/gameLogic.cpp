#include "gameLogic.hpp"

bool Collision(const gameObject& object1, const gameObject& object2)
{
    if(
        //check for collision on x-axis
        (
        (object1.GetLocationx() >= object2.GetLocationx() && object1.GetLocationx() <= object2.GetEndLocationx()) ||
        (object1.GetEndLocationx() >= object2.GetLocationx() && object1.GetEndLocationx() <= object2.GetEndLocationx()) ||
        (object2.GetLocationx() >= object1.GetLocationx() && object2.GetLocationx() <= object1.GetEndLocationx()) ||
        (object2.GetEndLocationx() >= object1.GetLocationx() && object2.GetEndLocationx() <= object1.GetEndLocationx())
        ) &&

        //check for collision on y-axis
        (
        (object1.GetLocationy() >= object2.GetLocationy() && object1.GetLocationy() <= object2.GetEndLocationy()) ||
        (object1.GetEndLocationy() >= object2.GetLocationy() && object1.GetEndLocationy() <= object2.GetEndLocationy()) ||
        (object2.GetLocationy() >= object1.GetLocationy() && object2.GetLocationy() <= object1.GetEndLocationy()) ||
        (object2.GetEndLocationy() >= object1.GetLocationy() && object2.GetEndLocationy() <= object1.GetEndLocationy())
        )
    )
    {
        return true;
    }
    return false;
}

//checks if certain trail sections can be conjoined into one
//this function saves a lot of memory and runtime
//returns whether pieces can be combined or not
bool CanCombine(std::array<wall, 50>& bikeTrail, uint8_t iterator)
{
    if(
        //check if wall can be conjoined on x axis
        (
        (bikeTrail[iterator - 1].GetLocationx() == bikeTrail[iterator - 2].GetEndLocationx()) && 
        (bikeTrail[iterator - 1].GetEndLocationx() == bikeTrail[iterator - 2].GetLocationx())
        ) ||

        //check if wall can be conjoined on y axis
        (
        (bikeTrail[iterator - 1].GetLocationy() == bikeTrail[iterator - 2].GetEndLocationy()) && 
        (bikeTrail[iterator - 1].GetEndLocationy() == bikeTrail[iterator - 2].GetLocationy())
        )
    )
    {
        return true;
    }
    return false;
}
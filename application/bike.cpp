#include "bike.hpp"

bike::bike(uint8_t locationx, uint8_t locationy, color color, char direction) :
    gameObject(locationx, locationy, (locationx + bitMap[0].size() - 1), (locationy + bitMap.size() - 1)),
    bitMap({{
        {0x0000, 0x0000, color, 0x0000, 0x0000}, 
        {0x0000, 0xFFFF, color, 0xFFFF, 0x0000}, 
        {0x0000, 0xFFFF, color, 0xFFFF, 0x0000},
        {0x0000, 0xFFFF, color, 0xFFFF, 0x0000},
        {0x0000, 0x0000, color, 0x0000, 0x0000}
    }}),
    direction(direction)
{}


void bike::Draw(SSD1351& screen)
{
    //reset pixels where object used to be
    switch(direction)
    {
        case 'N':
            screen.DrawFastRectangle(locationx, (locationy + velocity), endLocationx, (endLocationy + velocity), 0);
            break;
        case 'S':
            screen.DrawFastRectangle(locationx, (locationy - velocity), endLocationx, (endLocationy - velocity), 0);
            break;
        case 'W':
            screen.DrawFastRectangle((locationx + velocity), locationy, (endLocationx + velocity), endLocationy, 0);
            break;
        case 'E':
            screen.DrawFastRectangle((locationx - velocity), locationy, (endLocationx - velocity), endLocationy, 0);
            break;
    }

    //Draw the player
    screen.Draw5x5BitMap(bitMap, locationx, locationy);

    //Draw the last trail piece and conjoin it with another trail piece if possible
    if(bikeTrailIterator != 0)
    {
        bikeTrail[bikeTrailIterator - 1].Draw(screen);

        //this takes care of the combining
        if(bikeTrailIterator > 1 && CanCombine(bikeTrail, bikeTrailIterator))
        {
            //temp values for trail parts because it makes the code cleaner
            uint8_t trail1Locationx = bikeTrail[bikeTrailIterator - 1].GetLocationx();
            uint8_t trail1Locationy = bikeTrail[bikeTrailIterator - 1].GetLocationy();

            uint8_t trail2Locationx = bikeTrail[bikeTrailIterator - 2].GetLocationx();
            uint8_t trail2Locationy = bikeTrail[bikeTrailIterator - 2].GetLocationy();


            if(trail2Locationy == trail1Locationy)
            {
                //merge on x
                bikeTrail[bikeTrailIterator - 2] = wall(
                    (trail1Locationx < trail2Locationx) ? trail1Locationx : trail2Locationx,
                    trail1Locationy,
                    (trail1Locationx > trail2Locationx) ? bikeTrail[bikeTrailIterator - 1].GetEndLocationx() : bikeTrail[bikeTrailIterator - 2].GetEndLocationx(),
                    trail1Locationy,
                    bitMap[0][0].GetColor()
                );
            }
            else if(trail2Locationx == trail1Locationx)
            {
                //merge on y
                bikeTrail[bikeTrailIterator - 2] = wall(
                    trail1Locationx,
                    (trail1Locationy < trail2Locationy) ? trail1Locationy : trail2Locationy,
                    trail1Locationx,
                    (trail1Locationy > trail2Locationy) ? bikeTrail[bikeTrailIterator - 1].GetEndLocationy() : bikeTrail[bikeTrailIterator - 2].GetEndLocationy(),
                    bitMap[0][0].GetColor()
                );
            }

            //shifting the wall values back by one
            bikeTrail[bikeTrailIterator - 1] = wall(0, 0, 0, 0, 0, false);
            bikeTrailIterator--;
        }
    }

    //add a new trail piece to bikeTrail
    switch(direction)
    {
        case 'N':
            bikeTrail[bikeTrailIterator] = wall((locationx + 2), (locationy + 2), (locationx + 2), (locationy + 2 + velocity), bitMap[0][2].GetColor());
            break;
        case 'S':
            bikeTrail[bikeTrailIterator] = wall((locationx + 2), (locationy + 2 - velocity), (locationx + 2), (locationy + 2), bitMap[0][2].GetColor());
            break;
        case 'W':
            bikeTrail[bikeTrailIterator] = wall((locationx + 2), (locationy + 2), (locationx + 2 + velocity), (locationy + 2), bitMap[0][2].GetColor());
            break;
        case 'E':
            bikeTrail[bikeTrailIterator] = wall((locationx + 2 - velocity), (locationy + 2), (locationx + 2), (locationy + 2), bitMap[0][2].GetColor());
            break;
    }
    bikeTrailIterator++;
}

void bike::ReadAndMove(const bool& upKey, const bool& downKey, const bool& leftKey, const bool& rightKey)
{
    //read the inputs and change direction according to it
    //the inputs of the bike object need to be boolean, this way a non-player entity may move according to other inputs
    if(upKey && direction != 'S')
    {
        direction = 'N';
    }
    else if(downKey && direction != 'N')
    {
        direction = 'S';
    }
    else if(leftKey && direction != 'E')
    {
        direction = 'W';
    }
    else if(rightKey && direction != 'W')
    {
        direction = 'E';
    }

    //change location of object according to the velocity of the object
    switch(direction)
    {
        case 'N':
            locationy -= velocity;
            endLocationy -= velocity;
            break;
        case 'S':
            locationy += velocity;
            endLocationy += velocity;
            break;
        case 'W':
            locationx -= velocity;
            endLocationx -= velocity;
            break;
        case 'E':
            locationx += velocity;
            endLocationx += velocity;
            break;
    }
}

std::array<wall, 50> bike::GetBikeTrail() const
{
    return bikeTrail;
}

uint8_t bike::GetBikeTrailIterator() const
{
    return bikeTrailIterator;
}
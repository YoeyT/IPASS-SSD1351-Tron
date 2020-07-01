#include "AIBike.hpp"

AIBike::AIBike(uint8_t locationx, uint8_t locationy, color color, char direction) :
    bike(locationx, locationy, color, direction)
{}

void AIBike::MakeDecision(const bike& otherPlayer, const std::array<wall, 4>& borderWalls)
{
    //random is seeded with both locations of the AI, this way every place is unique from the others
    srand((locationx * locationy * otherPlayer.GetLocationx() * otherPlayer.GetLocationy() * 86632));
    int random = rand();

    //AI inputs
    bool up = false;
    bool down = false;
    bool left = false;
    bool right = false;

    //directions you can move to
    //the last spot has priority when in danger
    std::array<char, 3> availableDirections = {{'0', '0', '0'}};
    char newDirection;

    //fill available directions
    //some directions have priority over others depending on the situation
    switch(direction)
    {
        case 'N':
            availableDirections[0] = 'N';

            if(locationx > 63)
            {
                availableDirections[1] = 'E';
                availableDirections[2] = 'W';
            }
            else
            {
                availableDirections[1] = 'W';
                availableDirections[2] = 'E';
            }
            break;
        case 'S':
            availableDirections[0] = 'S';
            if(locationx > 63)
            {
                availableDirections[1] = 'E';
                availableDirections[2] = 'W';
            }
            else
            {
                availableDirections[1] = 'W';
                availableDirections[2] = 'E';
            }
            break;
        case 'W':
            availableDirections[0] = 'W';
            if(locationy > 63)
            {
                availableDirections[1] = 'N';
                availableDirections[2] = 'S';
            }
            else
            {
                availableDirections[1] = 'S';
                availableDirections[2] = 'N';
            }
            break;
        case 'E':
            availableDirections[0] = 'E';
            if(locationy > 63)
            {
                availableDirections[1] = 'N';
                availableDirections[2] = 'S';
            }
            else
            {
                availableDirections[1] = 'S';
                availableDirections[2] = 'N';
            }
            break;
    }


    //test whether a dummy would crash in every available direction
    bike testDummy1 = bike(locationx, locationy, 0, availableDirections[0]);
    bike testDummy2 = bike(locationx, locationy, 0, availableDirections[1]);
    bike testDummy3 = bike(locationx, locationy, 0, availableDirections[2]);

    bike twinDummy = *this;

    //move twin head out of the way
    twinDummy.ReadAndMove(up, down, left, right);
    twinDummy.ReadAndMove(up, down, left, right);
    twinDummy.ReadAndMove(up, down, left, right);
    twinDummy.ReadAndMove(up, down, left, right);

    std::array<bike*, 3> dummies = {{&testDummy1, &testDummy2, &testDummy3}};

    for(auto dummy : dummies)
    {
        //move the dummy to new location
        dummy->ReadAndMove(up, down, left, right);
    }

    for(uint8_t x = 0; x < dummies.size(); x++)
    {
        //check for any collisions
        //the dummies don't have trails, so it should also check for collisions with the other player as itself
        if(CheckCollisions(*dummies[x], otherPlayer, borderWalls) || CheckCollisions(*dummies[x], twinDummy, borderWalls))
        {
            availableDirections[x] = '0';
        }
    }

    for(char dir : availableDirections)
    {
        if(dir == direction)
        {
            //if there is no danger then the AI has a 1/20 chance of changing to a random available direction
            newDirection = ((availableDirections[(random % 3)]) != '0' && ((random % 20) == 0)) ? availableDirections[random % 3] : direction;
            break;
        }

        //change direction to an available direction if forward isn't an option
        switch(dir)
        {
        case 'N':
            newDirection = 'N';
            break;
        case 'S':
            newDirection = 'S';
            break;
        case 'W':
            newDirection = 'W';
            break;
        case 'E':
            newDirection = 'E';
            break;
        }
    }

    //translate the choice to inputs
    up = newDirection == 'N' ? true : false;
    down = newDirection == 'S' ? true : false;
    left = newDirection == 'W' ? true : false;
    right = newDirection == 'E' ? true : false;

    //make the call
    ReadAndMove(up, down, left, right);
}
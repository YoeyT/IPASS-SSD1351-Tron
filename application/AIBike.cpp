#include "AIBike.hpp"

AIBike::AIBike(uint8_t locationx, uint8_t locationy, color color, char direction) :
    bike(locationx, locationy, color, direction)
{}

//very dumb and poorly made AI
void AIBike::MakeDecision(const bike& otherPlayer, const std::array<wall, 4>& borderWalls)
{
    //random is seeded with both locations of the AI, this way every place is unique from the others
    srand((locationx * locationy * otherPlayer.GetLocationx() * otherPlayer.GetLocationy() * 86632)); //most magic of magic numbers
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
    availableDirections[0] = direction;
    
    //schrijf jezelf nooit in een situatie dat je zoiets moet schrijven
    switch(direction)
    {
        case 'N':
            if(locationx > 63) //magic number
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
    //wat????
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
        newDirection = dir;
    }

    //translate the choice to inputs
    up = newDirection == 'N'
    down = newDirection == 'S'
    left = newDirection == 'W'
    right = newDirection == 'E'

    //make the call
    ReadAndMove(up, down, left, right);
}

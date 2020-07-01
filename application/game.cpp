#include "game.hpp"

void StartGame(SSD1351& screen, hwlib::pin_in& upKey, hwlib::pin_in& downKey, hwlib::pin_in& leftKey, hwlib::pin_in& rightKey)
{
    //setup
    screen.Init();
    screen.FillScreen(0);

    //player
    bike player(12, 12, color(0, 0xFF, 0xFF));
    player.Draw(screen);

    //AI
    AIBike AI(111, 111, color(0xF8, 0x00, 0x00));
    AI.Draw(screen);

    //Borders
    wall borderLeft(0, 0, 2, 127, 0x001F);
    wall borderDown(0, 125, 127, 127, 0x001F);
    wall borderUp(0, 0, 127, 2, 0x001F);
    wall borderRight(125, 0, 127, 127, 0x001F);

    borderLeft.Draw(screen);
    borderDown.Draw(screen);
    borderUp.Draw(screen);
    borderRight.Draw(screen);

    const std::array<wall , 4> borderWalls = {borderLeft, borderDown, borderUp, borderRight};

    bool gameQuit = false;
    uint16_t colorWon;

    //gameloop, this runs every "frame"
    while(!gameQuit)
    {
        //read player inputs and move accordingly
        player.ReadAndMove(!upKey.read(), !downKey.read(), !leftKey.read(), !rightKey.read());
        player.Draw(screen);

        //Make a decision and move accordingly
        AI.MakeDecision(player, borderWalls);
        AI.Draw(screen);

        //check for collisions
        if(CheckCollisions(AI, player, borderWalls))
        {
            gameQuit = true;
            colorWon = 0x07FF;
        }
        else if(CheckCollisions(player, AI, borderWalls))
        {
            gameQuit = true;
            colorWon = 0xF800;
        }

        //limit frames per second, otherwise the game is too fast
        hwlib::wait_ms(50);
    }
    screen.FillScreen(colorWon);
}

bool CheckCollisions(const bike& player, const bike& otherPlayer, const std::array<wall, 4>& borderWalls)
{
    //check for wall collision
    for(wall wallObject : borderWalls)
    {
        if(Collision(player, wallObject))
        {
            return true;
        }
    }

    //check bike trail collisions
    for(uint8_t trail = 0; trail < (player.GetBikeTrailIterator() - 1); trail++)
    {
        if(Collision(player, player.GetBikeTrail()[trail]))
        {
            return true;
        }
    }
    //check other player bike trail collisions
    for(uint8_t trail = 0; trail < (otherPlayer.GetBikeTrailIterator() - 1); trail++)
    {
        if(Collision(player, otherPlayer.GetBikeTrail()[trail]))
        {
            return true;
        }
    }

    //check bike to bike collision
    if(Collision(player, otherPlayer))
    {
        return true;
    }

    return false;
}
#pragma once
#include "SSD1351.hpp"
#include "bike.hpp"
#include "wall.hpp"
#include "gameObject.hpp"
#include "gameLogic.hpp"
#include "AIBike.hpp"


void StartGame(SSD1351& screen, hwlib::pin_in& upKey, hwlib::pin_in& downKey, hwlib::pin_in& leftKey, hwlib::pin_in& rightKey);

bool CheckCollisions(const bike& player, const bike& otherPlayer, const std::array<wall, 4>& borderWalls);
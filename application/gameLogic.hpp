#pragma once
#include "gameObject.hpp"
#include "wall.hpp"

bool Collision(const gameObject& object1, const gameObject& object2);

bool CanCombine(std::array<wall, 50>& bikeTrail, uint8_t iterator);
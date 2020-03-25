#ifndef MAIN_H
#define MAIN_H

#include <iostream>
#include <vector>
#include <utility>
#include <string>

enum Move
{
  UP,
  DOWN,
  LEFT,
  RIGHT
};

const std::vector<std::string> MOVE_TO_STRING{"UP", "DOWN", "LEFT", "RIGHT"};

#endif
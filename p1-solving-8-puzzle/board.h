#ifndef BOARD_H
#define BOARD_H

#include "main.h"
#include <iostream>
#include <vector>
using namespace std;

class Board
{
  vector<vector<int>> state;
  pair<int, int> zeroPos;
  pair<int, int> getZeroPosition();
  pair<int, int> getPosition(int val);

public:
  static const vector<int> solutionState;
  static const vector<pair<int, int>> moveOffset;

  Board(vector<int> initialState);
  bool canMove(Move direction);
  void move(Move direction);
  void operator=(const Board &b);
  int encode();
  int encodeWithDepth(int depth);
  int numTilesOutOfPlace();
  int manhattanDistance();
  void printBoard();
  bool solved();
};

#endif
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
  pair<int, int> getZeroPosition() const;
  pair<int, int> getPosition(int val) const;

public:
  static const vector<int> solutionState;
  static const vector<pair<int, int>> moveOffset;

  Board(vector<int> initialState);
  bool canMove(Move direction);
  void move(Move direction);
  void operator=(const Board &b);
  int encode() const;
  int encodeWithDepth(int depth) const;
  int numTilesOutOfPlace() const;
  int manhattanDistance() const;
  void printBoard();
  bool solved();
};

struct BoardCompareManhattan {
  bool operator()(Board const& b1, Board const& b2);
};

#endif
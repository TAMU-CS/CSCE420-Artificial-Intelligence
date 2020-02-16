#ifndef SEARCH_H
#define SEARCH_H

#include "board.h"

#include <vector>
#include <queue>
#include <unordered_map>
#include <string>
#include <utility>
#include <limits>

struct BFSBoardCompareManhattan {
  bool operator()(Board const &b1, Board const &b2);
};

struct BFSBoardCompareTilesOutOfPlace {
  bool operator()(Board const &b1, Board const &b2);
};

struct AStarBoardCompareManhattan {
  bool operator()(Board const &b1, Board const &b2);
};

struct AStarBoardCompareTilesOutOfPlace {
  bool operator()(Board const &b1, Board const &b2);
};

void dfs(Board board);
void bfs(Board board);
void ids(Board board);
void greedyBestFirst(Board board);
void astar(Board board);



#endif
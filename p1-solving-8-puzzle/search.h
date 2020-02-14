#ifndef SEARCH_H
#define SEARCH_H

#include "board.h"

#include <vector>
#include <queue>
#include <unordered_map>
#include <string>
#include <utility>

void dfs(Board board);
void bfs(Board board);
void ids(Board board);

#endif
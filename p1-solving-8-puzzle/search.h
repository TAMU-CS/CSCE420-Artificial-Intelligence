#ifndef SEARCH_H
#define SEARCH_H

#include "board.h"

#include <vector>
#include <queue>
#include <unordered_map>
#include <string>
#include <utility>
#include <limits>

struct BFSBoardCompareManhattan
{
  bool operator()(Board const &b1, Board const &b2);
};

struct BFSBoardCompareTilesOutOfPlace
{
  bool operator()(Board const &b1, Board const &b2);
};

struct AStarBoardCompareManhattan
{
  bool operator()(Board const &b1, Board const &b2);
};

struct AStarBoardCompareTilesOutOfPlace
{
  bool operator()(Board const &b1, Board const &b2);
};

Board getBoardFromString(string input);

void dfs(Board board);
void bfs(Board board);
void ids(Board board);

template <class comparator>
void greedyBestFirst(Board board)
{
  unordered_map<int, bool> checkDup;
  priority_queue<Board, vector<Board>, comparator> pqueue;
  pqueue.push(board);
  bool hasSolution = false;
  int nodeCount = 0;
  int maxNodeListSize = 0;
  Board solution;
  checkDup[board.encode()] = true;

  while (!pqueue.empty())
  {
    nodeCount++;
    Board curBoard = pqueue.top();
    pqueue.pop();

    if (curBoard.solved())
    {
      hasSolution = true;
      solution = curBoard;
      break;
    }
    else
    {
      for (int i = 0; i < 4; i++)
      {
        Move mv = static_cast<Move>(i);
        if (curBoard.canMove(mv))
        {
          Board newBoard = curBoard;
          newBoard.move(mv);

          int hash = newBoard.encode();

          if (checkDup.find(hash) == checkDup.end())
          {
            checkDup[hash] = true;
            pqueue.push(newBoard);
          }
        }
      }
    }

    if(pqueue.size() > maxNodeListSize){
      maxNodeListSize = pqueue.size();
    }
  }

  if (hasSolution)
  {
    solution.printMoves();
  }
  else
  {
    cout << "Solution Does Not Exist!" << endl;
  }
  cout << "Nodes visited: " << nodeCount << endl;
  cout << "MaxNodeListSize: " << maxNodeListSize << endl;
}

template <class comparator>
void astar(Board board)
{
  unordered_map<int, int> checkDup;
  priority_queue<Board, vector<Board>, comparator> pqueue;
  pqueue.push(board);
  bool hasSolution = false;
  int nodeCount = 0;
  int maxNodeListSize = 0;
  Board solution;
  checkDup[board.encode()] = board.getNumMoves() + board.manhattanDistance();

  while (!pqueue.empty())
  {
    nodeCount++;
    Board curBoard = pqueue.top();
    pqueue.pop();

    if (curBoard.solved())
    {
      hasSolution = true;
      solution = curBoard;
      break;
    }
    else
    {
      for (int i = 0; i < 4; i++)
      {
        Move mv = static_cast<Move>(i);
        if (curBoard.canMove(mv))
        {
          Board newBoard = curBoard;
          newBoard.move(mv);

          int hash = newBoard.encode();
          int heuristic = newBoard.getNumMoves() + newBoard.manhattanDistance();

          if (checkDup.find(hash) == checkDup.end())
          {
            checkDup[hash] = heuristic;
            pqueue.push(newBoard);
          }
          else if (heuristic < checkDup[hash])
          {
            checkDup[hash] = heuristic;
            pqueue.push(newBoard);
          }
        }
      }
    }

    if(pqueue.size() > maxNodeListSize){
      maxNodeListSize = pqueue.size();
    }
  }

  if (hasSolution)
  {
    solution.printMoves();
  }
  else
  {
    cout << "Solution Does Not Exist!" << endl;
  }
  cout << "Nodes visited: " << nodeCount << endl;
  cout << "MaxNodeListSize: " << maxNodeListSize << endl;
}

#endif
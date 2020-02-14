#include "search.h"
#include "board.h"
#include "main.h"
using namespace std;

bool dfs_helper(Board board, vector<Move> moves, unordered_map<int, bool> &visited, vector<Move> &solution, int &nodeCount)
{
  nodeCount++;

  if (board.solved())
  {
    for (int i = 0; i < moves.size(); i++)
    {
      solution.push_back(moves[i]);
    }

    return true;
  }

  for (int i = 0; i < 4; i++)
  {
    Move mv = static_cast<Move>(i);

    if (board.canMove(mv))
    {
      Board newBoard = board;
      newBoard.move(mv);
      int hash = newBoard.encode();

      if (visited.find(hash) == visited.end())
      {
        vector<Move> newMoves = moves;
        newMoves.push_back(mv);
        visited[hash] = true;
        if (dfs_helper(newBoard, newMoves, visited, solution, nodeCount))
        {
          return true;
        };
      }
    }
  }

  return false;
}

void dfs(Board board)
{
  unordered_map<int, bool> visited;
  visited[board.encode()] = true;
  vector<Move> solution;
  int nodeCount = 0;

  bool solved = dfs_helper(board, vector<Move>(0), visited, solution, nodeCount);

  cout << "Solved with moves: \n";

  for (int i = 0; i < solution.size(); i++)
  {
    Move mv = solution[i];
    //board.move(mv);
    cout << MOVE_TO_STRING[solution[i]] << " ";
    //board.printBoard();
  }
  cout << "\nNodes visited: " << nodeCount << endl;
}

void bfs(Board board)
{
  unordered_map<int, bool> checkDup;
  queue<pair<Board, vector<Move>>> bfsQueue;
  int nodeCount = 1;
  bool hasSolution = false;
  vector<Move> solution;

  bfsQueue.push(make_pair(board, vector<Move>()));
  checkDup[board.encode()] = true;

  while (!bfsQueue.empty())
  {
    Board frontBoard = bfsQueue.front().first;
    vector<Move> frontMoves = bfsQueue.front().second;
    bfsQueue.pop();
    nodeCount++;

    if (frontBoard.solved())
    {
      hasSolution = true;
      solution = frontMoves;
      break;
    }
    else
    {

      for (int i = 0; i < 4; i++)
      {
        Move mv = static_cast<Move>(i);
        if (frontBoard.canMove(mv))
        {
          Board newBoard = frontBoard;
          newBoard.move(mv);

          int hash = newBoard.encode();

          if (checkDup.find(hash) == checkDup.end())
          {
            checkDup[hash] = true;
            vector<Move> newMoves = frontMoves;
            newMoves.push_back(mv);
            bfsQueue.push(make_pair(newBoard, newMoves));
          }
        }
      }
    }
  }

  if (hasSolution)
  {
    cout << "Solved with moves: ";
    for (int i = 0; i < solution.size(); i++)
    {
      cout << MOVE_TO_STRING[solution[i]] << " ";
    }
    cout << endl;
  }
  else
  {

    cout << "Solution Does Not Exist!" << endl;
  }
  cout << "Nodes visited: " << nodeCount << endl;
}

bool ids_helper(Board board, vector<Move> moves, unordered_map<int, bool> &visited, vector<Move> &solution, int &nodeCount, int curDepthFromLimit)
{
  nodeCount++;

  if (curDepthFromLimit < 0)
  {
    return false;
  }

  if (board.solved())
  {
    for (int i = 0; i < moves.size(); i++)
    {
      solution.push_back(moves[i]);
    }

    return true;
  }

  for (int i = 0; i < 4; i++)
  {
    Move mv = static_cast<Move>(i);

    if (board.canMove(mv))
    {
      Board newBoard = board;
      newBoard.move(mv);
      int hash = newBoard.encodeWithDepth(curDepthFromLimit);

      if (visited.find(hash) == visited.end())
      {
        vector<Move> newMoves = moves;
        newMoves.push_back(mv);
        visited[hash] = true;
        if (ids_helper(newBoard, newMoves, visited, solution, nodeCount, curDepthFromLimit - 1))
        {
          return true;
        };
      }
    }
  }

  return false;
}

void ids(Board board)
{

  bool hasSolution = false;
  int depthLimit = 0;
  vector<Move> solution;

  while (!hasSolution)
  {
    unordered_map<int, bool> visited;
    visited[board.encodeWithDepth(0)] = true;
    int nodeCount = 0;
    hasSolution = ids_helper(board, vector<Move>(0), visited, solution, nodeCount, depthLimit);

    cout << "Depth: " << depthLimit << " NodeCount: " << nodeCount << endl;

    depthLimit++;
  }

  for (int i = 0; i < solution.size(); i++)
  {
    Move mv = solution[i];
    //board.move(mv);
    cout << MOVE_TO_STRING[solution[i]] << " ";
    //board.printBoard();
  }
  cout << endl;
}

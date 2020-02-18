#include "search.h"
#include "board.h"
#include "main.h"
using namespace std;

bool BFSBoardCompareManhattan::operator()(Board const &b1, Board const &b2)
{
  return b1.manhattanDistance() > b2.manhattanDistance();
}

bool BFSBoardCompareTilesOutOfPlace::operator()(Board const &b1, Board const &b2)
{
  return b1.numTilesOutOfPlace() > b2.numTilesOutOfPlace();
}

bool AStarBoardCompareManhattan::operator()(Board const &b1, Board const &b2)
{
  return (b1.getNumMoves() + b1.manhattanDistance()) > (b2.getNumMoves() + b2.manhattanDistance());
}

bool AStarBoardCompareTilesOutOfPlace::operator()(Board const &b1, Board const &b2)
{
  return (b1.getNumMoves() + b1.numTilesOutOfPlace()) > (b2.getNumMoves() + b2.numTilesOutOfPlace());
}

Board getBoardFromString(string input){
  input = input.substr(1, input.size() - 2);

  vector<int> state;
  for(int i = 0; i < input.size(); i++){
    if(isdigit(input[i])){
      state.push_back(input[i] - '0');
    }
  }

  return Board(state);
}

Board dfs_helper(Board board, unordered_map<int, bool> &visited, int &nodeCount, int curDepth, int depthLimit)
{
  if (curDepth > depthLimit)
  {
    return board;
  }

  nodeCount++;

  if (board.solved())
  {
    return board;
  }

  for (int i = 0; i < 4; i++)
  {
    Move mv = static_cast<Move>(i);

    if (board.canMove(mv))
    {
      Board newBoard = board;
      newBoard.move(mv);
      int hash = newBoard.encodeWithDepth(curDepth);

      if (visited.find(hash) == visited.end())
      {
        visited[hash] = true;
        Board result = dfs_helper(newBoard, visited, nodeCount, curDepth + 1, depthLimit);
        if (result.solved())
        {
          return result;
        }
      }
    }
  }

  return board;
}

void dfs(Board board)
{
  unordered_map<int, bool> visited;
  visited[board.encode()] = true;
  int nodeCount = 0;

  Board result = dfs_helper(board, visited, nodeCount, 0, numeric_limits<int>::infinity());

  if (result.solved())
  {
    result.printBoard();
    result.printMoves();
  }
  else
  {
    cout << "Not solved\n";
  }
  cout << "\nNodes visited: " << nodeCount << endl;
}

void ids(Board board)
{

  bool hasSolution = false;
  int depthLimit = 0;
  Board solution;

  while (!hasSolution)
  {
    unordered_map<int, bool> visited;
    visited[board.encodeWithDepth(0)] = true;
    int nodeCount = 0;
    solution = dfs_helper(board, visited, nodeCount, 0, depthLimit);
    cout << "Depth: " << depthLimit << " NodeCount: " << nodeCount << endl;

    hasSolution = solution.solved();
    depthLimit++;
  }

  if (hasSolution)
  {
    solution.printBoard();
    solution.printMoves();
  }
  else
  {
    cout << "Solution Does Not Exist!" << endl;
  }
}

void bfs(Board board)
{
  unordered_map<int, bool> checkDup;
  queue<Board> bfsQueue;
  int nodeCount = 1;
  bool hasSolution = false;
  Board solution;

  bfsQueue.push(board);
  checkDup[board.encode()] = true;

  while (!bfsQueue.empty())
  {
    Board frontBoard = bfsQueue.front();
    bfsQueue.pop();
    nodeCount++;

    if (frontBoard.solved())
    {
      hasSolution = true;
      solution = frontBoard;
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
            bfsQueue.push(newBoard);
          }
        }
      }
    }
  }

  if (hasSolution)
  {
    solution.printBoard();
    solution.printMoves();
  }
  else
  {
    cout << "Solution Does Not Exist!" << endl;
  }
  cout << "Nodes visited: " << nodeCount << endl;
}

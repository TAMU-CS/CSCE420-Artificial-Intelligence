#include <iostream>
#include <vector>
#include <queue>
#include <utility>
#include <unordered_map>
using namespace std;

enum Move
{
  UP,
  DOWN,
  LEFT,
  RIGHT
};

vector<string> moveToString{"UP", "DOWN", "LEFT", "RIGHT"};

class Board
{
  vector<vector<int>> state;
  pair<int, int> zeroPos;

  pair<int, int> getZeroPosition()
  {
    for (int i = 0; i < 3; i++)
    {
      for (int j = 0; j < 3; j++)
      {
        if (state[i][j] == 0)
        {
          return make_pair(i, j);
        }
      }
    }
    throw "Invalid Board: Zero not found!";
  }

public:
  static const vector<int> solutionState;
  static const vector<pair<int, int>> moveOffset;

  Board(vector<int> initialState)
  {
    state = vector<vector<int>>(3, vector<int>(3, 0));

    for (int i = 0; i < 3; i++)
    {
      for (int j = 0; j < 3; j++)
      {
        state[i][j] = initialState[i * 3 + j];
      }
    }

    zeroPos = getZeroPosition();
  }

  bool canMove(Move direction)
  {
    pair<int, int> move = moveOffset[direction];
    int x = move.first + zeroPos.first;
    int y = move.second + zeroPos.second;

    return x < 3 && x >= 0 && y < 3 && y >= 0;
  }

  void move(Move direction)
  {
    pair<int, int> move = moveOffset[direction];
    pair<int, int> newPos = make_pair(zeroPos.first + move.first, zeroPos.second + move.second);
    state[zeroPos.first][zeroPos.second] = state[newPos.first][newPos.second];
    state[newPos.first][newPos.second] = 0;
    zeroPos = newPos;
  }

  void operator=(const Board &b)
  {
    state = vector<vector<int>>(3, vector<int>(3, 0));

    for (int i = 0; i < 3; i++)
    {
      for (int j = 0; j < 3; j++)
      {
        state[i][j] = b.state[i][j];
      }
    }

    zeroPos = b.zeroPos;
  }

  int encode()
  {
    int sum = 0;
    int multipleOffset = 1;
    for (int i = 0; i < 3; i++)
    {
      for (int j = 0; j < 3; j++)
      {
        sum += state[i][j] * multipleOffset;
        multipleOffset *= 10;
      }
    }
    return sum;
  }

  int encodeWithDepth(int depth){
    int sum = encode();
    return sum + depth * 1000000000;
  }

  void printBoard()
  {
    for (int i = 0; i < 3; i++)
    {
      cout << "|";
      for (int j = 0; j < 3; j++)
      {
        cout << state[i][j] << "|";
      }

      cout << endl;
    }
  }

  bool solved()
  {
    for (int i = 0; i < 3; i++)
    {
      for (int j = 0; j < 3; j++)
      {
        if (state[i][j] != solutionState[i * 3 + j])
        {
          return false;
        }
      }
    }
    return true;
  }
};

const vector<int> Board::solutionState = vector<int>{1, 2, 3, 8, 0, 4, 7, 6, 5};
const vector<pair<int, int>> Board::moveOffset = vector<pair<int, int>>{make_pair(-1, 0), make_pair(1, 0), make_pair(0, -1), make_pair(0, 1)};

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
    cout << moveToString[solution[i]] << " ";
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
      cout << moveToString[solution[i]] << " ";
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
    cout << moveToString[solution[i]] << " ";
    //board.printBoard();
  }
  cout << endl;
}

int main()
{

  vector<int> hard{5, 6, 7, 4, 0, 8, 3, 2, 1};
  vector<int> med{2, 8, 1, 0, 4, 3, 7, 6, 5}; //2 8 1 0 4 3 7 6 5
  Board board(med);
  //bfs(board);
  dfs(board);
  return 0;
}

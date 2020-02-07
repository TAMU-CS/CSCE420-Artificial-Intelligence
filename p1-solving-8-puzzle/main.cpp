#include <iostream>
#include <vector>
#include <queue>
#include <utility>
#include <unordered_map>
using namespace std;

enum Move
{
  LEFT,
  UP,
  RIGHT,
  DOWN
};

vector<string> moveToString{"LEFT", "UP", "RIGHT", "DOWN"};

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
const vector<pair<int, int>> Board::moveOffset = vector<pair<int, int>>{make_pair(0, -1), make_pair(-1, 0), make_pair(0, 1), make_pair(1, 0)};

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
            nodeCount++;
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

int main()
{
  vector<int> initialState{5, 6, 7, 4, 0, 8, 3, 2, 1};
  Board board(initialState);
  bfs(board);
  return 0;
}

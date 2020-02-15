#include "board.h"
using namespace std;

const vector<int> Board::solutionState = vector<int>{1, 2, 3, 8, 0, 4, 7, 6, 5};
const vector<pair<int, int>> Board::moveOffset = vector<pair<int, int>>{make_pair(-1, 0), make_pair(1, 0), make_pair(0, -1), make_pair(0, 1)};

pair<int, int> Board::getZeroPosition()
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

pair<int, int> Board::getPosition(int val){
  for (int i = 0; i < 3; i++)
  {
    for (int j = 0; j < 3; j++)
    {
      if (state[i][j] == val)
      {
        return make_pair(i, j);
      }
    }
  }
  throw "Could not find position for value: " + to_string(val);
}

Board::Board(vector<int> initialState)
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

bool Board::canMove(Move direction)
{
  pair<int, int> move = moveOffset[direction];
  int x = move.first + zeroPos.first;
  int y = move.second + zeroPos.second;

  return x < 3 && x >= 0 && y < 3 && y >= 0;
}

void Board::move(Move direction)
{
  pair<int, int> move = moveOffset[direction];
  pair<int, int> newPos = make_pair(zeroPos.first + move.first, zeroPos.second + move.second);
  state[zeroPos.first][zeroPos.second] = state[newPos.first][newPos.second];
  state[newPos.first][newPos.second] = 0;
  zeroPos = newPos;
}

void Board::operator=(const Board &b)
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

int Board::encode()
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

int Board::encodeWithDepth(int depth)
{
  int sum = encode();
  return sum + depth * 1000000000;
}

int Board::numTilesOutOfPlace(){
  int num = 0;
  for(int i = 0; i < 3; i++){
    for(int j = 0; j < 3; j++){
      if(solutionState[i * 3 + j] != state[i][j]){
        num++;
      }
    }
  }
  return num;
}

int Board::manhattanDistance(){
  int totalDist = 0;
  for(int i = 0; i < 3; i++){
    for(int j = 0; j < 3; j++){
      pair<int, int> actualPosition = getPosition(solutionState[i * 3 + j]);
      totalDist += (abs(i - actualPosition.first) + abs(j - actualPosition.second));
    }
  }
  return totalDist;
}


void Board::printBoard()
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

bool Board::solved()
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
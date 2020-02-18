#include "main.h"
#include "board.h"
#include "search.h"
#include "tree.h"
#include "minmax.h"
using namespace std;

string getCommand(string input);
string getList(string input);
string getHeuristic(string input);

int main()
{
  vector<int> dfsSolved{1, 2, 3, 8, 6, 4, 7, 0, 5};
  vector<int> easy{1, 3, 4, 8, 6, 2, 7, 0, 5};
  vector<int> med{2, 8, 1, 0, 4, 3, 7, 6, 5};
  vector<int> hard{5, 6, 7, 4, 0, 8, 3, 2, 1};
  Board board(easy);

  string input;
  cout << "Type or paste input and then hit ENTER.\n";
  cout << "Ex: (greedy '(1 2 3 4 5 6 7 8 0) 'h1)\n";
  cout << "Ex: (min-max '(1 (5 7) 4))\n";
  getline(cin, input);

  input = input.substr(1, input.size() - 2);
  string command = getCommand(input);
  string list = getList(input);
  string heuristic = getHeuristic(input);

  if (command == "dfs")
  {
    dfs(getBoardFromString(list));
  }
  else if (command == "bfs")
  {
    bfs(getBoardFromString(list));
  }
  else if (command == "ids")
  {
    ids(getBoardFromString(list));
  }
  else if (command == "greedy")
  {
    if (heuristic == "h1")
    {
      greedyBestFirst<BFSBoardCompareTilesOutOfPlace>(getBoardFromString(list));
    }
    else
    {
      greedyBestFirst<BFSBoardCompareManhattan>(getBoardFromString(list));
    }
  }
  else if (command == "astar")
  {
    if (heuristic == "h1")
    {
      astar<BFSBoardCompareTilesOutOfPlace>(getBoardFromString(list));
    }
    else
    {
      astar<BFSBoardCompareManhattan>(getBoardFromString(list));
    }    
  }else if (command == "min-max"){
    minmax(makeTree(list));
  }

  return 0;
}

string getCommand(string input)
{
  for (int i = 0; i < input.size(); i++)
  {
    if (input[i] == ' ')
    {
      return input.substr(0, i);
    }
  }
}

string getList(string input)
{
  int startList = 0;
  for (int i = 0; i < input.size(); i++)
  {
    if (input[i] == '\'')
    {
      startList = i;
      break;
    }
  }

  int leftPCount = 1;
  int i = startList + 2;
  while (leftPCount > 0 && i < input.size())
  {
    if (input[i] == '(')
    {
      leftPCount++;
    }
    else if (input[i] == ')')
    {
      leftPCount--;
    }
    i++;
  }
  return input.substr(startList + 1, i - startList);
}

string getHeuristic(string input)
{
  int startInd = 0;
  int count = 2;
  for (int i = 0; i < input.size(); i++)
  {
    if (input[i] == '\'')
    {
      count--;

      if (count == 0)
      {
        startInd = i;
        break;
      }
    }
  }

  if (count > 0)
  {
    return "";
  }

  return input.substr(startInd + 1, input.size());
}
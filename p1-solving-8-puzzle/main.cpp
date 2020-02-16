#include "main.h"
#include "board.h"
#include "search.h"
using namespace std;

int main()
{
  vector<int> dfsSolved{1, 2, 3, 8, 6, 4, 7, 0, 5};
  vector<int> easy{1, 3, 4, 8, 6, 2, 7, 0, 5};
  vector<int> med{2, 8, 1, 0, 4, 3, 7, 6, 5};
  vector<int> hard{5, 6, 7, 4, 0, 8, 3, 2, 1};
  Board board(easy);

  //bfs(board);

  // int opt;
  // while(true){
  //   int puzzleType;
  //   cout << "Enter 1-easy, 2-medium, 3-hard: ";
  //   cin >> puzzleType;

  // }
  astar(hard);
  return 0;
}

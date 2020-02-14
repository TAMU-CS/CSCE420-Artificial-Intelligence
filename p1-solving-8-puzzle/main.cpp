#include "main.h"
#include "board.h"
#include "search.h"
using namespace std;

int main()
{

  vector<int> hard{5, 6, 7, 4, 0, 8, 3, 2, 1};
  vector<int> med{2, 8, 1, 0, 4, 3, 7, 6, 5}; //2 8 1 0 4 3 7 6 5
  Board board(med);
  //bfs(board);
  bfs(board);
  return 0;
}

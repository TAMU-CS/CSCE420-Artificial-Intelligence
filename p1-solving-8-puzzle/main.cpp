#include "main.h"
#include "board.h"
#include "search.h"
#include "tree.h"
#include "minmax.h"
using namespace std;

int main()
{
  vector<int> dfsSolved{1, 2, 3, 8, 6, 4, 7, 0, 5};
  vector<int> easy{1, 3, 4, 8, 6, 2, 7, 0, 5};
  vector<int> med{2, 8, 1, 0, 4, 3, 7, 6, 5};
  vector<int> hard{5, 6, 7, 4, 0, 8, 3, 2, 1};
  Board board(easy);

  string input;
  // cout << "Input [search type] [list] [heuristic].\n";
  // cout << "Example: greedy '(1 2 3 4 5 6 7 8 0) 'h1\n";
  // cin >> input;

  Node* root = makeTree("((8 (7 9 8) 4) (((3 6 4) 2 1) ((6 2 9) 4 7 (6 4 5))))");
  printTree(root);
  minmax(root);
  return 0;
}

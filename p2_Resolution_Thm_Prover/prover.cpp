#include "prover.h"
using namespace std;

int main()
{
  vector<Clause> clauses = {
      Clause("(1 ((howl z)) ((hound z)))"),
      Clause("(2 nil ((have x y) (cat y) (have x z) (mouse z)))"),
      Clause("(3 nil ((ls w) (have w v) (howl v)))"),
      Clause("(4 ((have (john) (a))) nil)"),
      Clause("(5 ((cat (a)) (hound (a))) nil)"),
      Clause("(6 ((mouse (b))) nil)"),
      Clause("(7 ((ls (john))) nil)"),
      Clause("(8 ((have (john) (b))) nil)"),
  };
  for(int i = 0; i < clauses.size(); i++)
    cout << "clause" << i << "\n" << clauses[i];

  // Constant c("test");
  // cout << c.name << endl;

  return 0;
}

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

  resolve(clauses);
  return 0;
}

void resolve(vector<Clause> clauses)
{
  for (int i = 0; i < clauses.size(); i++)
  {
    for (int j = i + 1; j < clauses.size(); j++)
    {
      for (int l1 = 0; l1 < clauses[i].pos.size(); l1++)
      {
        for (int l2 = 0; l2 < clauses[j].neg.size(); l2++)
        {
          // make deep copys of clauses[i] and clauses[j] for c1 and c2
          Clause c1(clauses[i].value);
          Clause c2(clauses[j].value);
          try
          {
            unordered_map<string, Unifiable *> sub = Literal::unify(c1.pos[l1].root, c2.neg[l2].root);

            // delete l1 and l2
            c1.pos.erase(c1.pos.begin() + l1);
            c2.neg.erase(c2.neg.begin() + l2);

            //apply substitution on both c1 and c2
            c1.substitute(sub);
            c2.substitute(sub);

            //combine the two clauses
            c1.add(c2);

            if (c1.pos.size() == 0 && c1.neg.size() == 0)
            {
              cout << "FALSE when resolving: " << endl;
              cout << clauses[i].value << " and " << clauses[j].value << endl;
              return;
            }

            c1.num = clauses.size();
            clauses.push_back(c1);
            cout << c1 << endl;
          }
          catch (int errCode)
          {
          }
        }
      }

      for (int l1 = 0; l1 < clauses[i].neg.size(); l1++)
      {
        for (int l2 = 0; l2 < clauses[j].pos.size(); l2++)
        {
          // make deep copys of clauses[i] and clauses[j] for c1 and c2
          Clause c1(clauses[i].value);
          Clause c2(clauses[j].value);
          try
          {
            unordered_map<string, Unifiable *> sub = Literal::unify(c1.neg[l1].root, c2.pos[l2].root);

            // delete l1 and l2
            c1.neg.erase(c1.neg.begin() + l1);
            c2.pos.erase(c2.pos.begin() + l2);

            //apply substitution on both c1 and c2
            c1.substitute(sub);
            c2.substitute(sub);

            //combine the two clauses
            c1.add(c2);

            if (c1.pos.size() == 0 && c1.neg.size() == 0)
            {
              cout << "FALSE when resolving: " << endl;
              cout << c1 << " and " << c2 << endl;
              return;
            }

            c1.num = clauses.size();
            clauses.push_back(c1);
            cout << c1 << endl;
          }
          catch (int errCode)
          {
          }
        }
      }
    }
  }
}

//Clause("(1 ((howl v2)) ((hound v2)))"),
//Clause("(3 nil ((ls w1) (have w1 v2) (howl v2)))"),
// subs = (z0 | v2)
// l1 and l2 are unifiable

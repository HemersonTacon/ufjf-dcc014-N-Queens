#include <iostream>
#include "State.h"
#include "SearchTree.h"
using namespace std;

void test()
{
    State* s = new State(4);
    SearchTree *tree = new SearchTree(s);
    s->setQueen(0, 1);
    s->setQueen(1, 3);
    s->setQueen(2, 0);
    s->setQueen(3, 2);
    std::vector<State*> path = tree->backTracking();
    for(auto it = path.begin(); it != path.end(); ++it)
        (*it)->printTable();

    //cout << s->countConflicts() << endl;


    delete s;
}

int main()
{
    test();

    return 0;
}

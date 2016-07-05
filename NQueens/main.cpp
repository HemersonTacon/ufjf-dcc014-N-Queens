#include <iostream>
#include "State.h"

using namespace std;

void test()
{
    State* s = new State(4);

    s->setQueen(0, 0);
    s->setQueen(1, 1);
    s->setQueen(2, 2);
    s->setQueen(3, 3);

    //cout << s->countConflicts() << endl;

    s->makeChildren(3);
    delete s;
}

int main()
{
    test();

    return 0;
}

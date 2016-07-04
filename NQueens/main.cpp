#include <iostream>
#include "State.h"

using namespace std;

void test()
{
    State* s = new State(4);

    s->table[0] = 0;
    s->table[1] = 1;
    s->table[2] = 2;
    s->table[3] = 3;

    //cout << s->countConflicts() << endl;

    s->makeChildren();
}

int main()
{
    test();

    return 0;
}

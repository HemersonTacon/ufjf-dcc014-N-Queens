#include <stdlib.h>
#include "State.h"
#include <iostream>

State::State(int n)
{
    this->n = n;
    table = new int[n];

    for (int i = 0; i < n; ++i) table[i] = -1;
}

int State::countConflicts()
{
    int count = 0;

    for (int i = 0; i < n; ++i)
        for (int j = i + 1; j < n; ++j)
            if (table[i] == table[j] || j - i == abs(table[j] - table[i]))
                count++;

    return count;
}

void State::makeChildren()
{
    int childrenCount = n * (n-1), x;

    x = 0;

    children = new State*[childrenCount];

    for (int i = 0; i < n; ++i)
        for (int j = 1; j < n; ++j)
            children[x++] = makeChild(i, j);

}

State* State::makeChild(int pos, int r)
{
    State* child = new State(n);

    for (int i = 0; i < n; ++i)
        child->table[i] = table[i];

    child->table[pos] = (child->table[pos] + r) % n;
    child->printTable();

    return child;
}

void State::printTable()
{
    for(int i = 0; i < n; i++)
        std::cout<<this->table[i]<<" ";

    std::cout<<std::endl;
}

State::~State()
{
    //dtor
}

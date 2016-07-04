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

State* State::makeChild(int line, int r)
{
    State* child = new State(n);

    for (int i = 0; i < n; ++i)
        child->setQueen(i, table[i]);

    child->setQueen(line, (child->getQueenAt(line) + r) % n);
    child->printTable();

    return child;
}

void State::printTable()
{
    for(int i = 0; i < n; ++i)
        std::cout<< table[i] << " ";

    std::cout << std::endl;
}

void State::setQueen(int line, int column)
{
    table[line] = column;
}

int State::getQueenAt(int line)
{
    return table[line];
}

State::~State()
{
    //dtor
}

#include <stdlib.h>
#include "State.h"
#include <iostream>

State::State(int n)
{
    this->n = n;
    table = new int[n];
    children = NULL;
    parent = NULL;
    child_count = 0;
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

void State::makeChildren(int moves)
{
    moves = moves % n;
    int childrenCount = n * moves, x;

    x = 0;

    children = new State*[childrenCount];

    for (int i = 0; i < n; ++i)
        for (int j = 1; j <= moves; ++j)
            children[x++] = makeChild(i, j);

    this->child_count = x;
}

State* State::makeChild(int line, int r)
{
    State* child = new State(n);
    child->setParent(this);
    for (int i = 0; i < n; ++i)
        child->setQueen(i, table[i]);

    child->setQueen(line, (child->getQueenAt(line) + r) % n);
    child->printTable();

    return child;
}

void State::setParent(State* parent)
{
    this->parent = parent;
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
State* State::getParent()
{
    return this->parent;
}

State::~State()
{
    if(children != NULL){
        for(int i = 0; i < child_count; i++)
            delete children[i];


        delete []children;
    }
    delete []table;

    //delete children;
}
bool State::hasCycle()
{

}

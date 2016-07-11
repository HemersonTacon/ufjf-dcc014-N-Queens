#include <stdlib.h>
#include "State.h"
#include <iostream>

State::State(int n)
{
    this->n = n;
    last_visited = -1;
    table = new int[n];
    children = NULL;
    parent = NULL;
    child_count = 0;
    size_children = 0;
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
    this->size_children = childrenCount;

    x = 0;
    childrenCount = this->size_children;

    children = new State*[childrenCount];

    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j){
            if(i != j)
                //children[x++] = makeChild(i, j);
                children[++x] = makeChildAlternative(i,j);
        }



    //this->child_count = x;
}

State* State::makeChild(int line, int r)
{
    State* child = new State(n);
    child->setParent(this);
    for (int i = 0; i < n; ++i)
        child->setQueen(i, table[i]);

    child->setQueen(line, (child->getQueenAt(line) + r) % n);
    if(child->hasCycle()){
        delete child;
        child = NULL;
        this->child_count = this->child_count - 1;
        return child;
    }
    //child->printTable();

    return child;
}
State* State::makeChildAlternative(int i, int j)
{
    State* child = new State(n);
    child->setParent(this);
    for (int x = 0; x < n; ++x)
        child->setQueen(x, table[x]);

    if(i != j){
        child->setQueen(i,  table[j]);
        child->setQueen(j, table[i]);
    }
    if(child->hasCycle()){
        delete child;
        child = NULL;
        this->child_count = this->child_count - 1;
        return child;
    }

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
        for(int i = 0; i < n*n ; i++){
            if( children[i] != NULL)
                delete children[i];
        }


        delete []children;
    }
    delete []table;

    //delete children;
}
bool State::hasCycle()
{
    State *p = NULL;
    p = this->parent;
    if(isEqual(p)) return true;
    while(p->getParent() != NULL){
        if(isEqual(p))
            return true;
        p = p->getParent();
    }
    return false;
}
bool State::isEqual(State* parent)
{
    int *parent_table = parent->getTable();
    for(int  i = 0; i < n; i++){
        if(this->table[i] != parent_table[i])
            return false;
    }
    return true;
}
int* State::getTable()
{
    return this->table;
}

void State::setVisited(int val)
{
    this->last_visited = val;
}

int State::getVisited()
{
    return this->last_visited;
}
State* State::getChild(int i)
{
    return this->children[i];
}
int State::getSizeChildren()
{
    return this->size_children;
}

void State::setChild(int pos, State* child)
{
    this->children[pos] = child;
}

void State::setChildren(State** children)
{
    this->children = children;
}
int State::getChildCountValids()
{
    return this->child_count;
}

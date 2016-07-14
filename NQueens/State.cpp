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
    f = 0;
    last_i = 0;
    last_j = 0;
    child_count = 0;
    size_children = 0;
    cost = 0;
    children = new State*[(n*(n-1))/2];
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
    int childrenCount = ((n)*(n - 1))/2;
    this->size_children = childrenCount;

    int x = 0;
    child_count = this->size_children;

    //children = new State*[childrenCount];
    for(int i = 0 ; i < childrenCount; ++i)
        children[i] = NULL;

    for (int i = 0; i < n-1; ++i)
        for (int j = i + 1; j < n ; ++j){
                //children[x++] = makeChild(i, j);
                children[x++] = makeChildAlternative(i,j);
        }
    //if(child_count == 0) delete []children;
    std::cout<<"child count : " <<child_count<<std::endl;



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
   //std::cout<<"child count : " <<child_count<<std::endl;

    if(this->child_count > 0){
        for(int i = 0; i < (n*(n-1))/2; i++){
            if(children[i] != NULL)
                delete children[i];
        }



    }
    delete []children;
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
void State::setCost(int cost)
{
    this->cost  =  cost;
}

int State::getCost()
{
    return this->cost;
}
void State::setHeuristic(int h)
{
    this->heuristic = h;
}

int State::getHeuristic()
{
    return this->heuristic;
}
void State::setF(int f)
{
    this->f = f;
}

int State::getF()
{
    return this->f;
}
int State::getLast_i()
{
    return this->last_i;
}

int State::getLast_j()
{
    return this->last_j;
}

void State::setLast_i(int i)
{
    this->last_i = i;
}

void State::setLast_j(int j)
{
    this->last_j = j;
}
void State::upadateOp()
{

    last_j = last_j + 1 + (((last_j + 1) % n)  == 0 ? ((last_j + 1) / n) + 1 : 0);
    last_i = last_j / n;

}
void State::setChildCountValids(int i)
{
    this->child_count = i;
}

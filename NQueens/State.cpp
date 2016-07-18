#include <stdlib.h>
#include "State.h"
#include <iostream>

State::State(int n, int depth, int heuristicFunction)
{
    this->n = n;
    this->depth = depth;
    this->heuristicFunction = heuristicFunction;

    cost = heuristicValue = f = childCount = 0;
    childGen_i = 0;
    childGen_j = 1;
    board = new int[n];
    parent = nullptr;
    children = new State*[(n*(n-1))/2];

    for (int i = 0; i < n; ++i) board[i] = -1;
}

State::~State()
{
    for (int i = 0; i < childCount; ++i)
        delete children[i];

    delete []children;
    delete []board;
}

void State::printBoard()
{
    for(int i = 0; i < n; ++i)
        std::cout<< board[i] << " ";

    std::cout << std::endl;
}

void State::clearChildren()
{
    for(int i = 0; i < childCount; ++i)
        delete children[i];

    childCount = childGen_i = 0;
    childGen_j = 1;
}

void State::updateCost()
{
    cost = parent->getCost() + 1;
}

void State::updateHeuristicValue()
{
    switch(heuristicFunction)
    {
        case 1:
            heuristicValue = countConflicts();
            break;
        default:
            heuristicValue = 0;
    }
}

void State::updateF()
{
    f = cost + heuristicValue;
}

bool State::hasCycle()
{
    State *p = this->parent;

    if(equals(p)) return true;

    while(p->getParent() != nullptr){
        if(equals(p))
            return true;
        p = p->getParent();
    }
    return false;
}

int State::countConflicts()
{
    int count = 0;

    for (int i = 0; i < n; ++i)
        for (int j = i + 1; j < n; ++j)
            if (j - i == abs(board[j] - board[i]))
                count++;

    return count;
}

int State::makeChildren()
{
    State* newState;

    for (int i = 0; i < n-1; ++i)
        for (int j = i + 1; j < n ; ++j)
        {
            newState = makeChild(i, j);

            if (newState != nullptr)
                children[childCount++] = newState;
        }

    for (int i = childCount; i < n*(n-1)/2; ++i)
        children[i] = nullptr;

    return childCount;
}

State* State::makeChild(int i, int j)
{
    State* child = new State(n, depth + 1, heuristicFunction);

    for (int x = 0; x < n; ++x)
        child->setQueen(x, board[x]);

    child->setParent(this);
    child->setQueen(i, board[j]);
    child->setQueen(j, board[i]);

    if(child->hasCycle()) {
        delete child;
        child = nullptr;
    } else {
        child->updateCost();
        child->updateHeuristicValue();
        child->updateF();
    }

    return child;
}

State* State::makeNextChild()
{
    State* newState;

    for (; childGen_i < n-1; ++childGen_i, childGen_j = childGen_i + 1)
        for (; childGen_j < n; ++childGen_j)
        {
            newState = makeChild(childGen_i, childGen_j);

            if (newState != nullptr)
            {
                children[childCount++] = newState;

                ++childGen_j;

                return newState;
            }
        }

    return nullptr;
}

// getters and setters

void State::setQueen(int line, int column)
{
    board[line] = column;
}

void State::setParent(State* parent)
{
    this->parent = parent;
}

int State::getCost()
{
    return this->cost;
}

int State::getHeuristicValue()
{
    return this->heuristicValue;
}

int State::getF()
{
    return this->f;
}

int State::getDepth()
{
    return depth;
}

int State::getQueenAt(int line)
{
    return board[line];
}

int* State::getBoard()
{
    return this->board;
}

State* State::getParent()
{
    return this->parent;
}

State* State::getChild(int i)
{
    return this->children[i];
}

// private methods

bool State::equals(State* parent)
{
    int *parent_table = parent->getBoard();
    for(int  i = 0; i < n; i++){
        if(this->board[i] != parent_table[i])
            return false;
    }
    return true;
}

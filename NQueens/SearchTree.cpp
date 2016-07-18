#include "SearchTree.h"
#include <stack>
#include <queue>
#include <list>
#include "Utils.h"
#include <vector>
#include <algorithm>
#include <iostream>
#include <chrono>

SearchTree::SearchTree(int n, int heuristicFunction)
{
    this->n = n;
    this->visited = 0;
    this->expanded = 0;
    this->searchExecutionTime = 0;
    this->root = new State(n, 0, heuristicFunction);

    for (int i = 0; i < n; ++i) root->setQueen(i, i);

    root->updateHeuristicValue();
    root->updateF();
}

SearchTree::~SearchTree()
{
    delete root;
}

void SearchTree::printStats()
{
    if (visited == 0)
    {
        std::cout << "Call \"doSearch(int opt)\" to get stats." << std::endl;
        return;
    }

    std::cout << "Executed search in " << searchExecutionTime << " seconds [CPU Clock]" << std::endl;
    std::cout << "Statistics: " << std::endl;
    std::cout << "Solution depth: " << solution->getDepth() << std::endl;
    std::cout << "Solution cost: " << solution->getCost() << std::endl;
    std::cout << "Expanded nodes: " << expanded << std::endl;
    std::cout << "Visited nodes: " << visited << std::endl;
    std::cout << "Average branching factor: " << (double) expanded/visited << std::endl;
}

std::vector<State*> SearchTree::doSearch(int opc)
{
    std::clock_t startCpuTime = std::clock();

    switch(opc){
        case 1:
            solution = backTracking(root);
            break;
        case 2:
            solution = depthFirstSearch(5 * n); // limite de profundidade fixo
            break;
        case 3:
            solution = breadthFirstSearch();
            break;
        case 4:
            solution = orderSearch();
            break;
        case 5:
            solution = greedy();
            break;
        case 6:
            solution = AStar();
            break;
        case 7:
            solution = IDAStar();
            break;
    }

    searchExecutionTime = (std::clock() - startCpuTime) / (double)CLOCKS_PER_SEC;

    return getPathTo(solution);
}

std::vector<State*> SearchTree::getPathTo(State* solution)
{
    State *current = solution;
    std::vector<State*> path;

    while(current != nullptr){
        path.insert(path.begin(), current);
        current = current->getParent();
    }

    return path;
}

State* SearchTree::backTracking(State* root)
{
    ++visited;

    if(root->countConflicts() == 0)
        return root;

    State *child;

    while ((child = root->makeNextChild()) && child != nullptr)
    {
        ++expanded;

        child = backTracking(child);

        if (child != nullptr)
            return child;
    }

    return nullptr;
}

State* SearchTree::depthFirstSearch(int depthLimit){
    int childrenCount;
    std::stack<State*> s;
    State* current;

    s.push(root);

    while (!s.empty() && (current = s.top()) && ++visited && current->countConflicts() > 0)
    {
        s.pop();

        if (current->getDepth() < depthLimit)
        {
            childrenCount = current->makeChildren();

            expanded += childrenCount;

            for(int i = 0; i < childrenCount; ++i)
                s.push(current->getChild(i));
        }
    }

    return (!s.empty()) ? current : nullptr;
}

State* SearchTree::breadthFirstSearch()
{
    int childrenCount;
    std::queue<State*> q;
    State* current = root;

    q.push(root);

    while (!q.empty() && (current = q.front()) && ++visited && current->countConflicts() > 0)
    {
        q.pop();
        childrenCount = current->makeChildren();

        expanded += childrenCount;

        for(int i = 0; i < childrenCount; ++i)
            q.push(current->getChild(i));
    }

    return (!q.empty()) ? current : nullptr;
}

State* SearchTree::bestFirstSearch(bool (*comparator)(State*, State*))
{
    int childrenCount;
    std::vector<State*> open;
    State* current;

    open.push_back(root);

    while (!open.empty() && ( current = *(open.begin()) ) && ++visited && current->countConflicts() > 0)
    {
        open.erase(open.begin());
        childrenCount = current->makeChildren();

        expanded += childrenCount;

        for (int i = 0; i < childrenCount; ++i)
            open.push_back(current->getChild(i));

        std::sort(open.begin(), open.end(), comparator);
    }

    return (!open.empty()) ? current : nullptr;
}

State* SearchTree::orderSearch()
{
    return bestFirstSearch(comparator);
}

State* SearchTree::greedy()
{
    return bestFirstSearch(comparator2);
}

State* SearchTree::AStar()
{
    return bestFirstSearch(comparator3);
}

State* SearchTree::IDAStar()
{
    std::list<int> closed;
    int patamar = 0, patamar_old = -1;
    State* current = root;
    State* child = nullptr;

    visited = 1; // Raiz já é considerada visitada
    patamar = current->getF();

    while(current->countConflicts() > 0 || current->getF() > patamar){
        if(patamar == patamar_old)
            return nullptr;
        else{
            if(current->getF() > patamar){
                closed.push_back(current->getF());
                current = current->getParent();
            }

            child = current->makeNextChild();

            if (child != nullptr)
            {
                current = child;
                ++expanded;
                ++visited;
            }
            else if (current == root)
            {
                patamar_old = patamar;
                patamar = findMin(closed);

                current->clearChildren();
                closed.clear();
            }
            else
                current = current->getParent();
        }

    }

    return (patamar >= patamar_old) ? current : nullptr;
}

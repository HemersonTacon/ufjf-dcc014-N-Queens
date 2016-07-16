#include "SearchTree.h"
#include <stack>
#include <queue>
#include <list>
#include "Utils.h"
#include <vector>
#include <algorithm>
#include <iostream>
#include <chrono>

SearchTree::SearchTree(int n)
{
    this->n = n;
    this->visited = 0;
    this->expanded = 0;
    this->cpuDuration = 0;
    this->root = new State(n, 0);

    for (int i = 0; i < n; ++i) root->setQueen(i, i);
//    for(int i = 0; i < (n*(n-1))/2; i++){
//        root->upadateOp();
//        std::cout<<"i: "<<root->getLast_i()<<" Last_j: "<<root->getLast_j()%n<<std::endl;
//    }
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

    std::cout << "Executed search in " << cpuDuration << " seconds [CPU Clock]" << std::endl;
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
            solution = depthFirstSearch();
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

    cpuDuration = (std::clock() - startCpuTime) / (double)CLOCKS_PER_SEC;

    return getPathTo(solution);
}

std::vector<State*> SearchTree::getPathTo(State* solution)
{
    State *current = solution;
    std::vector<State*> path;

    while(current != NULL){
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

    int x = 0;
    State *current, *child;

    for (int i = 0; i < n-1; ++i) {
        for (int j = i + 1; j < n; ++j) {
            child = root->makeChildPermutation(i,j);
            if(child != NULL){
                ++expanded;
                root->setChild(x, child);
                current = backTracking(child);

                if(current != NULL)
                    return current;
            }
            ++x;
        }
    }

    return nullptr;
}

State* SearchTree::depthFirstSearch(){
    int childrenCount;
    std::stack<State*> s;
    State* current;

    s.push(root);

    visited = expanded = 0;

    while (!s.empty() && (current = s.top()) && ++visited && current->countConflicts() > 0)
    {
        s.pop();
        childrenCount = current->makeChildren();

        expanded += childrenCount;

        for(int i = 0; i < childrenCount; ++i)
            s.push(current->getChild(i));
    }

    return (!s.empty()) ? current : nullptr;
}

State* SearchTree::breadthFirstSearch()
{
    int childrenCount;
    std::queue<State*> q;
    State* current = root;

    q.push(root);

    visited = expanded = 0;

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

State* SearchTree::orderSearch()
{
    int childrenCount;
    std::vector<State*> open;
    State* current;

    root->setCost(0);
    open.push_back(root);

    while (!open.empty() && ( current = *(open.begin()) ) && ++visited && current->countConflicts() > 0)
    {
        open.erase(open.begin());
        childrenCount = current->makeChildren();

        expanded += childrenCount;

        for (int i = 0; i < childrenCount; ++i) {
            current->getChild(i)->setCost(current->getCost() + 1);
            open.push_back(current->getChild(i));
        }

        std::sort(open.begin(), open.end(), comparator);
    }

    return (!open.empty()) ? current : nullptr;
}

State* SearchTree::greedy()
{
    int childrenCount;
    std::vector<State*> open;
    State* current = root;

    root->setHeuristic(root->countConflicts());
    open.push_back(root);

    while (!open.empty() && ( current = *(open.begin()) ) && ++visited && current->countConflicts() > 0)
    {
        open.erase(open.begin());
        childrenCount = current->makeChildren();

        expanded += childrenCount;

        for(int i = 0; i < childrenCount; ++i){
            current->getChild(i)->setHeuristic(current->getChild(i)->countConflicts());
            open.push_back(current->getChild(i));
        }

        std::sort(open.begin(), open.end(), comparator2);
    }

    return (!open.empty()) ? current : nullptr;
}

State* SearchTree::AStar()
{
    int childrenCount;
    std::vector<State*> open;
    State* current = root;

    root->setCost(0);
    root->setHeuristic(root->countConflicts());
    root->setF(root->getCost() + root->getHeuristic());
    open.push_back(root);

    while (!open.empty() && ( current = *(open.begin()) ) && ++visited && current->countConflicts() > 0)
    {
        open.erase(open.begin());
        childrenCount = current->makeChildren();

        expanded += childrenCount;

        for(int i = 0; i < childrenCount; ++i){
            current->getChild(i)->setCost(current->getCost() + 1);
            current->getChild(i)->setHeuristic(current->countConflicts());
            current->getChild(i)->setF(current->getChild(i)->getCost() + current->getChild(i)->getHeuristic());
            open.push_back(current->getChild(i));
        }

        std::sort(open.begin(), open.end(), comparator3);
    }

    return (!open.empty()) ? current : nullptr;
}

State* SearchTree::IDAStar()
{
    std::list<int> closed;
    int patamar = 0, patamar_old = -1;
    State* current = root;
    State* child = NULL;
    current->setF(current->countConflicts());
    patamar = current->getF();

    while(current->countConflicts() > 0 || current->getF() > patamar){
        if(patamar == patamar_old)
            return NULL;
        else{
            if(current->getF() > patamar){
                closed.push_back(current->getF());
                current = current->getParent();
            }
            current->upadateOp();
            if(current->getLast_i() < n - 1){
                child = current->makeChildPermutation(current->getLast_i(), current->getLast_j()%n);
                if(child != NULL){
                    child->setCost(current->getCost() + 1);
                    child->setF(child->getCost() + child->countConflicts());
                    current = child;
                }
            }else{
                if(current == root){
                    patamar_old = patamar;
                    patamar = findMin(closed);
                    for(int i = 0; i < (n*(n-1))/2; ++i){
                        if(current->getChild(i) != NULL)
                            delete current->getChild(i);
                    }
                    current->setChildCountValids(0);
                    current->setLast_i(0);
                    current->setLast_j(0);
                    closed.clear();
                }else{
                    current = current->getParent();
                }
            }
        }

    }

    return (patamar >= patamar_old) ? current : nullptr;
}

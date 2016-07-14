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
    State* current = root;
    if(current->countConflicts() == 0){
        return current;
    }
    int  x = 0;

    //current->setChildren(new State*[childrenCount]);

    State* child = NULL;
    for (int i = 0; i < n-1 ; ++i){
        for (int j = i + 1  ; j < n ; ++j){
            child = current->makeChildAlternative(i,j);
            if(child != NULL){
                current->setChild(x++, child);
                current = backTracking(child);
                if(current != NULL)
                    return current;
            }else{
                ++x;
            }
        }
    }
    return nullptr;

}

std::vector<State*> SearchTree::Search(int opc)
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

State* SearchTree::depthFirstSearch(){
    int visited, expanded;
    std::stack<State*> s;
    State* current = root;

    s.push(root);

    visited = 1;
    expanded = 0;

    while(current->countConflicts() != 0){
        current->makeChildren();
        expanded += current->getChildCountValids();

        for(int i = 0; i < (n*(n-1))/2; ++i)
            if(current->getChild(i) != NULL)
                s.push(current->getChild(i));

        if(s.empty()) break;

        s.pop();
        current = s.top();
        ++visited;
    }

    setSearchData(visited, expanded);

    return (!s.empty()) ? current : NULL;
}

State* SearchTree::breadthFirstSearch()
{
    int visited, expanded;
    std::queue<State*> q;
    State* current = root;

    q.push(root);

    visited = 1;
    expanded = 0;

    while(current->countConflicts() != 0){
        current->makeChildren();
        expanded += current->getChildCountValids();
        q.pop();
        for(int i = 0; i < (n*(n-1))/2; ++i){
            if(current->getChild(i) != NULL)
                q.push(current->getChild(i));

        }

        if(q.empty()) break;

        current = q.front();
        ++visited;
    }

    setSearchData(visited, expanded);

    return (!q.empty()) ? current : NULL;
}

State* SearchTree::orderSearch()
{
    std::vector<State*> l;
    State* current = root;
    if(current == NULL)
        return NULL;
    root->setCost(0);
    l.push_back(root);
    std::sort(l.begin(), l.end(), comparator);
    current = *(l.begin());
    while(current->countConflicts() != 0){
        current->makeChildren();
        l.erase(l.begin());
        for(int i = 0; i < (n*(n-1))/2; ++i){
            if(current->getChild(i) != NULL){
                current->getChild(i)->setCost(current->getChild(i)->getParent()->getCost() + 1);
                l.push_back(current->getChild(i));
            }

        }

        if(l.empty()) return nullptr;

        std::sort(l.begin(), l.end(), comparator);
        current = *(l.begin());

    }

    return current;
}
State* SearchTree::greedy()
{
    std::vector<State*> l;
    State* current = root;
    if(current == NULL)
        return NULL;
    root->setHeuristic(root->countConflicts());
    l.push_back(root);
    std::sort(l.begin(), l.end(), comparator2);
    current = *(l.begin());
    while(current->countConflicts() != 0){
        current->makeChildren();
        l.erase(l.begin());
        for(int i = 0; i < (n*(n-1))/2; ++i){
            if(current->getChild(i) != NULL){
                current->getChild(i)->setHeuristic(current->getChild(i)->countConflicts());
                l.push_back(current->getChild(i));
            }

        }

        if(l.empty()) return nullptr;

        std::sort(l.begin(), l.end(), comparator2);
        current = *(l.begin());

    }

    return current;
}

State* SearchTree::AStar()
{
    std::vector<State*> l;
    State* current = root;
    if(current == NULL)
        return NULL;
    root->setCost(0);
    root->setHeuristic(root->countConflicts());
    root->setF(root->getCost() + root->countConflicts());
    l.push_back(root);
    std::sort(l.begin(), l.end(), comparator3);
    current = *(l.begin());
    while(current->countConflicts() != 0){
        current->makeChildren();
        l.erase(l.begin());
        for(int i = 0; i < (n*(n-1))/2; ++i){
            if(current->getChild(i) != NULL){
                 current->getChild(i)->setCost(current->getChild(i)->getParent()->getCost() + 1);
                 current->getChild(i)->setHeuristic(current->countConflicts());
                 current->getChild(i)->setF(current->getChild(i)->countConflicts() + current->getChild(i)->getHeuristic());
                l.push_back(current->getChild(i));
            }

        }

        if(l.empty()) return nullptr;

        std::sort(l.begin(), l.end(), comparator3);
        current = *(l.begin());

    }

    return current;
}
State* SearchTree::IDAStar()
{
    std::list<int> closed;
    int patamar = 0, patamar_old = -1;
    State* current = root;
    State* child = NULL;
    current->setF(current->countConflicts());
    patamar = current->getF();

    while(current->countConflicts() > 0){
        if(patamar == patamar_old)
            return NULL;
        else{
            if(current->getF() > patamar){
                closed.push_back(current->getF());
                current = current->getParent();
            }
            current->upadateOp();
            if(current->getLast_i() < n - 1){
                child = current->makeChildAlternative(current->getLast_i(), current->getLast_j()%n);
                if(child != NULL){
                    current = child;
                    current->setCost(current->getCost() + 1);
                    current->setF(current->getCost() + current->countConflicts());
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

                }else{
                    current = current->getParent();
                }
            }
        }

    }

    return current;
}

void SearchTree::setSearchData(int visited, int expanded)
{
    this->visited = visited;
    this->expanded = expanded;
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
    //std::cout << "Solution cost: " << cost << std::endl;
    std::cout << "Expanded nodes: " << expanded << std::endl;
    std::cout << "Visited nodes: " << visited << std::endl;
    std::cout << "Average branching factor: " << (double) expanded/visited << std::endl;
}

#include "SearchTree.h"
#include <stack>
#include <queue>
#include <list>
#include "Utils.h"
#include <vector>
#include <algorithm>
#include <iostream>
SearchTree::SearchTree(int n, int moves)
{
    this->n = n;
    this->moves = moves;
    this->root = new State(n);

    for (int i = 0; i < n; ++i) root->setQueen(i, i);
    for(int i = 0; i < (n*(n-1))/2; i++){
        root->upadateOp();
        std::cout<<"i: "<<root->getLast_i()<<" Last_j: "<<root->getLast_j()<<std::endl;
    }
}

SearchTree::~SearchTree()
{
    delete root;
}
std::vector<State*> SearchTree::getPathTo(State* solution)
{
    State *current = NULL;
    current = solution;
    std::vector<State*> path;
    if(solution != NULL){

        while(current->getParent() != NULL){
            path.insert(path.begin(), current);
            current = current->getParent();
        }

        path.insert(path.begin(), current);
        return path;
    }
}

State* SearchTree::backTracking(State* root)
{
    int childrenCount = n * moves;
    moves = moves % n;
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
    switch(opc){
        case 1:
            return getPathTo(backTracking(root));
            break;
        case 2:
             return getPathTo(depthFirstSearch());
             break;
        case 3:
        {
            State* solutinon = breadthFirstSearch();
            solutinon->printTable();
            return getPathTo(solutinon);
            break;
        }

         case 4:
            return getPathTo(orderSearch());
            break;

         case 5:
            return getPathTo(greedy());
            break;
         case 6:
            return getPathTo(AStar());
            break;
        case 7:
            return getPathTo(IDAStar());
            break;
    }

}


State* SearchTree::depthFirstSearch(){
    std::stack<State*> s;
    State* current = root;
    if(current == NULL)
        return NULL;
    s.push(root);
    while(current->countConflicts() != 0){
        current->makeChildren(moves);
        s.pop();

        for(int i = 0; i < (n*(n-1))/2; ++i){
            if(current->getChild(i) != NULL)
                s.push(current->getChild(i));
        }
        if(s.empty()) return nullptr;
        current = s.top();


    }

    return current;
}
State* SearchTree::breadthFirstSearch()
{
    std::queue<State*> q;
    State* current = root;
    if(current == NULL)
        return NULL;
    q.push(root);
    while(current->countConflicts() != 0){
        current->makeChildren(moves);
        q.pop();
        for(int i = 0; i < (n*(n-1))/2; ++i){
            if(current->getChild(i) != NULL)
                q.push(current->getChild(i));

        }

        if(q.empty()) return nullptr;

        current = q.front();

    }

    return current;
}

void SearchTree::freeSearchTree(State* root)
{
   /* if(root->getChildCountValids() == 0)
        delete root;

    for(int i = 0; i < n*moves; ++i){
            if(root->getChildCountValids() > 0)
                freeSearchTree(root->getChild(i));
    }*/
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
        current->makeChildren(moves);
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
        current->makeChildren(moves);
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
        current->makeChildren(moves);
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
    std::list<State*> closed;
    int patamar = 0, patamar_old = -1;
    State* current = root;
    current->setF(current->countConflicts());
    patamar = current->getF();

    while(current->countConflicts() > 0){
        if(patamar == patamar_old)
            return NULL;
        else{
            if(current->getF() > patamar){
                closed.push_back(current);
                current = current->getParent();
            }
            current->upadateOp();
            if(current->getLast_i() < n - 1){
                current = current->makeChildAlternative(current->getLast_i(), current->getLast_j()%n);
                if(current != NULL){
                    current->setCost(current->getCost() + 1);
                    current->setF(current->getCost() + current->countConflicts());
                }
            }else{
                if(current = root){
                    patamar_old = patamar;
                    patamar = findMin(closed);
                    for(int i = 0; i < (n*(n-1))/2; ++i){
                        if(current->getChild(i) != NULL)
                            delete current->getChild(i);
                    }

                }else{
                    current = current->getParent();
                }
            }




        }

    }

    return current;
}

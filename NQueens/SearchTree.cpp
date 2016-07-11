#include "SearchTree.h"
#include <stack>
#include <queue>
SearchTree::SearchTree(State* root)
{
    this->root = root;
}

SearchTree::~SearchTree()
{

}
std::vector<State*> SearchTree::getPathTo(State* solution)
{
    State *current = NULL;
    current = solution;
    std::vector<State*> path;
    while(current->getParent() != NULL){
        path.insert(path.begin(), current);
        current = current->getParent();
    }
    path.insert(path.begin(), current);
    return path;
}

State* SearchTree::backTrackingInternal(State* root, int moves, int n)
{
    int childrenCount = n * moves;
    moves = moves % n;
    State* current = root;
    if(current->countConflicts() == 0){
        return current;
    }
    int  x = 0;

    current->setChildren(new State*[childrenCount]);

    State* child = NULL;
    for (int i = 0; i < n; ++i){
        for (int j = 1; j <= moves; ++j){
            child = current->makeChild(i,j);
            if(child != NULL){
                current->setChild(x++, child);
                current = backTrackingInternal(child, moves, n);
                if(current != NULL)
                    return current;
            }else{
                ++x;
            }
        }
    }
    return nullptr;

}


std::vector<State*> SearchTree::Search(int n, int moves, int opc)
{   switch(opc){
        case 1:
            return getPathTo(backTrackingInternal(root,  moves ,n));
            break;
        case 2:
             return getPathTo(depthFirstSearch(root,  n ,moves));
             break;
        case 3:
             return getPathTo(breadthFirstSearch(root,  n ,moves));
             break;
    }

}
std::vector<State*> SearchTree::dps(int n, int moves)
{
    return getPathTo(depthFirstSearch(root, n, moves));
}

State* SearchTree::depthFirstSearch(State* root, int n, int moves){
    std::stack<State*> s;
    State* current = root;
    if(current == NULL)
        return NULL;

    while(current->countConflicts() != 0){
        current->makeChildren(moves);
        for(int i = n*moves -1 ; i >= 0; --i){
            if(current->getChild(i) != NULL)
                s.push(current->getChild(i));
        }
        current = s.top();
        s.pop();
        if(s.size() == 0) return nullptr;
    }
    return current;
}
State* SearchTree::breadthFirstSearch(State* root, int n, int moves)
{
    std::queue<State*> q;
    State* current = root;
    if(current == NULL)
        return NULL;

    while(current->countConflicts() != 0){
        current->makeChildren(moves);
        for(int i = 0; i < n*moves; ++i){
            if(current->getChild(i) != NULL)
                q.push(current->getChild(i));

        }
        current = q.front();
        q.pop();
        if(q.size() == 0) return nullptr;
    }
    return current;
}

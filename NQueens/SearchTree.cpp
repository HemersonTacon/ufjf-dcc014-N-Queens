#include "SearchTree.h"
#include <stack>
#include <queue>
SearchTree::SearchTree(int n, int moves)
{
    this->n = n;
    this->moves = moves;
    this->root = new State(n);

    for (int i = 0; i < n; ++i) root->setQueen(i, i);
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

    current->setChildren(new State*[childrenCount]);

    State* child = NULL;
    for (int i = 0; i < n; ++i){
        for (int j = 1; j <= moves; ++j){
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
            State* solutinon = breadthFirstSearch();
            solutinon->printTable();
            return getPathTo(solutinon);
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
        for(int i = 0; i < n*moves; ++i){
            if(current->getChild(i) != NULL)
                s.push(current->getChild(i));
        }

        current = s.top();

        if(s.empty()) return nullptr;
    }
    current->printTable();
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
        for(int i = 0; i < n*moves; ++i){
            if(current->getChild(i) != NULL)
                q.push(current->getChild(i));

        }


        current = q.front();
        current->printTable();
        if(q.empty()) return nullptr;
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

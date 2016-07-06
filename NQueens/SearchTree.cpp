#include "SearchTree.h"
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
    current = solution->getParent();
    std::vector<State*> path;
    while(current->getParent() != NULL){
        path.insert(path.begin(), current);
        current = current->getParent();
    }
    path.insert(path.begin(), current);
    return path;
}

State* SearchTree::backTrackingInternal(State* root)
{
    State* current = root;
    if(current->countConflicts() == 0){
        current->printTable();
        return current;
    }

    current->makeChildren(3);
    int i = 0;
    while(i < current->getSizeChildren()){
        if(current->getChild(i) != NULL){
            current = backTrackingInternal(current->getChild(i));
            if(current != NULL)
                return current;

        }
            i++;
    }
    return NULL;






 /*
    State* current = NULL;
    current = root;
    int i, valid_childs = 0;
    while(current->countConflicts() != 0){
        current->setVisited(current->getVisited() + 1);
        i =  current->getVisited();
        current->makeChildren(1);
        while(i < current->getSizeChildren()){
            if(current->getChild(i) != NULL){
                current = current->getChild(i);
                ++valid_childs;
                i++;
                break;
            }
            i++;
        }
        if(valid_childs == 0)
            current = current->getParent();
        current->setVisited(--i);

        if(current == NULL)
            return false;
    }
    return true;*/
}


std::vector<State*> SearchTree::backTracking()
{
    return getPathTo(backTrackingInternal(root));
}


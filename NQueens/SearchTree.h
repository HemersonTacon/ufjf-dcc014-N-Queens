#ifndef SEARCHTREE_H
#define SEARCHTREE_H
#include "State.h"
#include <stdlib.h>
#include <vector>
class SearchTree
{
    public:
        SearchTree(State* root);
        virtual ~SearchTree();
        State* backTrackingInternal(State* root, int moves, int n);
        State* depthFirstSearch(State* root, int n, int moves);
        State* breadthFirstSearch(State* root, int n, int moves);
        std::vector<State*> Search(int n, int moves, int opc);
        std::vector<State*> getPathTo(State* solution);
        std::vector<State*> dps(int n, int moves);


    protected:
    private:
        State* root;
};

#endif // SEARCHTREE_H

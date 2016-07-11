#ifndef SEARCHTREE_H
#define SEARCHTREE_H
#include "State.h"
#include <stdlib.h>
#include <vector>
class SearchTree
{
    public:
        SearchTree(State* root, int n, int moves);
        virtual ~SearchTree();
        State* backTrackingInternal(State* root, int moves, int n);
        State* depthFirstSearch(State* root, int n, int moves);
        State* breadthFirstSearch(State* root, int n, int moves);
        std::vector<State*> Search( int opc);
        std::vector<State*> getPathTo(State* solution);



    protected:
    private:
        State* root;
        void freeSearchTree(State* root);
        int n;
        int moves;
};

#endif // SEARCHTREE_H

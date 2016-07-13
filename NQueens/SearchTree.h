#ifndef SEARCHTREE_H
#define SEARCHTREE_H
#include "State.h"
#include <stdlib.h>
#include <vector>
class SearchTree
{
    public:
        SearchTree(int n, int moves);
        virtual ~SearchTree();

        State* backTracking(State* root);
        State* depthFirstSearch();
        State* breadthFirstSearch();
        std::vector<State*> Search(int opc);
        std::vector<State*> getPathTo(State* solution);
        State* orderSearch();
        State* greedy();
        State* AStar();
        State *IDAStar();
    private:
        State* root;
        void freeSearchTree(State* root);
        int n;
        int moves;
};

#endif // SEARCHTREE_H

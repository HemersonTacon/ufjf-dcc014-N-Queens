#ifndef SEARCHTREE_H
#define SEARCHTREE_H
#include "State.h"
#include <stdlib.h>
#include <vector>
class SearchTree
{
    public:
        SearchTree(int n);
        virtual ~SearchTree();

        void printStats();
        std::vector<State*> doSearch(int opc);
        std::vector<State*> getPathTo(State* solution);
        State* backTracking(State* root);
        State* depthFirstSearch();
        State* breadthFirstSearch();
        State* orderSearch();
        State* greedy();
        State* AStar();
        State *IDAStar();
    private:
        int n, visited, expanded;
        double cpuDuration;
        State* root;
        State* solution;

        //methods
        void setSearchData(int visited, int expanded);
};

#endif // SEARCHTREE_H

#ifndef SEARCHTREE_H
#define SEARCHTREE_H

#include <iostream>
#include <chrono>
#include <vector>
#include <stack>
#include <queue>
#include <list>
#include "State.h"
#include "MinHeap.h"

class SearchTree
{
    public:
        SearchTree(int n): SearchTree(n, 0) {};
        SearchTree(int n, int heuristicFunction);
        virtual ~SearchTree();

        void printStats();
        std::vector<State*> doSearch(std::string algorithm);

    private:
        int n, visited, expanded;
        double searchExecutionTime;
        State *root, *solution;

        //methods
        std::vector<State*> getPathTo(State* solution);
        State* backTracking(State* root);
        State* depthFirstSearch(int depthLimit);
        State* breadthFirstSearch();
        State* bestFirstSearch(bool (*comparator)(State*, State*));
        State* orderSearch();
        State* greedy();
        State* AStar();
        State *IDAStar();
};

#endif // SEARCHTREE_H

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
        State* backTrackingInternal(State* root);

        std::vector<State*> backTracking();
        std::vector<State*> getPathTo(State* solution);

    protected:
    private:
        State* root;
};

#endif // SEARCHTREE_H

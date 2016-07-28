#ifndef STATE_H
#define STATE_H

#include <iostream>

class State
{
    public:
        State(int n, int depth): State(n, depth, -1) {};
        State(int n, int depth, int heuristicFunction);
        virtual ~State();

        void printBoard();
        void clearChildren();
        void updateCost();
        void updateHeuristicValue();
        void updateF();
        bool hasCycle();
        int countConflicts();
        int makeChildren();
        State* makeNextChild();
        State* makeChild(int i, int j);

        // getters and setters
        void setQueen(int line, int column);
        void setParent(State *parent);
        int getCost();
        int getHeuristicValue();
        int getF();
        int getDepth();
        int getQueenAt(int line);
        int* getBoard();
        State* getParent();
        State* getChild(int i);

    private:
        int n, cost, heuristicFunction, heuristicValue, f,
            childCount, depth, childGen_i, childGen_j;
        int *board;
        State *parent;
        State **children;

        // methods
        bool equals(State *parent);
};

#endif // STATE_H

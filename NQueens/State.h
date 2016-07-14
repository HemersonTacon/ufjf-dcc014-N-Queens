#ifndef STATE_H
#define STATE_H


class State
{
    public:
        State(int n, int depth);
        virtual ~State();

        int countConflicts();
        bool hasCycle();
        int makeChildren();
        void printTable();
        void setQueen(int line, int column);
        int getQueenAt(int line);
        State* getParent();
        void setParent(State *parent);
        int* getTable();
        void setVisited(int val);
        int getVisited();
        int getSizeChildren();
        State* getChild(int i);
        State* makeChildMove(int line, int steps);
        State* makeChildPermutation(int i, int j);
        void setChild(int pos, State* child);
        void setChildren(State** children);
        void setChildCountValids(int i);
        void setCost(int cost);
        int getCost();
        void setHeuristic(int h);
        int getHeuristic();
        void setF(int f);
        int getF();
        int getLast_i();
        int getLast_j();
        void setLast_i(int i);
        void setLast_j(int j);
        void upadateOp();
        int getDepth();

    private:
        int n;
        int depth;
        int last_i, last_j;
        int cost;
        int last_visited;
        int heuristic;
        int f;
        int child_count;
        int *table;
        State **children;
        State *parent;

        //methods
        bool isEqual(State *parent);
};

#endif // STATE_H

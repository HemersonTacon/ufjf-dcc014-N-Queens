#ifndef STATE_H
#define STATE_H


class State
{
    public:
        State(int n, int depth);
        virtual ~State();

        int countConflicts();
        bool hasCycle();
        void makeChildren();
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
        State* makeChild(int line, int r);
        State* makeChildAlternative(int i, int j);
        void setChild(int pos, State* child);
        void setChildren(State** children);
        int getChildCountValids();
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

    protected:

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

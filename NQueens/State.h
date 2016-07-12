#ifndef STATE_H
#define STATE_H


class State
{
    public:
        State(int n);
        virtual ~State();

        int countConflicts();
        bool hasCycle();
        void makeChildren(int moves);
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
        void setCost(int cost);
        int getCost();
        void setHeuristic(int h);
        int getHeuristic();
        void setF(int f);
        int getF();

    protected:

    private:
        int n, size_children;
        int cost;
        int last_visited;
        int heuristic;
        int f;
        int child_count;
        int *table;
        State **children;
        State *parent;
        bool isEqual(State *parent);

};

#endif // STATE_H

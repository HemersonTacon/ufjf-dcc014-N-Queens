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
        State* makeChild(int line, int r);
        void printTable();
        void setQueen(int line, int column);
        int getQueenAt(int line);
        State* getParent();
        void setParent(State *parent);
        int* getTable();

    protected:

    private:
        int n;
        int child_count;
        int *table;
        State **children;
        State *parent;
        bool isEqual(State *parent);
};

#endif // STATE_H

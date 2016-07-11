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
        void setChild(int pos, State* child);
        void setChildren(State** children);

    protected:

    private:
        int n, size_children;
        int last_visited;
        int child_count;
        int *table;
        State **children;
        State *parent;
        bool isEqual(State *parent);

};

#endif // STATE_H

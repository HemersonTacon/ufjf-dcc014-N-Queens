#ifndef STATE_H
#define STATE_H


class State
{
    public:
        State(int n);
        virtual ~State();

        int countConflicts();
        void makeChildren();
        State* makeChild(int line, int r);
        void printTable();
        void setQueen(int line, int column);
        int getQueenAt(int line);

    protected:

    private:
        int n;
        int *table;
        State **children;
};

#endif // STATE_H

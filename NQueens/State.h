#ifndef STATE_H
#define STATE_H


class State
{
    public:
        State(int n);
        virtual ~State();

        int countConflicts();
        void makeChildren();
        State* makeChild(int pos, int r);
        void printTable();

        int *table;

    protected:

    private:
        int n;
        State **children;
};

#endif // STATE_H

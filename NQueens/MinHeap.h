#ifndef MINHEAP_H
#define MINHEAP_H

#include <math.h>
#include <vector>
#include "State.h"

class MinHeap
{
    public:
        MinHeap(bool (*comparator)(State*, State*)): MinHeap(0, comparator) {};
        MinHeap(int reserve, bool (*comparator)(State*, State*));
        ~MinHeap();

        void push(State* state, bool preserveHeap);
        void deleteMin(bool preserveHeap);
        void heapify();
        bool empty();
        State* top();

    private:
        bool (*comparator)(State*, State*);
        int count;
        std::vector<State*> heap;

        inline void swap(int i, int j);
        void up_heap(int position);
        void down_heap(int position);
        int getMin(int i, int j);
};

#endif // MINHEAP_H

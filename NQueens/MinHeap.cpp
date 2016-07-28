#include "MinHeap.h"

MinHeap::MinHeap(int reserve, bool (*comparator)(State*, State*))
{
    count = 0;
    heap.reserve(reserve);
    this->comparator = comparator;
}

MinHeap::~MinHeap()
{
    heap.clear();
}

void MinHeap::push(State* state, bool preserveHeap)
{
    heap.push_back(state);

    if (preserveHeap)
        up_heap(count);

    ++count;
}

void MinHeap::deleteMin(bool preserveHeap)
{
    heap[0] = heap[--count];

    heap.pop_back();

    if (preserveHeap)
        down_heap(0);
}

void MinHeap::heapify()
{
    for (int i = floor((count - 1)/2); i >= 0; --i) down_heap(i);
}

bool MinHeap::empty()
{
    return count == 0;
}

State* MinHeap::top()
{
    return heap[0];
}

inline void MinHeap::swap(int i, int j)
{
    State* aux;

    aux = heap[i];
    heap[i] = heap[j];
    heap[j] = aux;
}

void MinHeap::up_heap(int position)
{
    int parent = floor((position - 1) / 2);
    std::pair<int,int> aux;

    while (parent >= 0 && comparator(heap[position], heap[parent]))
    {
        swap(position, parent);

        position = parent;
        parent = floor((position - 1) / 2);
    }
}

void MinHeap::down_heap(int position)
{
    int fstChild = (2 * position) + 1,
        sndChild = fstChild + 1,
        minChild;
    std::pair<int,int> aux;

    while (sndChild < count && (minChild = getMin(fstChild, sndChild)) && comparator(heap[minChild], heap[position]))
    {
        swap(minChild, position);

        position = minChild;

        fstChild = (2 * position) + 1;
        sndChild = fstChild + 1;
    }

    if (fstChild < count && comparator(heap[fstChild], heap[position]))
        swap(fstChild, position);
}

int MinHeap::getMin(int i, int j)
{
    return comparator(heap[i], heap[j]) ? i : j;
}

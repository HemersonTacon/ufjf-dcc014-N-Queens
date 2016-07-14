#ifndef UTILS_H_INCLUDED
#define UTILS_H_INCLUDED

bool comparator (State* i, State* j) { return (i->getCost() < j ->getCost()); }
bool comparator2 (State* i, State* j) { return (i->getHeuristic() < j ->getHeuristic()); }
bool comparator3 (State* i, State* j) { return (i->getF() < j ->getF()); }
int findMin(std::list<int> l){
    int s = *(l.begin());

    int minimal = s;
    for(auto it = l.begin(); it!= l.end(); ++it){
        s = *it;
        if(s < minimal)
            minimal = s;
    }
    return minimal;
}
#endif // UTILS_H_INCLUDED

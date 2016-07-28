#ifndef UTILS_H_INCLUDED
#define UTILS_H_INCLUDED

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

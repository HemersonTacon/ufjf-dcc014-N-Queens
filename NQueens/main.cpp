#include <iostream>
#include "State.h"
#include "SearchTree.h"
using namespace std;
void printPath(std::vector<State*> path){
    for(auto it = path.begin(); it != path.end(); ++it)
        (*it)->printTable();
}
void test()
{
    int opc;
    State* s = new State(4);
    SearchTree *tree = new SearchTree(s);
    std::vector<State*> path;
    s->setQueen(0, 0);
    s->setQueen(1, 0);
    s->setQueen(2, 0);
    s->setQueen(3, 0);
    std::cout<<"Digite 0 para sair"<<std::endl;
    std::cout<<"Digite 1 para backtracking"<<std::endl;
    std::cout<<"Digite 2 para DPS"<<std::endl;
    std::cout<<"Digite 3 para largura"<<std::endl;
    cin>>opc;
    while(opc != 0){
        switch(opc){
            case 1:
              path = tree->Search(4, 1, opc);
              printPath(path);
              break;
            case 2:
              path = tree->Search(4, 1, opc);
              printPath(path);
              break;
            case 3:
              path = tree->Search(4, 1, opc);
              printPath(path);
              break;

        }
        std::cout<<"Digite 0 para sair"<<std::endl;
        std::cout<<"Digite 1 para backtracking"<<std::endl;
        std::cout<<"Digite 2 para DPS"<<std::endl;
        std::cout<<"Digite 3 para largura"<<std::endl;
        cin>>opc;
        system("clear");
    }



    //cout << s->countConflicts() << endl;


    delete s;
}

int main()
{
    test();

    return 0;
}

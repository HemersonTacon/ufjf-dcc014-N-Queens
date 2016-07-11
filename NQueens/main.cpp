#include <iostream>
#include "State.h"
#include <time.h>
#include "SearchTree.h"
#include <stdlib.h>
using namespace std;
void printPath(std::vector<State*> path){
    for(auto it = path.begin(); it != path.end(); ++it)
        (*it)->printTable();
}
void test()
{
    srand(time(NULL));
    std::vector<State*> path;
    int opc, n;
    std::cout<<"Entre com N:"<<std::endl;
    cin>>n;
    State* s = new State(n);
    SearchTree *tree = new SearchTree(s);
    for(int i = 0; i < n; i++){
        s->setQueen(i, rand()%n);
    }

    std::cout<<"Digite 0 para sair"<<std::endl;
    std::cout<<"Digite 1 para backtracking"<<std::endl;
    std::cout<<"Digite 2 para DPS"<<std::endl;
    std::cout<<"Digite 3 para largura"<<std::endl;
    cin>>opc;
    while(opc != 0){
        switch(opc){
            case 1:
              path = tree->Search(n, 1, opc);
              printPath(path);
              break;
            case 2:
              path = tree->Search(n, 1, opc);
              printPath(path);
              break;
            case 3:
              path = tree->Search(n, 1, opc);
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

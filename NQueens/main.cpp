#include <iostream>
#include "State.h"
#include <time.h>
#include "SearchTree.h"
#include <stdlib.h>
#include <stack>

using namespace std;

void printPath(std::vector<State*> path){
    for(auto it = path.begin(); it != path.end(); ++it)
        (*it)->printBoard();
}

void test()
{
    std::vector<State*> path;
    int opc, n;
    std::cout<<"Entre com N:"<<std::endl;
    cin>>n;
    SearchTree *tree = nullptr;


    std::cout<<"Digite 0 para sair"<<std::endl;
    std::cout<<"Digite 1 para backtracking"<<std::endl;
    std::cout<<"Digite 2 para DFS"<<std::endl;
    std::cout<<"Digite 3 para largura"<<std::endl;
    std::cout<<"Digite 4 para ordenada"<<std::endl;
    std::cout<<"Digite 5 para gulosa"<<std::endl;
    std::cout<<"Digite 6 para A*"<<std::endl;
    std::cout<<"Digite 7 para IDA*"<<std::endl;
    cin>>opc;
    while(opc != 0){

        tree = new SearchTree(n, 1);

        path = tree->doSearch(opc);

        if(path.size() == 0)
            std::cout<<"No solution"<<std::endl;
        else
            printPath(path);

        tree->printStats();

        delete tree;

        std::cout<<"Digite 0 para sair"<<std::endl;
        std::cout<<"Digite 1 para backtracking"<<std::endl;
        std::cout<<"Digite 2 para DPS"<<std::endl;
        std::cout<<"Digite 3 para largura"<<std::endl;
        std::cout<<"Digite 4 para ordenada"<<std::endl;
        std::cout<<"Digite 5 para gulosa"<<std::endl;
        std::cout<<"Digite 6 para A*"<<std::endl;
        std::cout<<"Digite 7 para IDA*"<<std::endl;
        cin>>opc;
    }
}

int main()
{
    test();

    return 0;
}

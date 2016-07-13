#include <iostream>
#include "State.h"
#include <time.h>
#include "SearchTree.h"
#include <stdlib.h>
using namespace std;
bool contains(int sorteio, State* s, int n){
    int* table = s->getTable();
    for(int i = 0; i < n; i++){
        if(sorteio == table[i])
            return true;
    }

    return false;

}
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
    SearchTree *tree = NULL;


    std::cout<<"Digite 0 para sair"<<std::endl;
    std::cout<<"Digite 1 para backtracking"<<std::endl;
    std::cout<<"Digite 2 para DPS"<<std::endl;
    std::cout<<"Digite 3 para largura"<<std::endl;
    std::cout<<"Digite 4 para ordenada"<<std::endl;
    std::cout<<"Digite 5 para gulosa"<<std::endl;
    std::cout<<"Digite 6 para A*"<<std::endl;
    cin>>opc;
    while(opc != 0){

        tree = new SearchTree(n, n-1);

        switch(opc){
            case 1:
              path = tree->Search(opc);
              printPath(path);
              break;
            case 2:
              path = tree->Search(opc);
              printPath(path);
              break;
            case 3:
              path = tree->Search(opc);
              if(path.size() == 0){
                std::cout<<"No solution"<<std::endl;
                break;
              }
              printPath(path);
              break;
            case 4:
              path = tree->Search(opc);
              if(path.size() == 0){
                std::cout<<"No solution"<<std::endl;
                break;
              }
              printPath(path);
              break;

            case 5:
              path = tree->Search(opc);
              if(path.size() == 0){
                std::cout<<"No solution"<<std::endl;
                break;
              }
              printPath(path);
              break;

            case 6:
              path = tree->Search(opc);
              if(path.size() == 0){
                std::cout<<"No solution"<<std::endl;
                break;
              }
              printPath(path);
              break;

        }
        delete tree;

        std::cout<<"Digite 0 para sair"<<std::endl;
        std::cout<<"Digite 1 para backtracking"<<std::endl;
        std::cout<<"Digite 2 para DPS"<<std::endl;
        std::cout<<"Digite 3 para largura"<<std::endl;
        std::cout<<"Digite 4 para ordenada"<<std::endl;
        std::cout<<"Digite 5 para gulosa"<<std::endl;
        std::cout<<"Digite 6 para A*"<<std::endl;
        cin>>opc;
        //system("clear");
    }
}

int main()
{
    test();

    return 0;
}

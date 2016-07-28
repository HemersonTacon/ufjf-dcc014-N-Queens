#include <iostream>
#include <stdexcept>
#include "SearchTree.h"
#include "State.h"

void printUsage()
{
    std::cout << "usage: nqueens n algorithm [-d depth] [-h heuristic] [-s] [-p]" << std::endl;
    std::cout << "  n: instance number of queens (> 3)" << std::endl;
    std::cout << "  algorithm: algorithm to find a solution (see list below)" << std::endl;
    std::cout << "  -d depth: depth limit for DFS (>0)" << std::endl;
    std::cout << "                (default depth is 5 * n)" << std::endl;
    std::cout << "  -h heuristic: heuristic function to evaluate states (0-1)" << std::endl;
    std::cout << "                (default heuristic is 0, which returns a constant value)" << std::endl;
    std::cout << "  -s: prints search statistics" << std::endl;
    std::cout << "  -p: prints path to found solution" << std::endl;
    std::cout << std::endl << "Avaiable algorithms are:" << std::endl;
    std::cout << "   bcktrk    Backtracking" << std::endl;
    std::cout << "   dfs       Depth-first search" << std::endl;
    std::cout << "   bfs       Breadth-first search" << std::endl;
    std::cout << "   ucs       Uniform-cost search" << std::endl;
    std::cout << "   greedy    Greedy best-first search/pure heuristic search" << std::endl;
    std::cout << "   astr      A*" << std::endl;
    std::cout << "   idastr    IDA*" << std::endl;
}

void printError(std::string message)
{
    std::cout << "aborted: " << message << std::endl << std::endl;

    printUsage();
}

void search(bool printPath, bool printStats, int n, int h, int d, std::string algorithm)
{
    SearchTree* tree = new SearchTree(n, h);

    if (d != 5 * n)
        tree->setDfsDepthLimit(d);

    std::vector<State*> path = tree->doSearch(algorithm);

    if(path.size() == 0)
        std::cout << "Search finished: no solution" << std::endl;
    else if (printPath)
    {
        std::cout << "Search finished, path to solution:" << std::endl;

        for(auto it = path.begin(); it != path.end(); ++it)
            (*it)->printBoard();
    }
    else
    {
        std::cout << "Search finished, found solution:" << std::endl;
        auto it = path.end();
        --it;
        (*it)->printBoard();
    }

    if (printStats)
        tree->printStats();
}

bool getParameters(int argc, char* argv[], bool &printStats, bool &printPath, int &n, int &h, int &d, std::string &algorithm)
{
    bool foundH, foundD;

    try {
        n = std::stoi(argv[1]);
    } catch (const std::invalid_argument ia) {
        printError("parameter 'n' must be an integer");

        return false;
    }

    if (n < 4) {
        printError("parameter 'n' must be greater than 3");

        return false;
    }

    d = 5 * n; // default depth limit for DFS
    algorithm = argv[2];

    if (!(algorithm == "bcktrk" || algorithm == "dfs" || algorithm == "bfs"
        || algorithm == "ucs" || algorithm == "greedy" || algorithm == "astr" || algorithm == "idastr"))
    {
        printError("invalid algorithm");

        return false;
    }

    printStats = printPath = foundH = foundD = false;

    for (int i = 3; i < argc; ++i) {
        std::string s(argv[i]);

        if (foundH) {
            try {
                h = std::stoi(argv[i]);
            } catch (const std::invalid_argument ia) {
                printError("parameter 'heuristic' must be an integer");

                return false;
            }

            foundH = false;
        } else if (foundD) {
            try {
                d = std::stoi(argv[i]);
            } catch (const std::invalid_argument ia) {
                printError("parameter 'depthm' must be an integer");

                return false;
            }

            foundD = false;
        }

        if (s == "-s") {
            printStats = true;
            continue;
        } else if (s == "-p") {
            printPath = true;
            continue;
        } else if (s == "-h") {
            foundH = true;
            continue;
        } else if (s == "-d") {
            foundD = true;
            continue;
        }
    }

    if (h < 0 || h > 1) {
        printError("parameter 'h' must be between 0 and 1");

        return false;
    }

    if (d < 1) {
        printError("parameter 'd' must be greater than 0");

        return false;
    }

    return true;
}

int main(int argc, char* argv[])
{
    bool printStats, printPath;
    int n, h = 0, d;
    std::string algorithm;

    if (argc == 1 || argc < 3 || argc > 9)
    {
        printUsage();

        return 0;
    }

    // gets parameters from args
    if (!getParameters(argc, argv, printStats, printPath, n, h, d, algorithm))
        return 0;

    search(printPath, printStats, n, h, d, algorithm);

    return 0;
}

//
// Created by Fangyuan Huang on 10/30/22.
//

#ifndef EVICTION_SWAPMANAGER_H
#define EVICTION_SWAPMANAGER_H

#include <vector>
#include <string>

using namespace std;

class SwapManager {
public:
    SwapManager(int capacity, string strategy);
    vector<int> space;
    // add an address into memory, if full, kick one out according to strategy
    void push(int address);
    // tells whether the space contains the address in its memory
    bool get(int address);
    void setCapacity(int capacity);
    void setStrategy(string strategy);

private:
    int capacity;
    string strategy;
    int hit;
    int miss;
    int total;

};


#endif //EVICTION_SWAPMANAGER_H

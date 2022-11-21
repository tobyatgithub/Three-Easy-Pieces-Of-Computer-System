//
// Created by Fangyuan Huang on 10/30/22.
//

#include "SwapManager.h"

#include <iostream>

using namespace std;

void SwapManager::push(int address) {
    if (space.size() >= capacity) {
        if (strategy == "FILO") {
            space.pop_back();
        } else if (strategy == "FIFO") {
            space.erase(space.begin());
        } else {
            cout << "unrecognized strategy:" << strategy << endl;
        }
    }
    space.push_back(address);
}

bool SwapManager::get(int address) {
    bool exist = find(space.begin(), space.end(), address) != space.end();
//    this->total += 1;
    total += 1;
    if (exist) {
        hit += 1;
        printf("Job %d found! HIT = %d, MISS = %d, TOTAL = %d, HITRATE = %.2f\n",
                address, hit, miss, total, 100. * hit / total);
    } else {
        miss += 1;
        push(address);
        printf("Job %d miss! HIT = %d, MISS = %d, TOTAL = %d, HITRATE = %.2f\n",
               address, hit, miss, total, 100. * hit / total);
    }

    return true;
}

void SwapManager::setCapacity(int capacity) {
    if (capacity < 0)
        throw invalid_argument("capacity");
    this->capacity = capacity;
}

void SwapManager::setStrategy(string strategy) {
    if (strategy != "FIFO" && strategy != "FILO")
        throw invalid_argument("strategy");
    this->strategy = strategy;
}

SwapManager::SwapManager(int capacity, string strategy) {
    cout << "Constructing a swap manager..." << endl;
    this->space = vector<int>();
    hit = 0;
    miss = 0;
    total = 0;
    setCapacity(capacity);
    setStrategy(strategy);
}
#include <iostream>

#include "SwapManager.h"

int main() {
    vector<int> jobList = {1,2,3,4,5,6,7,1,2,3,4,5,6,7};
    // test 1, FIFO
    SwapManager FIFO = SwapManager(5, "FIFO");
    for( int job: jobList) {
        FIFO.get(job);
    }

    SwapManager FILO = SwapManager(5, "FILO");
    for( int job: jobList) {
        FILO.get(job);
    }

    std::cout << "Hello, World!" << std::endl;
    return 0;
}

#include <iostream>

#include "SwapManager.h"

int main() {
    vector<int> jobList = {1,2,3,4,5,6,7,1,2,3,4,5,6,7};
    // test 1, FIFO
    SwapManager FIFO = SwapManager(5, "FIFO");
    SwapManager FILO = SwapManager(5, "FILO");
    std::cout << "Testing FIFO with cap = 5" << std::endl;
    for( int job: jobList) {
        FIFO.get(job);
    }
    std::cout << "Testing FILO with cap = 5" << std::endl;
    for( int job: jobList) {
        FILO.get(job);
    }

//    std::cout << "Change capacity to 7!" << std::endl;

    std::cout << "Testing FIFO with cap = 7" << std::endl;
    FIFO.setCapacity(7);
    for( int job: jobList) {
        FIFO.get(job);
    }

    std::cout << "Testing FILO with cap = 7" << std::endl;
    FILO.setCapacity(7);
    for( int job: jobList) {
        FILO.get(job);
    }
    return 0;
}

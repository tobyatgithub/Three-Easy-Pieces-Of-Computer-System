"""
Python prototype for the free space management
"""
import math


class Ticket:
    def __init__(self, size):
        self.size = size


class System:
    def __init__(
        self,
        capacity: int,
        logger: bool = True,
        strategy: str = "BEST",
        doCoalesce: bool = False,
    ):
        self.capacity = capacity
        self.freeList = [(0, capacity)]  # list of tuple (address, space)
        self.jobList = []
        self.strategy = strategy
        self.doCoalesce = doCoalesce
        self.logger = logger
        # by default we sort the free list by address

    def malloc(self, Ticket: Ticket):
        size = Ticket.size
        if self.strategy == "BEST":
            bestIndex, minDiff = -1, math.inf
            for index, chunk in enumerate(self.freeList):
                head, space = chunk
                if space < size:
                    continue
                else:
                    if space == size:
                        del self.freeList[index]
                        self.jobList.append((head, space))
                        return (head, space)

                    diff = space - size
                    if diff < minDiff:
                        minDiff = diff
                        bestIndex = index
            head, space = self.freeList[bestIndex]
            del self.freeList[bestIndex]
            # self.jobList.append((head, head + size))
            self.jobList.append((head, size))
            self.freeList.append((head + size, space - size))
            # sort
            self.freeList.sort()
            self.jobList.sort()
            print("Free list: ", self.freeList)
            print("Job list: ", self.jobList)
            print()

    def coalese(self):
        if not self.freeList:
            return

        tmp = [self.freeList.pop(0)]
        while len(self.freeList) > 0:
            head1, size1 = tmp[-1]
            head2, size2 = self.freeList.pop(0)

            # merge
            if head1 + size1 == head2:
                tmp[-1] = (head1, size1 + size2)
            else:
                tmp.append((head2, size2))
        self.freeList = tmp
        print("Free list: ", self.freeList)
        print("Job list: ", self.jobList)
        print()
        return

    def free(self, index):
        if index < 0 or index >= len(self.jobList):
            # raise error
            print("Invalid free index.\n")
            return
        tmp = self.jobList.pop(index)
        self.freeList.append(tmp)
        # sort
        self.freeList.sort()
        print("Free list: ", self.freeList)
        print("Job list: ", self.jobList)
        print()


def main():
    freeSpaceManager = System(capacity=100)
    job1 = Ticket(10)
    job2 = Ticket(20)
    job3 = Ticket(30)

    freeSpaceManager.malloc(job1)
    freeSpaceManager.malloc(job2)
    freeSpaceManager.malloc(job3)

    freeSpaceManager.free(1)

    freeSpaceManager.malloc(job2)

    # test coalesce
    freeSpaceManager.free(1)

    freeSpaceManager.coalese()


if __name__ == "__main__":
    main()

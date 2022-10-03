class queueJob:
    def __init__(self, length, priority=0, name=""):
        self.jobLength = length
        self.priority = priority  # 0 = highest
        self.name = ""  # maybe name, maybe id.


class mlfq:
    def __init__(self, quantum=12):
        # quantum in ms
        self.queue1 = []
        self.queue2 = []
        self.queue3 = []
        self.quantum = quantum

    def start(self):
        # start the system
        pass

    def addNewJob(self, job):
        # add a new job to the system
        pass

    def killAJob(self, job):
        # remove a job from all the queues
        pass

    def plotProcess(self):
        # plot how the system will run the jobs
        pass

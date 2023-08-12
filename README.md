# implementation-Semaphore-with-Round-Robben-Schedule
implementation Semaphore with Round Robben Schedule
✅implementation of semaphore API with my own Round robin schedule

 ⭐️Semaphore is a process synchronization tool that prevents a race condition that may occur when multiple cooperative processes try to access the same resources. Two or more processes can synchronise by means of the signal. This means the process, trying to access the same shared resource can be forced to stop at a specific place until it is signalled to access the resource.

⭐️Semaphore in OS is an integer value that indicates whether the resource required by the process is available or not. The value of a semaphore is modified by osSignalWait(int32_t *semaphore);or osSignalSet(int *semaphore); 
                                                                                                           
1️⃣void osSignalWait(int32_t *semaphore);                                                                                                                                                                      decrements the value of semaphore and if the semaphore value becomes negative then the process executing wait() would be blocked.

2️⃣void osSignalSet(int *semaphore);                                                                                                            The signal() operation increments the value of semaphore

🔗you can check my code from her:https://github.com/hazemzain/implementation-Semaphore-with-Round-Robben-Schedule.git

🤝if you want to read more about semaphore, I recommend this website for you 
🔗https://www.geeksforgeeks.org/semaphores-in-process-synchronization/

#ifndef ADVANCEDPROGRAMINGPART4_THREADSYNC_H
#define ADVANCEDPROGRAMINGPART4_THREADSYNC_H

#include <mutex>
#include <condition_variable>

class ThreadSync {
public:
    static std::mutex mtx;
    static std::condition_variable cv;
    static bool thread_created;
};

#endif //ADVANCEDPROGRAMINGPART4_THREADSYNC_H

#include "ThreadSync.h"
std::mutex ThreadSync::mtx;
std::condition_variable ThreadSync::cv;
bool ThreadSync::thread_created = false;
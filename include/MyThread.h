#ifndef __MYTHREAD_H__
#define __MYTHREAD_H__
#include"Thread.h"
#include"MyCache.h"

class ThreadPool;
class MyThread:public Thread
{
    friend class MyCacheThread;
public:
    void get_related(ThreadPool*p)
    {
        threadPoolPtr_ = p;
    }
    
private:
    void run();
    ThreadPool*threadPoolPtr_;
    MyCache cache_;

};

#endif
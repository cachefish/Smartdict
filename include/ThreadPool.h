#ifndef __THREADPOOL_H__
#define __THREADPOOL_H__

#include"MyThread.h"
#include"MyLock.h"
#include"MyCondition.h"
#include"MyTask.h"
#include"Myconf.h"
#include"MyCacheThread.h"
#include<vector>
#include<string>
#include<queue>
#include<map>

class ThreadPool
{
    friend class MyCacheThread;
public:
    ThreadPool(MyConf&conf,int size = 12):vecThreads_(size),queueTasks_(),queueTasksLock_(),
    queueTasksCond_(queueTasksLock_),isStarted_(false),conf_(conf),cacheThread_(size)
    {
            std::vector<MyThread>::iterator iter;
            for(iter = vecThreads_.begin();iter!=vecThreads_.end();++iter)
            {
                iter->get_related(this);
            }
            cacheThread_.get_related(this);
    }

    void on()
    {
        if(isStarted_)
        {
            return;
        }
        isStarted_ = true;
        std::vector<MyThread>::iterator  iter;
        for(iter = vecThreads_.begin();iter!=vecThreads_.end();iter++)
        {
            iter->start();
        }
        cacheThread_.start();
    }

    void  off()
    {
        if(isStarted_)
        {
            isStarted_=false;
            queueTasksCond_.broadcast();
            while(!queueTasks_.empty())
            {
                queueTasks_.pop();
            }
        }
    }

    void allocate_task(MyTask&task)
    {
        queueTasksLock_.lock();
        std::cout<<"Add Task"<<std::endl;
        queueTasks_.push(task);
        queueTasksLock_.unlock();
        queueTasksCond_.broadcast();
    }

    bool get_task(MyTask&task)
    {
        queueTasksLock_.lock();
        while(isStarted_&&queueTasks_.empty())
        {
            queueTasksCond_.wait();
        }
        if(!isStarted_)
        {
            queueTasksLock_.unlock();
            queueTasksCond_.broadcast();
            return false;
        }
        task = queueTasks_.front();
        queueTasks_.pop();
        queueTasksLock_.unlock();
        queueTasksCond_.broadcast();
        std::cout<<"get stak "<<std::endl;
        return true;
    }


    MyConf&conf_;
private:
    ThreadPool(const ThreadPool&obj)=delete;
    ThreadPool&operator = (const ThreadPool&obj);
private:
    std::vector<MyThread> vecThreads_;   //存放任务线程的容器
    std::queue<MyTask> queueTasks_;          //存放任务的队列

    MyLock queueTasksLock_;
    MyCondition queueTasksCond_;
    bool isStarted_;
    MyCacheThread cacheThread_;
};

#endif
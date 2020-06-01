#ifndef __MYLOCK_H__
#define __MYLOCK_H__
#include<pthread.h>
#include<iostream>
//互斥锁
class MyLock
{
    friend class MyCondition;

public:
    MyLock()
    {
            if(pthread_mutex_init(&m_mutex,NULL))
            {
                std::cout<<__DATE__<<" "<<__TIME__<<" "<<__FILE__<<" "<<__LINE__<<":"<<"pthread_mutex_init failed"<<std::endl;
            }
    }

    void lock()
    {
        pthread_mutex_lock(&m_mutex);
    }

    void unlock()
    {
        pthread_mutex_unlock(&m_mutex);
    }

    ~MyLock()
    {
        pthread_mutex_destroy(&m_mutex);
    }

private:
    pthread_mutex_t m_mutex;

};

#endif
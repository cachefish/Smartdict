#ifndef __MYCONDITION_H__
#define __MYCONDITION_H__
#include<iostream>
#include"MyLock.h"
//信号量
class MyCondition
{

public:
    MyCondition(MyLock&lock):m_mutex(lock.m_mutex)
    {
        if(pthread_cond_init(&m_cond,NULL)){
            std::cout<<__DATE__<<" "<<__TIME__<<" "<<__LINE__<<" "<<"pthread_cond_init dailed"<<std::endl;
        }
    }

    void wait()
    {
        pthread_cond_wait(&m_cond,&m_mutex);
    }

    void broadcast()
    {
        pthread_cond_broadcast(&m_cond);
    }
    ~MyCondition()
    {
        pthread_cond_destroy(&m_cond);
    }

private:
    pthread_cond_t m_cond;
    pthread_mutex_t &m_mutex;
};
#endif
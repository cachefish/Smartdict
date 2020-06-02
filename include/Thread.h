#ifndef __THREAD_H__
#define __THREAD_H__
#include<iostream>
#include<stdlib.h>

class Thread
{
public:
    Thread():_threadId(0),_isRunning(false)
    {
            if(pthread_attr_init(&threadAttr)){
                std::cout<<__DATE__<<" "<<__TIME__<<" "__FILE__<<" "<<__LINE__<<":"<<"pthread_attr_init"<<std::endl;
                exit(-1);
            }
    }

    ~Thread()
    {
        pthread_attr_destroy(&threadAttr);
    }

    void start(void *arg=NULL)
    {
        if(_isRunning){
            return;
        }
        m_arg = arg;
        _isRunning = true;

        //将线程设置为detach
        if(pthread_attr_setdetachstate(&threadAttr,PTHREAD_CREATE_DETACHED))
        {
            std::cout<<__DATE__<<" "<<__TIME__<<" "<<__FILE__<<" "<<__LINE__<<":"<<"pthread_attr_setdetachstate"<<std::endl;
            exit(-1);
        }
        //创建线程
        if(pthread_create(&_threadId,&threadAttr,Thread::runInThread,this))
        {
            std::cout<<__DATE__<<" "<<__TIME__<<" "<<__FILE__<<" "<<__LINE__<<":"<<"pthread_create"<<std::endl;
            exit(-1);
        }

    }

protected:
    void *m_arg;
private:
    static void *runInThread(void *arg)
    {
        Thread*p=(Thread*)arg;
        p->run();
        return NULL;
    }

    virtual void run()=0;

private:

        pthread_t  _threadId;
        bool _isRunning;
        pthread_attr_t threadAttr;

};


#endif
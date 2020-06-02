#ifndef __MYTASK_H__
#define __MYTASK_H__
#include <iostream>
#include <string>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <string.h>
#include <map>
#include <queue>
#include "Myconf.h"
#include "MyResult.h"
#include "MyCompare.h"
#include <unistd.h>

class MyCache;

class MyTask
{
public:
    MyTask(MyConf&conf):queryWord_(""),vecDictPtr_(&(conf.vecDict)),mapIndexPtr_(&conf.mapIndex)
    {
        memset(&addr_,0,sizeof(addr_));
    }

    MyTask(const std::string &queryWord,const struct sockaddr_in &addr,MyConf&conf ):
    queryWord_(queryWord),addr_(addr),vecDictPtr_(&conf.vecDict),mapIndexPtr_(&conf.mapIndex)
    {

    }
    
    void excute(MyCache&cache);

    int length(const std::string&str)
    {
        int index;
        int len =0;
        for(index=0;index!=str.size();index++)
        {
            if(str[index]&(1<<7)){
                index++;
            }
            len++;
        }
        return len;
    }   

    ~MyTask()
    {
        close(peerfd_);
    }

    void satistic(std::set<int>&iset);  

private:
    void get_result();  //根据用户的查询词获取最终结果，并放入队列中
    int editdistance(const std::string&right);//计算right与用户输入查询词的距离
    int  triple_min(const int&a,const int&b,const int&c)
    {
        return a<b?(a<c?a:c):(b<c?b:c); 
    }

private:
    std::string  queryWord_; // 用户的查询词
    struct sockaddr_in addr_;// 用于保存用户端地址和端口号
    int peerfd_;

    std::vector<std::pair<std::string,int>>* vecDictPtr_;// 指向保存数据词典的指针
    std::map<std::string,std::set<int>>*mapIndexPtr_; // 指向词典索引的指针
    std::priority_queue<MyResult, std::vector<MyResult>, MyCompare> result_; // 用于保存查询结果的优先级队列

};
#endif
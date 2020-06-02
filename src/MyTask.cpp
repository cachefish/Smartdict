#include"MyTask.h"
#include"MyCache.h"
#include<functional>
#include<algorithm>


//执行任务，并将结果发回客户端
void MyTask::excute(MyCache&cache)
{
    peerfd_ = socket(AF_INET,SOCK_DGRAM,0);
    std::cout<<"task excute"<<std::endl;

    std::unordered_map<std::string,std::string>::iterator iter;
    iter = cache.isMapped(queryWord_);
    if(iter!=cache.hashmap_.end())
    {
        std::cout<<"cached"<<std::endl;
        int iret = sendto(peerfd_,(iter->second).c_str(),(iter->second).size(),0,(struct sockaddr*)&addr_,sizeof(addr_));
        std::cout<<"send:"<<iret<<std::endl;
    }else{
        std::cout<<"no cached "<<std::endl;
        get_result();
        if(result_.empty()){
            std::string res = "no answer !";
            int iret = sendto(peerfd_,res.c_str(),res.size(),0,(struct sockaddr*)&addr_,sizeof(addr_));
            std::cout<<"send:"<<iret<<std::endl;
        }else{
            /* code */
            MyResult res = result_.top();
            int iret = sendto(peerfd_,res.word_.c_str(),res.word_.size(),0,(struct sockaddr*)&addr_,sizeof(addr_));
            std::cout<<"send:"<<iret<<std::endl;
            cache.map_to_cache(queryWord_,res.word_);

        }
        

    }

}
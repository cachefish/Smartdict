#ifndef __MYCACHE_H__
#define __MYCACHE_H__

#include"MyLock.h"
#include<stdexcept>
#include<string>
#include<utility>
#include<fstream>
#include<unordered_map>

//数据成员为unordered_map
//控制互斥访问unordered_map的锁:hashmapLock_

class MyCache
{

public:
    std::unordered_map<std::string,std::string> hashmap_;

    void map_to_cache(std::string&key,std::string&value)
    {
        hashmapLock_.lock();
        hashmap_[key] = value;
        hashmapLock_.unlock();
    }

    //返回迭代器类型
    std::unordered_map<std::string,std::string>::iterator isMapped(const std::string&word)
    {
        return hashmap_.find(word);
    }
    //写入
    void write_to_file(std::ofstream &outfile)
    {
        hashmapLock_.lock();
        for(std::unordered_map<std::string,std::string>::iterator iter = hashmap_.begin();iter!=hashmap_.end();++iter)
        {
            outfile<<iter->first<<"\t"<<iter->second<<std::endl;
        }
        hashmapLock_.unlock();
    }
    //读
    void read_from_file(const std::string &fileName)
    {
        std::ifstream infile(fileName.c_str());
        if(!infile){
            std::cout<<"read file err  "<<fileName<<std::endl;
            throw std::runtime_error("open cache file fail");
        }
        std::string query,result;
        while(infile>>query>>result)
        {
            hashmap_.insert(std::make_pair(query,result));
        }
        infile.close();
    }
private:
    MyLock hashmapLock_;

};

#endif
#ifndef __MYCONF_H__
#define __MYCONF_H__
#include<iostream>
#include<fstream>
#include<sstream>
#include<stdexcept>
#include<set>
#include<map>
#include<utility>
#include<vector>
class MyConf
{
    friend class MyTask;
    friend class MySocket;
    friend class ThreadPool;

public:
    MyConf(const std::string&name):_infile(name.c_str())
    {
            if(!_infile){
                    std::cout<<__DATE__<<" "<<__TIME__<<" "<<__FILE__<<" "<<__LINE__<<" "<<"open failed!"<<std::endl;
                    exit(-1);
            }
        
            std::string line;
            while(getline(_infile,line)){
                std::istringstream instream(line);
                std::string key,value;
                instream>>key>>value;
                _mapConf.insert(make_pair(key,value));

            }
            _infile.close();

            //一次设置每个单词的每个字母所对应的索引
            for(int vecDictidx=0;vecDictidx!=vecDict.size();++vecDictidx)
            {
                setIndex(vecDictidx);
            }         
    }

    void setIndex(int vecDictidx)
    {
        std::string word,letter;  //单词以及单词中的每一个字母
        word = vecDict[vecDictidx].first;  //根据词典的下标来找每一个单词
        //遍历单词的每一个字母，制作索引
        for(int i = 0;i!=word.size();++i)
        {
            if(word[i]&(1<<7)){
                letter = word.substr(i,2);
                i++;
            }else{
                letter = word.substr(i,1);
            }
            mapIndex[letter].insert(vecDictidx); //将包含这个字母的单词 所在vector的下标放入set中
        }
    }

    std::map<std::string,std::string> &getMapConf()
    {
        return _mapConf;
    }


private:
    std::ifstream  _infile; 

    std::map<std::string,std::string> _mapConf;   //配置文件
    std::vector<std::pair<std::string,int>>  vecDict;  //词频
    std::map<std::string,std::set<int>> mapIndex;   //字母索引

};


#endif
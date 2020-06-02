#ifndef __MYRESULT_H__
#define __MYRESULT_H__
#include<string>

class MyResult
{
public:
    std::string  word_;  //保存词库中的词
    int frequence_;        //保存词库中词的词频
    int distance_;            //保存词库中的词与用户词的距离

};


#endif
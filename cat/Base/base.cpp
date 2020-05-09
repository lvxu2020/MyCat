#include "base.h"
#include <QCoreApplication>
#include <QTime>
#include <iostream>
#include <vector>
#include <iterator>
#include <regex>

Base::Base()
{

}
//qt是针对于图形界面的程序，如果直接sleep，那界面势必无法响应。无法刷新。
void BaseSpace::mySleep(int ms = 1000){
    QTime time;
    time.start();
    while (time.elapsed() < ms)
    {
        QCoreApplication::processEvents();
    }
}

/*
   用delim指定的正则表达式将字符串in分割，返回分割后的字符串数组
   delim 分割字符串的正则表达式
 */
std::vector<std::string> BaseSpace::mySplit(const std::string& in, const std::string& delim) {
    std::regex re{ delim };
    // 调用 std::vector::vector (InputIterator first, InputIterator last,const allocator_type& alloc = allocator_type())
    // 构造函数,完成字符串分割
    return std::vector<std::string> {
        std::sregex_token_iterator(in.begin(), in.end(), re, -1),
        std::sregex_token_iterator()
    };
}


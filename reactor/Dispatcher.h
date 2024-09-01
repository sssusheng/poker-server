#ifndef DISPATCHER_H
#define DISPATCHER_H

#include "Channel.h"
#include <string>


class EventLoop;

class Dispatcher {
public:
    Dispatcher(EventLoop *evloop);

    virtual ~Dispatcher();

    // 添加
    virtual int add() = 0;

    // 删除
    virtual int remove() = 0;

    // 修改
    virtual int modify() = 0;

    // 事件监测
    virtual int dispatch(int timeout = 2) = 0; // 单位: s
    inline void setChannel(Channel *channel) {
        m_channel = channel;
    }

protected:
    std::string m_name = std::string();
    Channel *m_channel;
    EventLoop *m_evLoop;
};


#endif //DISPATCHER_H

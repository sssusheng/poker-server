#ifndef POLLDISPATCHER_H
#define POLLDISPATCHER_H

#include "Channel.h"
#include "EventLoop.h"
#include "Dispatcher.h"
#include <poll.h>


class PollDispatcher : public Dispatcher {
public:
    PollDispatcher(EventLoop *evloop);

    ~PollDispatcher() override;

    // 添加
    int add() override;

    // 删除
    int remove() override;

    // 修改
    int modify() override;

    // 事件监测
    int dispatch(int timeout = 2) override; // 单位: s

private:
    int m_maxfd;
    pollfd *m_fds;
    const int m_maxNode = 1024;
};


#endif //POLLDISPATCHER_H

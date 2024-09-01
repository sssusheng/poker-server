#ifndef EPOLLDISPATCHER_H
#define EPOLLDISPATCHER_H

#include "EventLoop.h"
#include "Dispatcher.h"
#include <sys/epoll.h>


class EpollDispatcher : public Dispatcher {
public:
    explicit EpollDispatcher(EventLoop *evloop);

    ~EpollDispatcher() override;

    // 添加
    int add() override;

    // 删除
    int remove() override;

    // 修改
    int modify() override;

    // 事件监测
    int dispatch(int timeout = 2) override; // 单位: s

private:
    int epollCtl(int op) const;

private:
    int m_epfd;
    epoll_event *m_events;
    const int m_maxNode = 520;
};


#endif //EPOLLDISPATCHER_H

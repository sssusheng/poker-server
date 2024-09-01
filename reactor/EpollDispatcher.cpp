#include "EpollDispatcher.h"
#include "Dispatcher.h"
#include <sys/epoll.h>
#include <cstdlib>
#include <unistd.h>
#include <cstdio>


EpollDispatcher::EpollDispatcher(EventLoop *evloop): Dispatcher(evloop) {
    m_epfd = epoll_create(10);
    if (m_epfd == -1) {
        perror("epoll_create");
        exit(0);
    }
    m_events = new epoll_event[m_maxNode];
    m_name = "Epoll";
}

EpollDispatcher::~EpollDispatcher() {
    close(m_epfd);
    delete[]m_events;
}

int EpollDispatcher::epollCtl(const int op) const {
    epoll_event ev{};
    ev.data.fd = m_channel->getSocket();
    int events = 0;
    if (m_channel->getEvent() & static_cast<int>(FDEvent::ReadEvent)) {
        events |= EPOLLIN;
    }
    if (m_channel->getEvent() & static_cast<int>(FDEvent::WriteEvent)) {
        events |= EPOLLOUT;
    }
    ev.events = events;
    const int ret = epoll_ctl(m_epfd, op, m_channel->getSocket(), &ev);
    return ret;
}

int EpollDispatcher::add() {
    const int ret = epollCtl(EPOLL_CTL_ADD);
    if (ret == -1) {
        perror("epoll_ctr add");
        exit(0);
    }
    return ret;
}

int EpollDispatcher::remove() {
    const int ret = epollCtl(EPOLL_CTL_DEL);
    if (ret == -1) {
        perror("epoll_ctr delete");
        exit(0);
    }
    // 通过 channel 释放对应的 TcpConnection 资源
    m_channel->destroyCallback(const_cast<void *>(m_channel->getArg()));
    return ret;
}

int EpollDispatcher::modify() {
    const int ret = epollCtl(EPOLL_CTL_MOD);
    if (ret == -1) {
        perror("epoll_ctr modify");
        exit(0);
    }
    return ret;
}

int EpollDispatcher::dispatch(const int timeout) {
    int count = epoll_wait(m_epfd, m_events, m_maxNode, timeout * 1000);
    for (int i = 0; i < count; ++i) {
        const int events = m_events[i].events;
        int fd = m_events[i].data.fd;
        if (events & EPOLLERR || events & EPOLLHUP) {
            // 对方断开了连接, 删除 fd
            // epollRemove(Channel, evLoop);
            continue;
        }
        if (events & EPOLLIN) {
            m_evLoop->eventActive(fd, static_cast<int>(FDEvent::ReadEvent));
        }
        if (events & EPOLLOUT) {
            m_evLoop->eventActive(fd, static_cast<int>(FDEvent::WriteEvent));
        }
    }
    return 0;
}

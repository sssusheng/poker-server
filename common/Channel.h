#ifndef CHANNEL_H
#define CHANNEL_H

#include <functional>


// 定义文件描述符的读写事件
enum struct FDEvent {
    TimeOut = 0x01,
    ReadEvent = 0x02,
    WriteEvent = 0x04
};


class Channel {
public:
    // 定义函数指针
    using handleFunc = std::function<int(void *)>;

    Channel(int fd, FDEvent events, handleFunc readFunc, handleFunc writeFunc, handleFunc destroyFunc, void *arg);

    // 回调函数
    handleFunc readCallback;
    handleFunc writeCallback;
    handleFunc destroyCallback;

    // 修改fd的写事件(检测 or 不检测)
    void writeEventEnable(bool flag);

    // 判断是否需要检测文件描述符的写事件
    bool isWriteEventEnable();

    // 取出私有成员的值
    inline int getEvent() {
        return m_events;
    }

    inline int getSocket() {
        return m_fd;
    }

    inline const void *getArg() {
        return m_arg;
    }

private:
    // 文件描述符
    int m_fd;
    // 读写事件
    int m_events;
    // 回调函数的参数
    void *m_arg;
};


#endif //CHANNEL_H

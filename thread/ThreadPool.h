#ifndef THREADPOOL_H
#define THREADPOOL_H

#include "EventLoop.h"
#include "WorkerThread.h"
#include <vector>


// 定义线程池
class ThreadPool {
public:
    ThreadPool(EventLoop *mainLoop, int count);

    ~ThreadPool();

    // 启动线程池
    void run();

    // 取出线程池中的某个子线程的反应堆实例
    EventLoop *takeWorkerEventLoop();

private:
    // 主线程的反应堆模型
    EventLoop *m_mainLoop;
    bool m_isStart;
    int m_threadNum;
    std::vector<WorkerThread *> m_workerThreads;
    int m_index;
};


#endif //THREADPOOL_H

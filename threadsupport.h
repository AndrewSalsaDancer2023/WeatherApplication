#pragma once
#include <QThread>
#include <QWaitCondition>
#include <QMutex>
#include <QDebug>
#include <QByteArray>
#include <QPair>
#include <utility>
#include <functional>
#include <deque>
#include "geocoder.h"

typedef QPair<ForecastType, GeoData> result_type;
typedef std::function<void()> task_type;

class WorkQueue: public QObject
{
    Q_OBJECT
private:
    std::deque<task_type> tasks;
    QMutex tasks_mutex;
    QWaitCondition queueNotEmpty;

public:
    void push_task(const task_type& task)
    {
        QMutexLocker locker(&tasks_mutex);
        tasks.push_back(task);

        locker.unlock();
        queueNotEmpty.notify_one();
    }

    task_type pop_task()
    {
        QMutexLocker locker(&tasks_mutex);
        while(tasks.empty())
        {
             queueNotEmpty.wait(&tasks_mutex);
        }
        task_type ret = std::move(tasks.front());
        tasks.pop_front();

        return ret;
    }
};

class QueueThread : public QThread
{
    Q_OBJECT
    void run() {
        void* res = QThread::currentThreadId();
        qDebug() << "QueueThread id:" << res;

        while(true)
        {
            auto task = queue->pop_task();
            if(task)
            {
//             auto res1 = task();
//             emit resultReady(res1);
                task();
            }
            else
                break;
        }
        qDebug() << "Thread exit!!!" << '\n';
    }
public:
    void setWorkQueue(WorkQueue* q) { queue = q;}
//signals:
//    void resultReady(result_type);
private:
    volatile bool finish = false;
    WorkQueue* queue{nullptr};
};

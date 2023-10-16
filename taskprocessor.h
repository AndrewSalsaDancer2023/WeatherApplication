#pragma once
#include <boost/thread/thread.hpp>
#include <boost/asio/io_service.hpp>
#include <boost/noncopyable.hpp>

template <class T>
    struct task_wrapped {
private:
    T task_unwrapped_;
public:
    explicit task_wrapped(const T& f)
        : task_unwrapped_(f)
        {}

    void operator()() const
    {
    //	Сброс	прерывания.
        try {
            boost::this_thread::interruption_point();
        } catch(const boost::thread_interrupted&){}
        try
        {                                    //	Выполнение	задачи.
            task_unwrapped_();
        }
        catch (const std::exception& e)
        {
         //   std::cerr<<	"Exception:	"	<<	e.what()	<<	'\n';
        }
        catch (const boost::thread_interrupted&)
        {
           //  std::cerr<< "Thread interrupted\n";
         }
        catch (...) {
             //std::cerr<< "Unknown exception\n";
         }
    }
};

template <class T>
    task_wrapped<T> make_task_wrapped(const T& task_unwrapped) {
     return task_wrapped<T>(task_unwrapped);
    }

class tasks_processor: private boost::noncopyable
{
    protected:
     static boost::asio::io_service& get_ios() {
         static boost::asio::io_service ios;
 //        static boost::asio::io_service::work work(ios);
         return ios;
     }

    public:
     template <class T>
        static void push_task(const T& task_unwrapped) {
            get_ios().post(make_task_wrapped(task_unwrapped));
         }

    static void start()
    {
        get_ios().run();
    }

    static void stop()
    {
        get_ios().stop();
    }
};

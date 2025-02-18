#include "hdr/WorkerThread.hpp"

#define tn template<std::size_t numOfThreads> 
#define wt WorkerThread<numOfThreads>
const int required_threads{8};

tn wt::WorkerThread() {_inite();}
tn wt::~WorkerThread() {_stop();}

tn Result wt::_inite()
{
    for(std::size_t i=0; i < numOfThreads; ++i) { available_threads.insert(i;)}
    return Result::SUCCESS;
}

tn Result wt::_exe_impl(Task& i_task)
{
    if(available_threads.empty()) return Result::NO_AVAILABLE_THREAD

    std::size_t index_thread = *available_threads.begin();
    available_threads.erase(index_thread);
    threads[index_thread] = std::thread([this,&i_task,index_thread] () 
    {
        i_task();
        available_threads.insert(index_thread);
    });

    return Result::SUCCESS;
}

tn Result wt::_exe(Task& i_task){ return _exe_impl(i_task);}
tn bool wt::is_any_thread_available() const {return !available_threads.empty();}


template class WorkerThread<required_threads>;


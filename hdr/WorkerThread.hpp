#pragma once

#include <array>
#include <set>
#include <thread>

#include "hdr/Task.hpp"
#include "hdr/Result.hpp"

template<std::size_t numOfThreads>
class WorkerThread
{
    private:
        std::array<std::thread , numOfThreads > threads;
        std::set<std::size_t> available_threads;

        Result _inite();
        Result _stop();
        Result _exe_impl(Task& i_task);
    
    public:
        WorkerThread();
        ~WorkerThread();

        Result _exe(Task& i_task);
        bool is_any_thread_available() const;
};
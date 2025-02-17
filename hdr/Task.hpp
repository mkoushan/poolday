#pragma once
#include <functional>

class Task
{
    public:
        using TaskFunc = std::function<void()>;
        Task(TaskFunc func);
        void operator()() const;

    private:
        TaskFunc taskfunction;
};
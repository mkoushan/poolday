#pragma once

#include <condition_variable>
#include <cstdlib>
#include <mutex>
#include <queue>
#include <thread>

#include "log.hpp"
#include "result.hpp"
#include "task.hpp"

template <std::size_t NumberOfThreads> class ThreadPool {
  std::array<std::thread, NumberOfThreads> worker_threads;
  std::queue<Task> tasks;
  std::mutex queue_mutex;
  std::condition_variable condition;
  bool stop{false};

public:
  ThreadPool() {
    for (std::size_t i = 0; i < NumberOfThreads; ++i) {
      auto &thread = worker_threads[i];
      thread = std::thread([this, i] {
        while (true) {
          Task task(0, 0);
          {
            std::unique_lock<std::mutex> lock(queue_mutex);

            condition.wait(lock, [this] { return stop || !tasks.empty(); });

            if (stop && tasks.empty())
              return;

            task = std::move(tasks.front());
            tasks.pop();
          }

          const auto result = task.execute();

          if (result == Result::TASK_COMPLETED)
            INFO(std::format("Task {} has been done with thread {}\n",
                             task.task_id(), i));
        }
      });
    }
  }

  ~ThreadPool() {
    {
      std::unique_lock<std::mutex> lock(queue_mutex);
      stop = true;
    }

    condition.notify_all();

    for (std::thread &thread : worker_threads) {
      thread.join();
    }
  }

  Result add_task(Task &&task) {
    {
      std::unique_lock<std::mutex> lock(queue_mutex);
      if (stop) {
        throw std::runtime_error("enqueue on stopped ThreadPool");
      }
      tasks.emplace(std::forward<Task>(task));
    }
    condition.notify_one();

    INFO(std::format("Adding task {} with exe_time {}\n", task.task_id(),
                     task.get_exe_time()));

    return Result::SUCCESS;
  }
};

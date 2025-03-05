#pragma once

#include <chrono>
#include <cstddef>
#include <thread>

#include "log.hpp"
#include "result.hpp"

class Task {
  std::size_t exe_time;
  std::size_t id;

public:
  Task(const std::size_t i_id, const std::size_t i_exe_time)
      : exe_time(i_exe_time), id(i_id) {}

  Result execute() {
    INFO(std::format("Executing task {} with exe_time {} \n", id, exe_time));

    while (true) {
      if (exe_time > 0) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        --exe_time;
      } else
        return Result::TASK_COMPLETED;
    }

    return Result::FAILURE;
  }

  bool is_task_done() const { return exe_time == 0; }

  std::size_t task_id() const { return id; }
  std::size_t get_exe_time() const { return exe_time; }
};

#include <iostream>
#include <string>
#include <vector>

#include "log.hpp"
#include "task.hpp"
#include "thread_pool.hpp"

int main(int argc, char *argv[]) {
  constexpr std::size_t NumberOfThreads = 8;
  constexpr auto LogLevel = LOG_LEVEL::INFO;

  if (argc < 2 || (argc - 2) != std::stoi(argv[1]) * 2) {
    std::cerr << "use: ./poolday number_of_tasks "
                 "task_1_arrive_time task_1_exe_time ...\n";
    return 1;
  }

  const std::size_t number_of_tasks = std::stoi(argv[1]);

  // arrive_time exe_time
  std::vector<std::pair<std::size_t, std::pair<std::size_t, std::size_t>>>
      tasks;

  INFO(std::format("Number of tasks = {}\n", number_of_tasks));

  for (std::size_t i = 2; i <= number_of_tasks * 2; i += 2) {
    tasks.push_back({std::stoi(argv[i]), {std::stoi(argv[i + 1]), i / 2}});
  }

  std::sort(tasks.begin(), tasks.end());

  for (const auto &el : tasks)
    INFO(std::format("Task {} with exe_time {} and arrive_time {}\n",
                     el.second.second, el.second.first, el.first));

  ThreadPool<NumberOfThreads> thread_pool;

  for (const auto task_pair : tasks) {
    const auto id = task_pair.second.second;
    const auto exe_time = task_pair.second.first;

    thread_pool.add_task(Task(id, exe_time));
  }
  INFO("All tasks has been added successfully.\n");

  return 0;
}

#include "hdr/Task.hpp"

Task::Task(TaskFunc func ) : taskfunction(func) {}

void Task::operator()() const {if(taskfunction) taskfunction();}
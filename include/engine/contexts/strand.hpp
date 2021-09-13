#pragma once
#include <queue>

#include <iostream>
#include <map>
#include <thread>

#include "basic_types.hpp"
#include "concepts.hpp"
#include "task_utils.hpp"

namespace ngn
{

template<QueueCallable TaskQueue = std::queue<Task>>
struct Strand;

template<QueueCallable Q>
inline void post(Strand<Q>& context, Task f);

template<QueueCallable Q>
inline void post(Strand<Q>& context, Task f, Task handler);

template<QueueCallable Q>
inline void wait(Strand<Q>& context);

void start(Strand<>& context);

void schedule(std::queue<std::pair<TaskId, Task>>& queue, Task task, TaskId id);

template<QueueCallable TaskQueue>
struct Strand
{
  ~Strand();

  TaskQueue _queue;
  std::mutex _task_queue_mutex;
  std::condition_variable _task_queue_cv;

  std::queue<TaskId> _finished_tasks;
  std::mutex _completion_queue_mutex;

  std::map<TaskId, Task> _tasks_completion_handlers;

  std::thread _thread;

  // maybe use an enum for signals
  bool _is_running : 1 = false;
  bool _stop : 1 = false;
  size_t _curr_task_id = 0;
};

} // namespace ngn

namespace ngn
{
template<QueueCallable Q>
inline void wait(Strand<Q>& context)
{
  wait(context._queue);
}

template<QueueCallable Q>
inline void post(Strand<Q>& context, Task f)
{
  schedule(context._queue, f);
  start(context);
}

template<QueueCallable Q>
inline void post(Strand<Q>& context, Task f, Task handler)
{
  throw std::runtime_error("todo");
}

} // namespace ngn

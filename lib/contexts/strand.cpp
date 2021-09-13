#include "engine/contexts/strand.hpp"

#include "engine/contexts/queue_utils.hpp"

namespace ngn
{

void schedule(std::queue<std::pair<TaskId, Task>>& queue, Task task, TaskId id)
{
  queue.push(std::make_pair(std::move(id), std::move(task)));
}

void start(Strand<>& context)
{
  if (!context._is_running)
  {
    context._thread = std::thread([&context]() {
      while (!context._stop)
      {
        // Run all task present in the queue
        while (!empty(context._queue))
        {
          // request the access to the queue in writing mode
          auto lock = std::unique_lock(context._task_queue_mutex);

          // take the front task to be run
          auto [_, task] = require_task(context._queue);
          // remove task from queue

          // free the queue access write
          lock.unlock();

          // run task
          task();

          //_completed_tokens
        }

        // take a lock and wait for a new task to be added to the queue
        auto lock = std::unique_lock(context._task_queue_mutex);

        context._task_queue_cv.wait(lock, [&context]() { return !empty(context._queue) || context._stop; });
      }

      // reinit
      context._is_running = false;
      context._stop = false;
    });

    // Initialize the status of the context
    context._is_running = true;
    context._stop = false;
  }
}

template<>
Strand<>::~Strand()
{
  using namespace std::chrono_literals;
  while (!empty(_queue))
  {
    std::this_thread::sleep_for(1ms);
  }
  _stop = true;
  _task_queue_cv.notify_one();
  _thread.join();
}

} // namespace ngn

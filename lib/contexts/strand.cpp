#include "engine/contexts/strand.hpp"

namespace ngn
{

void wait(Strand &context)
{
    using namespace std::chrono_literals;
    while (!context._task_queue.empty())
    {
        std::this_thread::sleep_for(1ms);
    }
}

void start(Strand &context)
{
    if (!context._is_running)
    {
        context._thread = std::thread([&context]() {
            while (!context._stop)
            {
                // Run all task present in the queue
                while (!context._task_queue.empty())
                {
                    // request the access to the queue in writing mode
                    auto lock = std::unique_lock(context._mutex);

                    // take the front task to be run
                    auto task = std::move(context._task_queue.front());

                    // remove task from queue
                    context._task_queue.pop();

                    // free the queue access write
                    lock.unlock();

                    // run task
                    task();
                }

                // take a lock and wait for a new task to be added to the queue
                auto lock = std::unique_lock(context._mutex);

                context._cv.wait(lock, [&context]() { return !context._task_queue.empty() || context._stop; });
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

Strand::~Strand()
{
    using namespace std::chrono_literals;
    while (!_task_queue.empty())
    {
        std::this_thread::sleep_for(1ms);
    }
    _stop = true;
    _cv.notify_one();
    _thread.join();
}

} // namespace ngn

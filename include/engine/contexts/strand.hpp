#pragma once
#include <thread>
#include <queue>
#include "contexts_api.hpp"
#include <iostream>

namespace ngn {

struct Strand;

template<typename FuncType>
void post(Strand& context, FuncType f);

template<typename FuncType>
std::future<void> post(Strand& context, FuncType f, tokens::UseFuture);

void wait(Strand& context);

struct Strand
{
  ~Strand();

  template<typename FuncType>
  friend void post(Strand& context, FuncType f);

  template<typename FuncType>
  friend std::future<void> post(Strand& context, FuncType f, tokens::UseFuture);

  friend void wait(Strand& context);

private:

  void _start()
  {
    if(!_is_running)
    {
      _thread = std::thread([this]()
      {
         while(!_stop)
         {
             // Run all task present in the queue
             while(!_task_queue.empty())
             {
               // request the access to the queue in writing mode
               auto lock = std::unique_lock(_mutex);

               // take the front task to be run
               auto task = std::move(_task_queue.front());

               // remove task from queue
               _task_queue.pop();

               // free the queue access write
               lock.unlock();

               // run task
               task();

             }

             //take a lock and wait for a new task to be added to the queue
             auto lock = std::unique_lock(_mutex);

             this->_cv.wait(lock, [this](){
               return !_task_queue.empty() || _stop;
             });
         }

         // reinit
         _is_running = false;
         _stop       = false;
      });

      // Initialize the status of the context
      _is_running = true;
      _stop       = false;
    }
  }

  std::queue<std::packaged_task<void()>> _task_queue;
  std::thread _thread;
  std::mutex _mutex;
  std::condition_variable _cv;

  // using bitfield or enum for status
  bool _is_running/*:1*/ = false;
  bool _stop/*:1*/ = false;
};


template<typename FuncType>
void post(Strand& context, FuncType f)
{
   context._task_queue.push(std::packaged_task<void()>(std::move(f)));
   context._start();
}

template<typename FuncType>
std::future<void> post(Strand& context, FuncType f, tokens::UseFuture)
{
    auto task = std::packaged_task<void()>(std::move(f));
    auto future = task.get_future();
    context._task_queue.push(std::move(task));
   context._start();
    return future;
}

void wait(Strand& context)
{
  using namespace std::chrono_literals;
  while(!context._task_queue.empty()){
      std::this_thread::sleep_for(1ms);
  }
}

Strand::~Strand()
{
    using namespace std::chrono_literals;
    while(!_task_queue.empty()){
      std::this_thread::sleep_for(1ms);
    }
    _stop = true;
    _cv.notify_one();
   _thread.join();
}

}

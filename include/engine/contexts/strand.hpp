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

void start(Strand& context);

struct Strand
{
  ~Strand();

  template<typename FuncType>
  friend void post(Strand& context, FuncType f);

  template<typename FuncType>
  friend std::future<void> post(Strand& context, FuncType f, tokens::UseFuture);

  friend void wait(Strand& context);

  friend void start(Strand& context);

private:

  std::queue<std::packaged_task<void()>> _task_queue;
  std::thread _thread;
  std::mutex _mutex;
  std::condition_variable _cv;

  // maybe use an enum for status
  bool _is_running:1 = false;
  bool _stop:1 = false;
};


template<typename FuncType>
void post(Strand& context, FuncType f)
{
   context._task_queue.push(std::packaged_task<void()>(std::move(f)));
   start(context);
}

template<typename FuncType>
std::future<void> post(Strand& context, FuncType f, tokens::UseFuture)
{
    auto task = std::packaged_task<void()>(std::move(f));
    auto future = task.get_future();
    context._task_queue.push(std::move(task));
    start(context);
    return future;
}


}

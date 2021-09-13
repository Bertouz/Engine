#pragma once
#include "concepts.hpp"
#include "err_codes.hpp"
#include <chrono>
#include <thread>
#include <functional>

namespace ngn {

template<Queue Q>
inline void wait(const Q& queue);

template<Queue Q>
inline bool empty(const Q& queue);

template<QueueCallable Q, Callable C>
inline void schedule(Q& s, C&& f);

template<QueueCallable Q>
inline auto require_task(Q& s) -> std::tuple<ErrCode, typename Q::value_type>;
}

namespace ngn {

template<Queue Q>
inline void wait(const Q& queue)
{
  using namespace std::chrono_literals;
  while (!empty(queue))
  {
    std::this_thread::sleep_for(1ms);
  }
}

template<Queue Q>
inline bool empty(const Q& queue)
{
  return queue.empty();
}

template<QueueCallable Q, Callable C>
inline void schedule(Q& s, C&& f)
{
  s.push(std::move(f));
}

template<QueueCallable Q>
inline auto require_task(Q& s) -> std::tuple<ErrCode, typename Q::value_type>
{
  if (!s.empty())
  {
    auto task = s.front();
    s.pop();
    return std::make_tuple(ErrCode::NoError, task);
  }
  else
  {
    return std::make_tuple(ErrCode::ErrorNoTaskScheduled, typename Q::value_type([]() {}));
  }
}


}

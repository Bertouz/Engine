#pragma once
#include <queue>

#include <functional>
#include <future>

#include "err_codes.hpp"
#include "tokens.hpp"

namespace ngn
{

using Task = std::function<void()>;
using TaskId = uint32_t;
using ThreadStatus = uint32_t;

struct CompletionToken
{
  TaskId id;
  ThreadStatus status;
};

} // namespace ngn

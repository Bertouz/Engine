#pragma once

/**
 * @defgroup Tokens
 * @ingroup Contexts
 */

namespace ngn
{

namespace tokens
{

/**
 * @brief The UseFuture struct - Tag indicating that we want to use the future associated with an asynchronous task
 * @ingroup Tokens
 */
struct UseFuture
{
};

inline constexpr UseFuture use_future;
} // namespace tokens

} // namespace ngn

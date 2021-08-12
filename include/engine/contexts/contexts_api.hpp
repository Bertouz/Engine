#pragma once
#include "tokens.hpp"
#include <future>

namespace ngn
{

/**
 * @brief post - Give a callable to a context to be run
 * @param context - Context in which we want to run the callable
 * @param f - Callable which must have a signature void() if not explicitly said otherwise
 * @ingroup Contexts
 */
template <typename ContextType, typename FuncType> void post(ContextType &context, FuncType f);

/**
 * @brief post - Give a callable to a context to be run and give the future associated to the use
 * @param context - Context in which we want to run the callable
 * @param f - Callable which must have a signature void() if not explicitly said otherwise
 * @return thre future of the task so  that the user can wait on it
 * @ingroup Contexts
 */
template <typename ContextType, typename FuncType>
std::future<void> post(ContextType &context, FuncType f, tokens::UseFuture);

/**
 * @brief wait - wait for the context to finish all its task before returning
 * @param context
 * @ingroup Contexts
 */
template <typename ContextType> void wait(ContextType &context);

/**
 * @brief start - Request the context to start all its worker to process tasks
 * If the context is already processing tasks then the fonction does nothing
 * The function return as soon as all worker are started
 * @param context - context we want to start
 * @ingroup Contexts
 */
template <typename ContextType> void start(ContextType &context);

} // namespace ngn

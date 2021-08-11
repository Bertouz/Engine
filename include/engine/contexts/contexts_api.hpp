#pragma once
#include <future>
#include "tokens.hpp"

namespace ngn {

/**
 * @brief post - Give a callable to a context to be run
 * @param context - Context in which we want to run the callable
 * @param f - Callable which must have a signature void() if not explicitly said otherwise
 * @ingroup Contexts
 */
template<typename ContextType, typename FuncType>
void post(ContextType& context, FuncType f);

/**
 * @brief post - Give a callable to a context to be run and give the future associated to the use
 * @param context - Context in which we want to run the callable
 * @param f - Callable which must have a signature void() if not explicitly said otherwise
 * @return thre future of the task so  that the user can wait on it
 * @ingroup Contexts
 */
template<typename ContextType, typename FuncType>
std::future<void> post(ContextType& context, FuncType f, tokens::UseFuture);

/**
 * @brief wait - wait for the context to finish all its task before returning
 * @param context
 */
template<typename ContextType>
void wait(ContextType& context);



}

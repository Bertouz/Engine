#pragma once
#include <concepts>
#include <type_traits>

namespace ngn {
template<typename T>
concept NoInvokeResult = std::is_same_v<void, std::invoke_result_t<T>>;

/**
 * @note We cant have std::function noexcept so its of no use hear
 */
template<typename T>
concept NoThrowInvokable = std::is_nothrow_invocable_v<T>;

template<typename T>
concept Callable = /*NoThrowInvokable<T> &&*/ NoInvokeResult<T>;


template<typename T>
concept Queue = requires(T a, typename T::value_type c)
{
  a.push(c);
  {a.front()}->std::convertible_to<typename T::value_type>;
  a.pop();
  {a.empty()}->std::same_as<bool>;
};

template<typename T>
concept QueueCallable = Queue<T> && Callable<typename T::value_type>;

}

#include "engine/contexts/task_utils.hpp"

namespace ngn {

std::thread::native_handle_type get_worker_handle()
{
#ifdef __linux__
  return pthread_self();
#elif _WIN32
  static_assert(true, "TBD && Todo");
#endif
}


}

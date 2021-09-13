#pragma once
#include <thread>

namespace ngn {

std::thread::native_handle_type get_worker_handle();

}


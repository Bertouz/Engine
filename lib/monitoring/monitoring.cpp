#include "engine/monitoring/monitoring.hpp"
#include <filesystem>
namespace ngn
{
std::ifstream open_ifstream_procstat(pid_t pid, pid_t tid)
{

  std::filesystem::path statfile = std::filesystem::path("/proc") / std::to_string(pid) /
                                   std::filesystem::path("task") / std::to_string(tid) / std::filesystem::path("stat");

  if (std::filesystem::exists(statfile))
  {
    return std::ifstream(statfile.string());
  }
  throw std::runtime_error("THe file :" + statfile.string() + " doesnt exists");
}

ProcStatData parsing_procstat(std::istream& in)
{
		ProcStatData stat;

		in >> stat.pid
		   >> stat.name
		   >> stat.state
		   >> stat.ppid
		   >> stat.pgrp
		   >> stat.session
		   >> stat.tty_nr
		   >> stat.tpgid
		   >> stat.flags
		   >> stat.minflt
		   >> stat.cminflt
		   >> stat.majflt
		   >> stat.cmajflt
		   >> stat.utime
		   >> stat.stime
		   >> stat.cutime
		   >> stat.cstime
		   >> stat.priority
		   >> stat.nice
		   >> stat.num_threads
		   >> stat.itrealvalue
		   >> stat.starttime
		   >> stat.vsize
		   >> stat.rss
		   >> stat.rsslim
		   >> stat.startcode
		   >> stat.endcode
		   >> stat.startstack
		   >> stat.kstkesp
		   >> stat.kstkeip
		   >> stat.signal
		   >> stat.blocked
		   >> stat.sigignore
		   >> stat.sigcatch
		   >> stat.wchan
		   >> stat.nswap
		   >> stat.cnswap
		   >> stat.exit_signal
		   >> stat.processor
		   >> stat.rt_priority
		   >> stat.policy
		   >> stat.delayacct_blkio_ticks
		   >> stat.guest_time
		   >> stat.cguest_time
		   >> stat.start_data
		   >> stat.end_data
           >> stat.start_brk
		   >> stat.arg_start
		   >> stat.arg_end
		   >> stat.env_start
		   >> stat.env_end
		   >> stat.exit_code;
		return stat;
}

}

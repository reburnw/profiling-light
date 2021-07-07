#include "Profiling.hpp"


Profiler::Profiler() {
    std::cout << "Profiler Init" << std::endl;
    funcCall.push("TOTAL");
    func_map["TOTAL"] = 0;
    cnt_map["TOTAL"] = 1;
    used_map["TOTAL"] = 0;
    return ;
}

Profiler::~Profiler() {
    for (auto k:func_map) {
        std::cout << "Log: " << k.first << 
                    " TimeUse: " << k.second << 
                    " Cnt: "<<cnt_map[k.first]<<
                    " Clear: "<< k.second-used_map[k.first] <<
                    std::endl;
    }
    std::cout << "Profiler Destroy" << std::endl;
    return ;
}

void Profiler::log(std::string s, long long t) {
    funcCall.pop();
    auto& fa = funcCall.top();
    used_map[fa] += t;
    if(func_map.find(s)==func_map.end()) {
        func_map[s] = t;
        cnt_map[s] = 1;
    } else {
        func_map[s] += t;
        cnt_map[s] += 1;
    }
}

void Profiler::access(std::string s) {
    funcCall.push(s);
}

ProfileUnit::ProfileUnit(Profiler* p, std::string s)
:profiler(p),f_name(s ) {
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &time_start);
    profiler->access(f_name);
    return ;
}

ProfileUnit::~ProfileUnit() {
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &time_end);
    profiler->log( f_name, 
        1000000000LL * (time_end.tv_sec-time_start.tv_sec) + (time_end.tv_nsec-time_start.tv_nsec));
}
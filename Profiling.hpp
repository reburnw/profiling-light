
#ifndef PROFILE_C
#define PROFILE_C

#include <map>
#include <stack>
#include <iostream>
#include <time.h>

// contents of the header
class Profiler {
public:
    Profiler() ;
    ~Profiler() ;
    void log(std::string s, long long t);
    void access(std::string s);
private:
    std::map<std::string, long long> func_map;
    std::map<std::string, long long> cnt_map;
    std::map<std::string, long long> used_map;
    std::stack<std::string> funcCall;
};

class ProfileUnit {
public:
    ProfileUnit(Profiler* p, std::string f) ;
    ~ProfileUnit() ;
    Profiler* profiler;
    std::string f_name;
    timespec time_start, time_end;
};

#endif // PROFILE_C

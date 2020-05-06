#pragma once
//#include <cstdio>
//#include <cerrno>
//#include <cstring>
//
//#ifdef NDEBUG
//#define DEBUG(M, ...)
//#else
//#define DEBUG(M, ...) fprintf(stderr, "DEBUG %s:%d: " M "\n", __FILE__, __LINE__, ##__VA_ARGS__)
//#endif
//
//#define CLEAN_ERRNO() (errno == 0 ? "None" : strerror(errno))
//#define LOG_ERR(M, ...) fprintf(stderr, "[ERROR] (%s:%d: errno: %s) " M "\n", __FILE__, __LINE__, CLEAN_ERRNO(), ##__VA_ARGS__)
//#define LOG_WARN(M, ...) fprintf(stderr, "[WARN] (%s:%d: errno: %s) " M "\n", __FILE__, __LINE__, CLEAN_ERRNO(), ##__VA_ARGS__)
//#define LOG_INFO(M, ...) fprintf(stderr, "[INFO] (%s:%d) " M "\n", __FILE__, __LINE__, ##__VA_ARGS__)
//#define CHECK(A, M, ...) if(!(A)) { LOG_ERR(M, ##__VA_ARGS__); errno=0; goto error; }
//#define SENTINEL(M, ...)  { LOG_ERR(M, ##__VA_ARGS__); errno=0; goto error; }
//#define CHECK_MEM(A) CHECK((A), "Out of memory.")
//#define CHECK_DEBUG(A, M, ...) if(!(A)) { DEBUG(M, ##__VA_ARGS__); errno=0; goto error; }
// Source: http://c.learncodethehardway.org/book/ex20.html.


namespace Dbg {
    bool has_user_set_any_breakpoints();
    bool breakstep();
    void bpset(const memory_address addr);
    void bprm(const memory_address addr);
    bool isbp(const memory_address addr);
}

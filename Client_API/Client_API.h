#ifndef _Client_API_
#define _Client_API_

#include "../include/zookeeper.h"
#include "string"

#define DEFAULT_TIMEOUT 10000
typedef void (*f)(std::string);

class Client_API{
public:
    static bool Connect(std::string add_port);
    static bool Listen_root(std::string path, void (*func)(std::string) = NULL, bool first = true);
    static bool Create_Child(int child_type);
    static bool Version_Check(int version);
    static int Get_Version();
    static std::string Get_Message();
    static void Close();
    
private:
    static zhandle_t* zh;
    static std::string add_port;
    static std::string root_path;
    static std::string message;
    static int version;
    static f func;

    static void watcher(zhandle_t *zzh, int type, int state, const char *path,void *watcherCtx);
    static void zk_string_completion(int rc, const char *value, const void *data);
    static void zk_data_completion(int rc, const char *value, int value_len, const struct Stat *stat, const void *data);
};

#endif

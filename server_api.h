#ifndef _SERVERAPI_
#define _SERVERAPI_

#include "include/zookeeper.h"

#include "string"

#define DEFAULT_TIMEOUT 10000

class ServerApi{
    public:
    static bool Connect(std::string addr_port);
    static bool CreateRoot(std::string path);
    static bool ChangeMessage(std::string message);
    static bool DeleteRoot();
    static void Close();

    private:
    static std::string addr_port_;
    static std::string root_path_;
    static zhandle_t* zh_;

    static void watcher(zhandle_t *zh, int type, int state, const char *path,void *watcherCtx);
    static void zk_string_completion(int rc, const char *value, const void *data);
    static void zk_stat_completion(int rc, const struct Stat *stat, const void *data);
};

#endif
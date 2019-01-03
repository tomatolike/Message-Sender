#ifndef _SERVER_API_
#define _SERVER_API_

#include "../include/zookeeper.h"
#include "string"

#define DEFAULT_TIMEOUT 10000

class Server_API{
    public:
    static bool Connect(std::string addr_port);
    static bool Create_root(std::string path);
    static bool Change_message(std::string message);
    static bool Delete_root();
    static void Close();

    private:
    static std::string addr_port;
    static std::string root_path;
    static zhandle_t* zh;

    static void watcher(zhandle_t *zh, int type, int state, const char *path,void *watcherCtx);
    static void zk_string_completion(int rc, const char *value, const void *data);
    static void zk_stat_completion(int rc, const struct Stat *stat, const void *data);
};

#endif
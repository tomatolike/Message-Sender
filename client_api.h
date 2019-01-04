#ifndef _ClientAPI_
#define _ClientAPI_

#include "include/zookeeper.h"

#include "string"

#define DEFAULT_TIMEOUT 10000
typedef void (*f)(std::string);

class ClientApi{
public:
    static bool Connect(std::string add_port);
    static bool ListenRoot(std::string path, void (*func)(std::string) = NULL, bool first = true);
    static bool CreateChild(int child_type);
    static bool VersionCheck(int version);
    static int GetVersion();
    static std::string GetMessage();
    static void Close();
    
private:
    static zhandle_t* zh_;
    static std::string add_port_;
    static std::string root_path_;
    static std::string message_;
    static int version_;
    static f func_;

    static void watcher(zhandle_t *zzh, int type, int state, const char *path,void *watcherCtx);
    static void zk_string_completion(int rc, const char *value, const void *data);
    static void zk_data_completion(int rc, const char *value, int value_len, const struct Stat *stat, const void *data);
};

#endif

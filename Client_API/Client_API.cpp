#include "Client_API.h"
#include "iostream"


zhandle_t* Client_API::zh = NULL;
std::string Client_API::message = "";
std::string Client_API::add_port = "";
std::string Client_API::root_path = "";
int Client_API::version = 0;
f Client_API::func = NULL;

bool Client_API::Connect(std::string add_port)
{
    //set debug level
    zoo_set_debug_level(ZOO_LOG_LEVEL_WARN);
    
    //Connection
    zh = zookeeper_init(add_port.c_str(), Client_API::watcher, DEFAULT_TIMEOUT, 0, 0, 0);
    if(zh == NULL){
        return false;
    }
    return true;
}

bool Client_API::Listen_root(std::string path, void (*func)(std::string), bool first)
{
    int getret;
    if(first){
        char buf[1024];
        int buflen = 1024;
        struct Stat *temp_stat = new struct Stat;
        getret = zoo_get(zh,path.c_str(),1,buf,&buflen,temp_stat);
        if(getret != ZOK){
            return false;
        }
        Client_API::message = buf;
        Client_API::version = temp_stat->version;
    }
    else{
        getret = zoo_aget(zh, path.c_str(), 1, Client_API::zk_data_completion, (const void *)func);
        if(getret != ZOK){
            return false;
        }
    }
    Client_API::root_path = path;
    Client_API::func = func;
    return true;
}

bool Client_API::Create_Child(int child_type = ZOO_EPHEMERAL|ZOO_SEQUENCE)
{
    int ret = zoo_acreate(zh, Client_API::root_path.c_str(), "child", 5, &ZOO_OPEN_ACL_UNSAFE, child_type, Client_API::zk_string_completion, "CREATE_CHILD");
    if(ret != ZOK){
        return false;
    }
    return true;
}

bool Client_API::Version_Check(int version)
{
    if(Client_API::version == version) return true;
    return false;
}

int Client_API::Get_Version()
{
    return Client_API::version;
}

std::string Client_API::Get_Message()
{
    return Client_API::message;
}

void Client_API::Close()
{
    if(zh != NULL) zookeeper_close(zh);
    zh = NULL;
}

void Client_API::watcher(zhandle_t *zzh, int type, int state, const char *path,void *watcherCtx)
{
    if(type == ZOO_CHANGED_EVENT){
        //new message, need to get it. Get root first
        std::string root = path;
        Client_API::Listen_root(root, Client_API::func, false);
    }
}

void Client_API::zk_string_completion(int rc, const char *value, const void *data)
{
}

void Client_API::zk_data_completion(int rc, const char *value, int value_len, const struct Stat *stat, const void *data)
{

    Client_API::message = value;
    Client_API::version = stat->version;

    if(data != NULL){
        Client_API::func(Client_API::message);
    }
}

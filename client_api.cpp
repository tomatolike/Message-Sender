#include "client_api.h"

#include "iostream"

zhandle_t* ClientApi::zh_ = NULL;
std::string ClientApi::message_ = "";
std::string ClientApi::add_port_ = "";
std::string ClientApi::root_path_ = "";
int ClientApi::version_ = 0;
f ClientApi::func_ = NULL;

bool ClientApi::Connect(std::string add_port)
{
    //set debug level
    zoo_set_debug_level(ZOO_LOG_LEVEL_WARN);
    
    //Connection
    zh_ = zookeeper_init(add_port.c_str(), ClientApi::watcher, DEFAULT_TIMEOUT, 0, 0, 0);
    if(zh_ == NULL){
        return false;
    }
    return true;
}

bool ClientApi::ListenRoot(std::string path, void (*func)(std::string), bool first)
{
    int getret;
    if(first){
        char buf[1024];
        int buflen = 1024;
        struct Stat *temp_stat = new struct Stat;
        getret = zoo_get(zh_,path.c_str(),1,buf,&buflen,temp_stat);
        if(getret != ZOK){
            return false;
        }
        ClientApi::message_ = buf;
        ClientApi::version_ = temp_stat->version;
    }
    else{
        getret = zoo_aget(zh_, path.c_str(), 1, ClientApi::zk_data_completion, (const void *)func);
        if(getret != ZOK){
            return false;
        }
    }
    ClientApi::root_path_ = path;
    ClientApi::func_ = func;
    return true;
}

bool ClientApi::CreateChild(int child_type = ZOO_EPHEMERAL|ZOO_SEQUENCE)
{
    int ret = zoo_acreate(zh_, ClientApi::root_path_.c_str(), "child", 5, &ZOO_OPEN_ACL_UNSAFE, child_type, ClientApi::zk_string_completion, "CreateChild");
    if(ret != ZOK){
        return false;
    }
    return true;
}

bool ClientApi::VersionCheck(int version)
{
    if(ClientApi::version_ == version) return true;
    return false;
}

int ClientApi::GetVersion()
{
    return ClientApi::version_;
}

std::string ClientApi::GetMessage()
{
    return ClientApi::message_;
}

void ClientApi::Close()
{
    if(zh_ != NULL) zookeeper_close(zh_);
    zh_ = NULL;
}

void ClientApi::watcher(zhandle_t *zzh, int type, int state, const char *path,void *watcherCtx)
{
    if(type == ZOO_CHANGED_EVENT){
        //new message, need to get it. Get root first
        std::string root = path;
        ClientApi::ListenRoot(root, ClientApi::func_, false);
    }
}

void ClientApi::zk_string_completion(int rc, const char *value, const void *data)
{
}

void ClientApi::zk_data_completion(int rc, const char *value, int value_len, const struct Stat *stat, const void *data)
{

    ClientApi::message_ = value;
    ClientApi::version_ = stat->version;

    if(data != NULL){
        ClientApi::func_(ClientApi::message_);
    }
}

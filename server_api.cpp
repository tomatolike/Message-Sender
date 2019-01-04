#include "server_api.h"
#include "iostream"

std::string ServerApi::addr_port_ = "";
std::string ServerApi::root_path_ = "";
zhandle_t* ServerApi::zh_ = NULL;

bool ServerApi::Connect(std::string addr_port)
{
    //set debug level
    zoo_set_debug_level(ZOO_LOG_LEVEL_WARN);

    zh_ = zookeeper_init(addr_port.c_str(),ServerApi::watcher,DEFAULT_TIMEOUT,0,NULL,0);
    if(zh_ == NULL) return false;
    ServerApi::addr_port_ = addr_port;
    return true;
}

bool ServerApi::CreateRoot(std::string path)
{
    char pathbuffer[100];
    int ret = zoo_create(zh_,path.c_str(),"Hello_World",11,&ZOO_OPEN_ACL_UNSAFE,0,pathbuffer,100);

    if(ret == ZOK || ret == ZNODEEXISTS){
        ServerApi::root_path_ = path;
        return true;
    }
    return false;
}

bool ServerApi::ChangeMessage(std::string message)
{
    int ret = zoo_aset(zh_,ServerApi::root_path_.c_str(),message.c_str(),message.length(),-1,ServerApi::zk_stat_completion,"SET_MESSAGE");
    if(ret == ZOK){
        return true;
    }
    return false;
}

bool ServerApi::DeleteRoot()
{
    if(ServerApi::root_path_.compare("") == 0) return false;
    int ret = zoo_delete(zh_,ServerApi::root_path_.c_str(),-1);
    if(ret == ZOK || ret == ZNONODE){
        return true;
    }
    return false;
}

void ServerApi::Close()
{
    if(zh_ != NULL){
        zookeeper_close(zh_);
        zh_ = NULL;
    }
}

void ServerApi::watcher(zhandle_t *zh, int type, int state, const char *path,void *watcherCtx)
{

}

void ServerApi::zk_string_completion(int rc, const char *value, const void *data)
{

}

void ServerApi::zk_stat_completion(int rc, const struct Stat *stat, const void *data)
{
}
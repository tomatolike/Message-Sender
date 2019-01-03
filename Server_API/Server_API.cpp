#include "Server_API.h"
#include "iostream"

std::string Server_API::addr_port = "";
std::string Server_API::root_path = "";
zhandle_t* Server_API::zh = NULL;

bool Server_API::Connect(std::string addr_port)
{
    //set debug level
    zoo_set_debug_level(ZOO_LOG_LEVEL_WARN);

    zh = zookeeper_init(addr_port.c_str(),Server_API::watcher,DEFAULT_TIMEOUT,0,NULL,0);
    if(zh == NULL) return false;
    Server_API::addr_port = addr_port;
    return true;
}

bool Server_API::Create_root(std::string path)
{
    char pathbuffer[100];
    int ret = zoo_create(zh,path.c_str(),"Hello_World",11,&ZOO_OPEN_ACL_UNSAFE,0,pathbuffer,100);

    if(ret == ZOK || ret == ZNODEEXISTS){
        Server_API::root_path = path;
        return true;
    }
    return false;
}

bool Server_API::Change_message(std::string message)
{
    int ret = zoo_aset(zh,Server_API::root_path.c_str(),message.c_str(),message.length(),-1,Server_API::zk_stat_completion,"SET_MESSAGE");
    if(ret == ZOK){
        return true;
    }
    return false;
}

bool Server_API::Delete_root()
{
    if(Server_API::root_path.compare("") == 0) return false;
    int ret = zoo_delete(zh,Server_API::root_path.c_str(),-1);
    if(ret == ZOK || ret == ZNONODE){
        return true;
    }
    return false;
}

void Server_API::Close()
{
    if(zh != NULL){
        zookeeper_close(zh);
        zh = NULL;
    }
}

void Server_API::watcher(zhandle_t *zh, int type, int state, const char *path,void *watcherCtx)
{

}

void Server_API::zk_string_completion(int rc, const char *value, const void *data)
{

}

void Server_API::zk_stat_completion(int rc, const struct Stat *stat, const void *data)
{
}
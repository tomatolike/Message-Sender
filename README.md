## Message-Sender

### Description

This message sender is based on ZooKeeper. This tool is used to send message from servers to clients.  
The server part tool (server\_api) will create a node on your ZooKeeper server and you can use it to change the value (message) of the node.  
The client part tool (client\_api) will set a watch on the node created by server tool, then react to the value changes (means new messages) of the node.

### Files

+ lib/include:
These are libraries and header files essential for the tool.  

+ client\_api/server\_api:
The tool itself.

+ client\_test.cpp/server\_test.cpp:
Examples.

### Usage

+ First of all, you need to build a ZooKeeper server. See: [ZooKeeper](https://zookeeper.apache.org/doc/current/index.html)

+ ServerApi:

```c++
//All methods are static.

//This method is used to connect your ZK server. Input your server address and port as a string.
//e.g. ServerApi::Connect("192.168.xxx.xx:1234");
bool ServerApi::Connect(std::string add_port);

//This method is used to create the message node on your ZK server. The path is a file-path-like string. See ZK's official documents to know how to set path.
//If the node has already created, the method will still return true.
bool ServerApi::CreateRoot(std::string path);

//After create the node, you can change message now.
bool ServerApi::ChangeMessage(std::string message);

//This method is used to delete the message node.
bool ServerApi::DeleteRoot();

//Used to close the session with ZK server.
void ServerApi::Close();
```

+ Client\_API:

```c++
//All methods are static.

//This method is used to connect your ZK server.
bool ClientApi::Connect(std::string add_port);

//This method is used to listen to your message node on ZK server.
//param func is used as a call back function pointer, when the tool recieved a new message, it would transmit the message string as the parameter to your call back function.
//If you set first as true (as it defaultly is), the tool would not regard the message on the node as a new message when it first connects, in case that the message is old and has not been changed for a long time.
bool ClientApi::ListenRoot(std::string path, void (*func)(std::string) = NULL, bool first = true);

//Yes, though not essential in recieving message, the tool still provides you with a method to create a node. The default node type is ephemeral_sequential. See the ZK official documents to know the types of nodes.
bool ClientApi::CreateChild(int child_type);

//If you do not use a call back function in Listen_root method, you can use this method to check your message version. If the version does not match (return false), you are recieving a new message.
bool ClientApi::VersionCheck(int version);

//Remember to match the new version number if you use Version_Check.
int ClientApi::GetVersion();

//Get the new message. Better to use call back function.
std::string ClientApi::GetMessage();

//Close the session with ZK server.
void ClientApi::Close();
```
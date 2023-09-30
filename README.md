# Simple chat
C++ boost::asio implementation of multi-threaded chat server, and client


# Install boost asio
```
wget https://boostorg.jfrog.io/artifactory/main/release/1.82.0/source/boost_1_82_0.tar.gz
tar -xvf boost_1_82_0.tar.gz
cd boost_1_82_0
sudo ./bootstrap.sh
sudo ./b2 install
```

# Usage

## Build project

- This project consists of three main parts: an application-level client, a server, and a server core responsible for network core functionality.

- To execute the project, you need to build these three sub-projects in the following order
    - server core -> client, server.

- Since the server core is composed as a static library, it should be built first. After that, you can proceed to build the client and server.

- You can use CMake to build server core, followed by the server and client.
## Run
- Client
    ```
    ./client <nickname> <host_address> <host_port>
    ```
- Server
    ```
    ./server <port>
    ```
![](https://github.com/Ladun/simple_chat/blob/master/example.png)
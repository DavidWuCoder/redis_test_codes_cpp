#include <sw/redis++/redis++.h>
#include <sw/redis++/redis.h>

#include <iostream>
#include <string>

int main()
{
    // 创建 Redis 对象，需指定 Redis服务器ip地址和端口
    sw::redis::Redis redis("tcp://127.0.0.1:6379");
    // 调用 ping 方法，让客户端发送一个 ping 命令，服务端会返回一个 pong
    std::string result = redis.ping();
    std::cout << result << std::endl;
    return 0;
}

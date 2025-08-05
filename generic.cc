
#include <sw/redis++/redis++.h>
#include <sw/redis++/redis.h>

#include <chrono>
#include <cstdarg>
#include <iostream>
#include <iterator>
#include <string>
#include <thread>
#include <vector>

// get 和 set
void test1(sw::redis::Redis &redis)
{
    std::cout << "get 和 set 的使用" << std::endl;

    // 清空一下数据库，避免之前数据的干扰，生产环境禁用！
    redis.flushall();

    // 使用 set 设置几个 key
    redis.set("key1", "111");

    // 使用 get 获取到 key 对应的 value
    auto value1 = redis.get("key1");
    if (value1)
    {
        std::cout << "value1=" << value1.value() << std::endl;
    }

    auto value2 = redis.get("key2");
    if (value2)
    {
        std::cout << "value2=" << value2.value() << std::endl;
    }
}

// exists 命令
void test2(sw::redis::Redis &redis)
{
    std::cout << "exists 的 使用" << std::endl;
    // 清空一下数据库，避免之前数据的干扰，生产环境禁用！
    redis.flushall();

    redis.set("key1", "value1");
    redis.set("key2", "value2");

    auto ret = redis.exists("key1");
    std::cout << ret << std::endl;

    ret = redis.exists("key3");
    std::cout << ret << std::endl;

    ret = redis.exists({"key1", "key2", "key3"});
    std::cout << ret << std::endl;
}

// del 命令
void test3(sw::redis::Redis &redis)
{
    std::cout << "del 的使用" << std::endl;
    // 清空一下数据库，避免之前数据的干扰，生产环境禁用！
    redis.flushall();

    redis.set("key1", "value1");
    redis.set("key2", "value2");

    auto ret = redis.del({"key1", "key2", "key3"});
    std::cout << ret << std::endl;

    ret = redis.exists({"key1", "key2", "key3"});
    std::cout << ret << std::endl;
}

// keys 命令
void test4(sw::redis::Redis &redis)
{
    std::cout << "keys 的使用" << std::endl;
    // 清空一下数据库，避免之前数据的干扰，生产环境禁用！
    redis.flushall();

    redis.set("key1", "value1");
    redis.set("key2", "value2");
    redis.set("key3", "value2");
    redis.set("key4", "value2");
    redis.set("key5", "value2");

    // redis 的keys 有两个参数，第一个是匹配规则
    // 第二个是 “插入迭代器”，我们可以事先构建一个容器，传入迭代器，这样 keys
    // 就会把查询到的元素插入容器中
    std::vector<std::string> result;
    auto it = std::back_inserter(result);
    redis.keys("*", it);

    // 打印容器相关内容
    for (auto &str : result)
    {
        std::cout << str << std::endl;
    }
}

// expire and ttl
void test5(sw::redis::Redis &redis)
{
    std::cout << "expire and ttl" << std::endl;
    // 清空一下数据库，避免之前数据的干扰，生产环境禁用！
    redis.flushall();

    redis.set("key1", "111");
    redis.expire("key1", std::chrono::seconds(10));

    std::this_thread::sleep_for(std::chrono::seconds(5));
    long long ret = redis.ttl("key1");
    std::cout << "剩余时间: " << ret << std::endl;
}

void test6(sw::redis::Redis &redis)
{
    std::cout << "type" << std::endl;
    // 清空一下数据库，避免之前数据的干扰，生产环境禁用！
    redis.flushall();

    redis.set("key1", "111");
    redis.lpush("key2", "111");

    std::cout << redis.type("key1") << std::endl;
    std::cout << redis.type("key2") << std::endl;
}

int main()
{
    sw::redis::Redis redis("tcp://127.0.0.1:6379");
    // test1(redis);
    // test2(redis);
    // test3(redis);
    // test4(redis);
    // test5(redis);
    test6(redis);
    return 0;
}

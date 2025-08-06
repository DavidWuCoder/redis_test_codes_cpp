#include <sw/redis++/redis++.h>
#include <sw/redis++/redis.h>

#include <iostream>
#include <iterator>
#include <set>

// sadd smembers
void test1(sw::redis::Redis &redis)
{
    std::cout << "sadd and smembers" << std::endl;

    // 清空一下数据库，避免之前数据的干扰，生产环境禁用！
    redis.flushall();

    // 一次添加一个元素
    redis.sadd("key", "111");

    // 一次添加多个元素（使用初始化列表）
    redis.sadd("key", {"222", "333"});

    // 一次添加多个元素（使用迭代器）
    std::vector<std::string> elems = {"444", "555"};
    redis.sadd("key", elems.begin(), elems.end());

    // 通过 smembers 获取返回结果
    //  1. vector
    //  2. set
    // std::vector<std::string> results;
    // auto it = std::back_inserter(results);
    std::set<std::string> results;
    auto it = std::inserter(results, results.end());
    redis.smembers("key", it);

    // 打印结果
    for (auto &res : results)
    {
        std::cout << res << std::endl;
    }
}

// sismember and spop
void test2(sw::redis::Redis &redis)
{
    std::cout << "sismember and spop" << std::endl;
    // 清空一下数据库，避免之前数据的干扰，生产环境禁用！
    redis.flushall();

    redis.sadd("key", {"111", "222", "333"});

    bool result = redis.sismember("key", "111");
    std::cout << result << std::endl;

    redis.spop("key");
    redis.spop("key");
    redis.spop("key");

    result = redis.sismember("key", "111");
    std::cout << result << std::endl;
}

// sinter
void test3(sw::redis::Redis &redis)
{
    std::cout << "sinter" << std::endl;
    // 清空一下数据库，避免之前数据的干扰，生产环境禁用！
    redis.flushall();

    redis.sadd("key1", {"111", "222", "333"});
    redis.sadd("key2", {"111", "222", "444"});

    std::set<std::string> results;
    auto it = std::inserter(results, results.end());
    redis.sinter({"key1", "key2"}, it);

    for (auto &result : results)
    {
        std::cout << result << std::endl;
    }
}

// sinterstore
void test4(sw::redis::Redis &redis)
{
    std::cout << "sinterstore" << std::endl;
    // 清空一下数据库，避免之前数据的干扰，生产环境禁用！
    redis.flushall();

    redis.sadd("key1", {"111", "222", "333"});
    redis.sadd("key2", {"111", "222", "444"});

    long long len = redis.sinterstore("key3", {"key1", "key2"});
    std::cout << "len: " << len << std::endl;

    std::set<std::string> results;
    auto it = std::inserter(results, results.end());
    redis.smembers("key3", it);

    // 打印结果
    for (auto &res : results)
    {
        std::cout << res << std::endl;
    }
}

int main()
{
    sw::redis::Redis redis("tcp://127.0.0.1:6379");
    // test1(redis);
    // test2(redis);
    test3(redis);
    test4(redis);
    return 0;
}

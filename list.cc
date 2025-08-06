#include <sw/redis++/redis++.h>
#include <sw/redis++/redis.h>

#include <iostream>
#include <iterator>

// lpush 和 lrange
void test1(sw::redis::Redis& redis)
{
    std::cout << "lpush and lrange" << std::endl;
    // 清空一下数据库，避免之前数据的干扰，生产环境禁用！
    redis.flushall();

    // 插入单个元素
    redis.lpush("key", "1");

    // 插入一组元素，基于初始化列表
    redis.lpush("key", {"2", "3", "4"});

    // 插入一组元素，基于迭代器
    std::vector<std::string> values = {"5", "6", "7"};
    redis.lpush("key", values.begin(), values.end());

    // lrange 获取结果，需要构造容器，传入插入迭代器
    std::vector<std::string> results;
    auto it = std::back_inserter(results);
    redis.lrange("key", 0, -1, it);

    // 打印结果
    for (auto& result : results)
    {
        std::cout << result << std::endl;
    }
}

// lpop 和 rpop
void test2(sw::redis::Redis& redis)
{
    std::cout << "lpop and rpop" << std::endl;
    // 清空一下数据库，避免之前数据的干扰，生产环境禁用！
    redis.flushall();

    redis.rpush("key", {"1", "2", "3", "4", "5", "6", "7"});

    auto ret = redis.lpop("key");
    if (ret)
    {
        std::cout << "lpop: " << ret.value() << std::endl;
    }

    ret = redis.rpop("key");
    if (ret)
    {
        std::cout << "rpop: " << ret.value() << std::endl;
    }
}

// blpop
void test3(sw::redis::Redis& redis)
{
    std::cout << "blpop" << std::endl;
    // 清空一下数据库，避免之前数据的干扰，生产环境禁用！
    redis.flushall();

    auto ret = redis.blpop({"key1", "key2", "key3"});
    if (ret)
    {
        std::cout << "key: " << ret.value().first << std::endl;
        std::cout << "elem: " << ret.value().second << std::endl;
    }
    else
    {
        std::cout << "元素无效！" << std::endl;
    }
}

int main()
{
    sw::redis::Redis redis("tcp://127.0.0.1:6379");
    // test1(redis);
    // test2(redis);
    test3(redis);
    return 0;
}

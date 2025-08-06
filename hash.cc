
#include <sw/redis++/redis.h>

#include <iostream>
#include <iterator>

// hget and hset
void test1(sw::redis::Redis &redis)
{
    std::cout << "hget and hset" << std::endl;
    // 清空一下数据库，避免之前数据的干扰，生产环境禁用！
    redis.flushall();

    // 插入一个 field-value 对
    redis.hset("key", "f1", "1");

    // 插入多个 field-value 对（初始化列表）
    redis.hset("key", {std::make_pair("f2", "2"), std::make_pair("f3", "3")});

    // 插入多个 field-value 对（迭代器）
    std::vector<std::pair<std::string, std::string>> fields = {
        std::make_pair("f4", "4"), std::make_pair("f5", "5")};

    auto result = redis.hget("key", "f1");
    if (result)
    {
        std::cout << result.value() << std::endl;
    }
    else
    {
        std::cout << "返回值无效！" << std::endl;
    }
}

// hexists, hlen, hdel
void test2(sw::redis::Redis &redis)
{
    std::cout << "hget and hset" << std::endl;
    // 清空一下数据库，避免之前数据的干扰，生产环境禁用！
    redis.flushall();

    // 插入多个 field-value 对（初始化列表）
    redis.hset("key", {std::make_pair("f2", "2"), std::make_pair("f3", "3")});

    std::cout << "删除前：" << std::endl;
    long long len = redis.hlen("key");
    std::cout << "len: " << len << std::endl;

    bool result = redis.hexists("key", "f2");
    std::cout << result << std::endl;

    redis.hdel("key", "f2");

    std::cout << "删除后：" << std::endl;
    len = redis.hlen("key");
    std::cout << "len: " << len << std::endl;
    result = redis.hexists("key", "f2");
    std::cout << result << std::endl;
}

// hkeys hvals
void test3(sw::redis::Redis &redis)
{
    std::cout << "keys hvals" << std::endl;
    // 清空一下数据库，避免之前数据的干扰，生产环境禁用！
    redis.flushall();

    // 插入多个 field-value 对（初始化列表）
    redis.hset("key", {std::make_pair("f1", "1"), std::make_pair("f2", "2"),
                       std::make_pair("f3", "3")});

    std::vector<std::string> fields;
    auto it = std::back_inserter(fields);

    redis.hkeys("key", it);

    for (auto &str : fields)
    {
        std::cout << str << std::endl;
    }
    std::vector<std::string> vals;

    it = std::back_inserter(vals);

    redis.hvals("key", it);

    for (auto &str : vals)
    {
        std::cout << str << std::endl;
    }
}

int main()
{
    sw::redis::Redis redis("tcp://127.0.0.1:6379");
    // test2(redis);
    test3(redis);
    return 0;
}

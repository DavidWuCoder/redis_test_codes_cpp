#include <sw/redis++/redis.h>

#include <iostream>
#include <iterator>

// zadd zrange
void test1(sw::redis::Redis& redis)
{
    std::cout << "zadd zrange" << std::endl;
    // 清空数据库，防止之前的数据干扰，生产环境禁用！
    redis.flushall();

    // 三种版本
    redis.zadd("key", "吕布", 99);
    redis.zadd("key", {std::make_pair("赵云", 98), std::make_pair("张飞", 95)});

    std::vector<std::pair<std::string, double>> members = {
        std::make_pair("典韦", 97), std::make_pair("关羽", 96)};
    redis.zadd("key", members.begin(), members.end());

    // zrange 是否查询分数要看容器类型
    //  如果容器仅 string 则 仅查询member
    //  如果容器是 pair<string, double>, 则返回member 和 分数
    std::cout << "仅查询member" << std::endl;
    std::vector<std::string> results;
    auto it = std::back_inserter(results);
    redis.zrange("key", 0, -1, it);

    for (auto& s : results)
    {
        std::cout << s << std::endl;
    }

    std::cout << "查询member和分数" << std::endl;
    std::vector<std::pair<std::string, double>> scores;
    auto it1 = std::back_inserter(scores);
    redis.zrange("key", 0, -1, it1);

    for (auto& [member, score] : scores)
    {
        std::cout << member << " " << score << std::endl;
    }
}

// zcard zscore zrank
void test2(sw::redis::Redis& redis)
{
    std::cout << "zcard zscore zrank" << std::endl;
    // 清空数据库，防止之前的数据干扰，生产环境禁用！
    redis.flushall();

    redis.zadd("key", "zhangsan", 90);
    redis.zadd("key", "lisi", 91);
    redis.zadd("key", "wangwu", 92);
    redis.zadd("key", "zhaoliu", 93);

    long long result = redis.zcard("key");
    std::cout << result << std::endl;

    auto score = redis.zscore("key", "zhangsan");
    if (score)
    {
        std::cout << "score: " << score.value() << std::endl;
    }
    else
    {
        std::cout << "score 无效" << std::endl;
    }

    auto rank = redis.zrank("key", "lisi");
    if (score)
    {
        std::cout << "rank: " << rank.value() << std::endl;
    }
    else
    {
        std::cout << "rank 无效" << std::endl;
    }
}

int main()
{
    sw::redis::Redis redis("tcp://127.0.0.1:6379");
    // test1(redis);
    test2(redis);
    return 0;
}

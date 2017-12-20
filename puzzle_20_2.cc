#include <assert.h>
#include <boost/algorithm/string/classification.hpp>
#include <boost/algorithm/string/split.hpp>
#include <iostream>
#include <vector>


struct Point
{
    constexpr Point() = default;
    constexpr Point(long _id, std::vector<long>&& l)
        : id(_id)
    {
        assert(l.size() == 9);
        auto it = l.begin();
        x = *it++;
        y = *it++;
        z = *it++;
        v_x = *it++;
        v_y = *it++;
        v_z = *it++;
        a_x = *it++;
        a_y = *it++;
        a_z = *it++;
    }

    long id = 0;
    long x = 0, y = 0, z = 0;
    long v_x = 0, v_y = 0, v_z = 0;
    long a_x = 0, a_y = 0, a_z = 0;
    long len = 0;
    long acc = 0;
    bool del = false;

    void step() noexcept
    {
        v_x += a_x;
        v_y += a_y;
        v_z += a_z;
        x += v_x;
        y += v_y;
        z += v_z;
        len = std::abs(x) + std::abs(y) + std::abs(z);
        acc = std::abs(a_x) + std::abs(a_y) + std::abs(a_z);
    }

    bool operator<(const Point& b) const noexcept {
        return std::tie(len, acc) < std::tie(b.len, b.acc);
    }

    bool operator==(const Point& b) const noexcept {
        return std::tie(x, y, z) == std::tie(b.x, b.y, b.z);
    }
};

int main()
{
    // p=<-4897,3080,2133>, v=<-58,-15,-78>, a=<17,-7,0>
    // -4897,3080,2133,-58,-15,-78,17,-7,0
    std::vector<Point> points;
    std::string line;
    long id = 0;
    while (std::getline(std::cin, line)) {
        std::vector<std::string> words;
        boost::algorithm::split(
            words, line, boost::is_any_of(", "), boost::algorithm::token_compress_on);
        std::vector<long> nums;
        for (const auto& word : words) {
            nums.push_back(atol(&word[0]));
        }
        points.emplace_back(Point(id++, std::move(nums)));
    }

    for (int i = 0; i < 500; ++i) {
        for (auto it = points.begin(); it != points.end(); ++it) {
            for (auto i2 = std::next(it); i2 != points.end(); ++i2) {
                assert(it != points.end());
                assert(i2 != points.end());
                if (*it == *i2) {
                    it->del = true;
                    i2->del = true;
                }
            }
        }
        points.erase(
            std::partition(points.begin(), points.end(), [](const Point& a) { return !a.del; }),
            points.end());

        std::sort(points.begin(), points.end());
        std::cout << points.size() << "\n";

        for (auto& p : points) {
            p.step();
        }
    }

    return 0;
}

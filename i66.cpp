#include <iostream>
#include <random>
#include <vector>
#include <algorithm>
#include <iomanip>

int main() {
    // 常態分佈參數
    double mean = 0.0;         // 平均值
    double stddev = 1.0;       // 標準差
    int num_points = 63;       // 取樣點數

    // 建立隨機數生成器
    std::random_device rd;
    std::mt19937 generator(rd());
    std::normal_distribution<double> distribution(mean, stddev);

    // 存儲取樣結果
    std::vector<double> points;

    for (int i = 0; i < num_points; ++i) {
        double point = distribution(generator);
        points.push_back(point);
    }

    // 排序結果（選擇性）
    std::sort(points.begin(), points.end());

    // 印出結果
    std::cout << "63 points sampled from a normal distribution (mean = " << mean
              << ", stddev = " << stddev << "):\n";
    for (size_t i = 0; i < points.size(); ++i) {
        std::cout << std::fixed << std::setprecision(4) << points[i] << " ";
        if ((i + 1) % 10 == 0) std::cout << std::endl; // 每10個點換行
    }
    std::cout << std::endl;

    return 0;
}

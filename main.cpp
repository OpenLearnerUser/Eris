#include <iostream>
#include <Eris/array1.h>
#include <Eris/array2.h>
#include <Eris/parallel.h>
#include <Eris/point3.h>
#include <Eris/size3.h>
#include <Eris/size2.h>
#include <vector>
#include <chrono>
#include <thread>
#include <atomic>
#include <cmath>
#include <iomanip>
#include <Eris/size.h>
using namespace Eris;



void testParallelForWithVector() {
    const size_t N = 1000;  // 一千万个元素
    std::vector<double> data(N);
    
    std::cout << std::fixed << std::setprecision(6);


    auto heavy_task = [&data](size_t i) {
        double result = 0.0;
        for (int j = 0; j < 100; ++j) {  // 100倍计算量
            result += std::sin(i * j) * std::cos(i * j);
        }
        return result;
    };
    
    // 测试1：并行赋值
    std::cout << "\n测试1：并行赋值..." << std::endl;
    auto start_time = std::chrono::high_resolution_clock::now();
    
    paralleFor<size_t>(0, N, [&data,&heavy_task](size_t i) {
        data[i] = heavy_task(i);
    }, ExecutionPolicy::KParallel);
    
    auto end_time = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);
    std::cout << "并行执行时间: " << duration.count() << " ms" << std::endl;
    
    // 测试2：顺序赋值
    std::cout << "\n测试2：顺序赋值..." << std::endl;
    std::vector<double> data2(N);
    start_time = std::chrono::high_resolution_clock::now();
    
    paralleFor<size_t>(0, N, [&data2,&heavy_task](size_t i) {
        data2[i] = heavy_task(i);
    }, ExecutionPolicy::Kserial);
    
    end_time = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);
    std::cout << "顺序执行时间: " << duration.count() << " ms" << std::endl;
    
    // 验证结果
    bool identical = true;
    for(size_t i = 0; i < N; i++) {
        if(std::abs(data[i] - data2[i]) > 1e-10) {
            identical = false;
            std::cout << "在索引 " << i << " 处发现差异" << std::endl;
            break;
        }
    }
    std::cout << "结果验证: " << (identical ? "通过 ✓" : "失败 ✗") << std::endl;
    
    // 测试3：并行计算和（使用 CAS 循环，兼容 C++17）
std::cout << "\n测试3：并行计算和..." << std::endl;
std::atomic<double> atomic_sum(0.0);
start_time = std::chrono::high_resolution_clock::now();

paralleFor<size_t>(0, N, [&data, &atomic_sum](size_t i) {
    // CAS 循环实现原子加法
    double expected = atomic_sum.load(std::memory_order_relaxed);
    while (!atomic_sum.compare_exchange_weak(expected, 
                                              expected + data[i],
                                              std::memory_order_relaxed,
                                              std::memory_order_relaxed)) {
        // 循环继续，expected 已被更新为当前值
    }
}, ExecutionPolicy::KParallel);

end_time = std::chrono::high_resolution_clock::now();
duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);
std::cout << "并行求和时间: " << duration.count() << " ms" << std::endl;
std::cout << "和: " << atomic_sum.load() << std::endl;
    
    // 方法2：顺序求和作为基准
    double sequential_sum = 0.0;
    start_time = std::chrono::high_resolution_clock::now();
    
    for (size_t i = 0; i < N; ++i) {
        sequential_sum += data[i];
    }
    
    end_time = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);
    std::cout << "顺序求和时间: " << duration.count() << " ms" << std::endl;
    std::cout << "和（顺序）: " << sequential_sum << std::endl;
    
    // 检查差异
    double diff = std::abs(atomic_sum.load() - sequential_sum);
    std::cout << "原子与顺序差异: " << diff << std::endl;
    
    if (diff > 1.0) {
        std::cout << "⚠️ 警告：原子求和结果与顺序求和差异较大，可能存在数据竞争！" << std::endl;
    }
    
    // 测试4：边界测试
    std::cout << "\n测试4：边界测试（空范围）..." << std::endl;
    paralleFor<size_t>(10, 5, [](size_t i) {
        std::cout << "这不应该被执行" << std::endl;
    }, ExecutionPolicy::KParallel);
    std::cout << "空范围测试通过 ✓" << std::endl;
    
    // 测试5：小数据量
    std::cout << "\n测试5：小数据量测试..." << std::endl;
    std::vector<double> small_data(10);
    paralleFor<size_t>(0, 10, [&small_data](size_t i) {
        small_data[i] = static_cast<double>(i * i);
    }, ExecutionPolicy::KParallel);
    
    std::cout << "小数据量结果: ";
    for(const auto& val : small_data) {
        std::cout << val << " ";
    }
    std::cout << std::endl;
}




int main(int argc, char **argv)
{

    // std::cout << "=== paralleFor 函数测试 ===" << std::endl;
    // std::cout << "硬件并发线程数: " << std::thread::hardware_concurrency() << std::endl;
    // std::cout << std::endl;
    
    // try {
    //     testParallelForWithVector();
    // } catch(const std::exception& e) {
    //     std::cerr << "测试过程中发生异常: " << e.what() << std::endl;
    //     return 1;
    // }
    
    // std::cout << "\n所有测试完成！" << std::endl;

    Point3<double> a;
    a={1,2,4};
    std::cout<<"a="<<a[1]<<std::endl;
    return 0;
}
#include <iostream>
#include <numbers>
#include <algorithm>
#include <numeric>
#include <cmath>
#include <iomanip>

// Задание 1: Расчет среднего периметра треугольников
namespace GeometryCalc {
    double computeSegment(double x_start, double y_start, double x_end, double y_end) {
        double dx = x_end - x_start;
        double dy = y_end - y_start;
        return std::hypot(dx, dy);
    }

    double calculatePerimeter(double xa, double ya, double xb, double yb, double xc, double yc) {
        double side_ab = computeSegment(xa, ya, xb, yb);
        double side_bc = computeSegment(xb, yb, xc, yc);
        double side_ca = computeSegment(xc, yc, xa, ya);
        return side_ab + side_bc + side_ca;
    }

    void processTriangles() {
        const int TRIANGLE_COUNT = 3;
        double total_sum = 0.0;
        
        for(int idx = 0; idx < TRIANGLE_COUNT; ++idx) {
            std::cout << "Треугольник " << (idx + 1) << " (введите x1 y1 x2 y2 x3 y3): ";
            double ax, ay, bx, by, cx, cy;
            std::cin >> ax >> ay >> bx >> by >> cx >> cy;
            
            double perimeter = calculatePerimeter(ax, ay, bx, by, cx, cy);
            std::cout << std::fixed << std::setprecision(3) 
                      << "Периметр: " << perimeter << std::endl;
            
            total_sum += perimeter;
        }
        
        double average_value = total_sum / TRIANGLE_COUNT;
        std::cout << std::fixed << std::setprecision(3) 
                  << "Среднее значение: " << average_value << std::endl;
    }
}

// Задание 2: Сортировка массива

// Задание 3: Табулирование функции
namespace FunctionTabulation {
    double mathFunction(double x) {
        return (x >= 1.0) ? std::sqrt(x - 1.0) : -1.0;
    }
    
    void createTable() {
        std::cout << "Таблица значений функции f(x) = sqrt(x - 1):\n";
        std::cout << std::setw(5) << "x" << std::setw(12) << "f(x)" << std::endl;
        std::cout << std::string(20, '-') << std::endl;
        
        for(int x_val = 1; x_val <= 12; ++x_val) {
            double result = mathFunction(static_cast<double>(x_val));
            std::cout << std::setw(5) << x_val;
            
            if(result >= 0.0) {
                std::cout << std::fixed << std::setprecision(4) 
                          << std::setw(12) << result;
            } else {
                std::cout << std::setw(12) << "не опред.";
            }
            std::cout << std::endl;
        }
    }
}

// Задание 4: Подсчет совпадений в массиве
namespace ArrayAnalysis {
    template<size_t N>
    int countOccurrences(int target, const int (&data)[N]) {
        return std::count(data, data + N, target);
    }
    
    void findMatches() {
        const int DATA_SIZE = 13;
        int sample_data[DATA_SIZE] = {3, 7, 2, 3, 8, 3, 5, 7, 3, 1, 4, 3, 6};
        
        std::cout << "Анализируемый массив: ";
        for(int i = 0; i < DATA_SIZE; ++i) {
            std::cout << sample_data[i] << " ";
        }
        std::cout << std::endl;
        
        int search_value;
        std::cout << "Введите число для поиска: ";
        std::cin >> search_value;
        
        int matches = countOccurrences(search_value, sample_data);
        std::cout << "Найдено совпадений: " << matches << std::endl;
    }
}

// Главная программа
int main() {
    std::cout << "===== ЗАДАНИЕ 1: ПЕРИМЕТРЫ ТРЕУГОЛЬНИКОВ =====\n";
    GeometryCalc::processTriangles();
 
    
    std::cout << "\n===== ЗАДАНИЕ 3: ТАБУЛИРОВАНИЕ ФУНКЦИИ =====\n";
    FunctionTabulation::createTable();
    
    std::cout << "\n===== ЗАДАНИЕ 4: ПОДСЧЕТ СОВПАДЕНИЙ =====\n";
    ArrayAnalysis::findMatches();
    
    return 0;
}
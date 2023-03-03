#include <iostream>
#include <omp.h>
#include <cmath>
using namespace std;

double func(double x)   // значение подынтегральной функции 
{
    return (pow(x, 3) - 3);  // например, x^3 - 3
}

int main()
{
    int i;
    double a, b;
    cout << "Введите пределы интегрирования." << endl;
    cout << "Нижний: ";
    cin >> a;
    cout << "Верхний: ";
    cin >> b;

    double n = 10000, sum, h, integral;
    h = (b - a) / n;
    sum = (func(a) + func(b)) / 2; // значения на концах других частичных отрезков считаются дважды
    #pragma omp parallel private(i) shared(n, h) reduction(+:sum)
    {
        int threads = omp_get_num_threads();
        int id = omp_get_thread_num();
        for (i=id+1; i<n; i+=threads)
            sum += func(a + h*i);
    }
    integral = sum * h;
    cout << "integral: " << integral << endl;
}

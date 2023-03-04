# Лабораторная работа №1
## Выбранные задачи:
<b>№1.</b> Написать программу где каждый поток печатает свой идентификатор, количество потоков всего и строчку «Hello World». Запустить программу с 8 потоками. Всегда ли вывод идентичен? Почему? 

<i>Результат работы (файл hello-world.cpp в папке lab1)</i>:
![Screenshot from 2023-02-27 11-31-26](https://user-images.githubusercontent.com/102433741/222807518-8709c048-2939-44bb-865b-e797007cb173.png)

Вывод не упорядочен по номерам потоков (нитей), т.к. порядок выполнения потоков заранее неизвестен (+ нет ordered). 

<b>№2.</b> Написать программу, в которой объявлен массив из 16000 элементов и инициализирован так, что значение элемента массива равно его порядковому номеру. Затем создайте результирующий массив, в котором (за исключением крайних элементов) будут средние значения исходного массива: 
b[i] = (a[i-1] + a[i] + a[i+1])/3.0.
Запустите программу с 8-ю процессами при различных типах распределения работ. 

Результат работы (файл hello-world.cpp в папке lab1):
![static 1000](https://user-images.githubusercontent.com/102433741/222811800-c2525055-83f3-498b-a65b-d46cd08b606a.png)

На скриншоте результат (вернее, его небольшая часть) при использовании schedule(static, 1000) для 2 циклов (инициализация массива a и инициализация массива b). Для каждого цикла потоки получили на выполнение итерации след. образом: 0 поток - от 0 до 999, 1 поток - от 1000 до 1999, и т.д. по аналогии (с 8000 начинается снова с 0 потока). 

![изображение](https://user-images.githubusercontent.com/102433741/222813982-0b492bda-b6a4-4d4c-811d-608b5b659a9f.png)

![guided 1000](https://user-images.githubusercontent.com/102433741/222814177-13fda315-2c34-4d45-8f0f-421c1c2dfc06.png)

На первом скриншоте использовано schedule(dynamic, 1000), на втором - schedule(guided). На практике разницы между ними не увидела, т.к. размеры блоков для данной задачи получились одинаковыми. 

<b>№4.</b> Напишите программу перемножения больших матриц. Сравните врем выполнения последовательной и параллельной программы на 2,4, 8 потоках (процессорах).

Для примера взяты матрицы с элементами вида i + j + 1 (i - номер строки элемента, j - номер его столбца), т.е. в матрицах нет нулевых элементов.

Наилучший получившийся результат работы (файл task4_sequential.cpp в папке lab1):
![final4](https://user-images.githubusercontent.com/102433741/222815661-4249bc6d-cbcc-4e94-9900-ea2da362583b.png)

Параллельное выполнение программы занимает больше времени по сравнению с последовательным выполнением.

<b>Задача №2.</b> 
Разработайте программу для задачи вычисления определенного интеграла с использованием метода трапеций. 

Результат работы с циклическим распределением итераций (файл lab1.cpp в папке lab1):
![Screenshot from 2023-03-04 13-35-56](https://user-images.githubusercontent.com/102433741/222895091-ad516eba-07d4-4a8f-be13-90a7e721c253.png)

Время в мкс посчитано для функций с циклом, где вычисляется сумма значений функции в узловых точках (за исключением нижнего и верхнего пределов интегрирования), - при последовательном выполнении цикла (sequential), а также при параллельном вычислении (parallel; 2, 4 и 8 потоков). При параллельно работающих 8 потоках время выполнения функции сокращено в 2 раза по сравнению с последовательным выполнением. Конечный результат - значение определенного интеграла - идентичен.

Также были оптимизированы вычисления - значение функции на концах каждого частичного отрезка посчитано лишь единожды (при сдвиге на шаг правый конец предыдущего частичного отрезка становится левым концом нового частичного отрезка, но нет нужды вычислять значение функции в одной и той же точке 2 раза). 

Формула для вычисления:

$$ \int_{x_0}^{x_n}f(x)dx = \big(f(x_0) + f(x_n) + 2\sum_{i=1}^{n-1}f(x_i) \big) \cdot \frac{h}{2} $$

$$ x_i = a + i \cdot h $$

$$ h = \frac{b - a}{n} $$

где n - число разбиений на частичные отрезки, h - шаг разбиения, $x_i$ - узлы интегрирования ($i = \overline{0, n}$).

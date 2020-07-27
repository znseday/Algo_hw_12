#include <iostream>

using namespace std;

// Реализовать алгоритм Дейкстры
// Реализовать классику всех времен и народов, алгоритм Дейкстры :)

// Граф задан вектором смежности int A[N][Smax]. Это п.5 в структурах данных в лекции. Отличие только в том, что вершины нумеруются от 0 а не от 1, и номера самой вершины первым столбцом в матрице не будет, будут только номера смежных вершин.

// Задание:

// Реализовать алгоритм Дейкстры. Если понадобится использование дерева/кучи обязательно применение собственных структур данных из предыдущих занятий. Можно использовать стандартный массив [] встроенный в язык.

// Выходные данные:

// Результат должен быть представлен в виде массива Edge[] edges где Edge - класс, содержащий пару вершин, которые соединяет это ребро Edge { int v1; int v2; }

#include "findshortest.h"

bool IsDebugOutput = true;

void SimpleTest(size_t nTest, FindShortest &_findShortest, size_t _fromV, size_t _toV);

int main()
{
    FindShortest findShortest;

    // Примеры, как в вебинаре, но нумерация вершин с нуля
    SimpleTest(0, findShortest, 0, 4);
    SimpleTest(1, findShortest, 0, 6);

    return 0;
}

void SimpleTest(size_t nTest, FindShortest &_findShortest, size_t _fromV, size_t _toV)
{
    cout << "Test " << nTest << ":" << endl;
    if (!_findShortest.LoadFromFile("test" + to_string(nTest) + ".txt"))
    {
        cerr << "file not found or can not be read" << endl;
        exit(0);
    }

    auto res = _findShortest.FindShortestFromTo(_fromV, _toV);

    cout << "Shortest Path (Edges):" << endl;
    for (const auto & e : res)
        cout << e << endl;
    cout << endl;
}










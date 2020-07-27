#ifndef FINDSHORTEST_H
#define FINDSHORTEST_H

#include <iostream>
#include <string>
#include <vector>
#include <limits>

extern bool IsDebugOutput;

#define MY_DEBUG_ONLY(x) { if(IsDebugOutput) {x}  }

struct Edge // Согласно заданию
{
    int v1; int v2;
    Edge(int x, int y) : v1(x), v2(y) {}
};

std::ostream & operator<<(std::ostream &s, const Edge &e);

struct Vertex
{
    bool Visited = false;
//    double Dist = std::numeric_limits<double>::max(); // или бесконечность???
    double Dist = std::numeric_limits<double>::infinity(); // или бесконечность???
    int From = -1;
    std::vector<std::pair<size_t, double>> V; // смежные вершины {индекс, вес}
};



class FindShortest
{
protected:

    std::vector<Vertex> Vertices;

    int FindMin();

public:
    FindShortest() = default;
    ~FindShortest() = default;

    bool LoadFromFile(const std::string &fn);

    std::vector<Edge> FindShortestFromTo(size_t _fromV, size_t _toV);


};

#endif // FINDSHORTEST_H




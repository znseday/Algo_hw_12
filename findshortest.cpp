#include "findshortest.h"

#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

ostream & operator<<(ostream &s, const Edge &e)
{
    s << "{" << e.v1 << "; " << e.v2 << "}";
    return s;
}

bool FindShortest::LoadFromFile(const string &fn)
{
    ifstream f(fn);
    if (!f)
        return false;

    size_t N;
    f >> N;

    Vertices.clear();
    Vertices.resize(N);

    size_t m, v; double w;

    for (size_t i = 0; i < N; ++i)
    {
        f >> m;
        for (size_t j = 0; j < m; ++j)
        {
            f >> v >> w;
            Vertices[i].V.emplace_back(v, w);
        }
    }

    MY_DEBUG_ONLY(
        cout << "Src Graph {Vertex, Weight}:" << endl;
        for (size_t i = 0; i < Vertices.size(); ++i)
        {
            cout << i << ":  ";
            for (const auto &v : Vertices[i].V)
                cout << "{" << v.first << "; " << v.second << "}  ";
            cout << endl;
        }
        cout << endl;
    )

    return true;
}
//---------------------------------------------------------

void FindShortest::ResetDistances()
{
    for (auto &v : Vertices)
    {
        v.Dist = std::numeric_limits<double>::infinity();
        v.From = -1;
        v.Visited = false;
    }
}
//---------------------------------------------------------

int FindShortest::FindMin()
{
    if (Vertices.empty())
        throw runtime_error("Vertices is empty");

//    double MinD = std::numeric_limits<double>::max(); // или бесконечность???
    double MinD = std::numeric_limits<double>::infinity(); // или бесконечность???
    int ind = -1;
    for (int i = 0; i < (int)Vertices.size(); ++i)
    {
        if ( !Vertices[i].Visited && Vertices[i].Dist < MinD)
        {
            MinD = Vertices[i].Dist;
            ind = i;
        }
    }
    if (ind == -1)
        throw runtime_error("Min Not Found");

    return ind;
}
//---------------------------------------------------------

vector<Edge> FindShortest::FindShortestFromTo(size_t _fromV, size_t _toV)
{
    vector<Edge> res; // возвращаем массив ребер согласно заданию

    ResetDistances();

    Vertices[_fromV].Dist = 0;

    for (size_t k = 0; k < Vertices.size(); ++k)
    {
        int vMin = FindMin();

        for (auto & v : Vertices[vMin].V)
        {
            if (Vertices[v.first].Visited)
                continue;

            if (Vertices[vMin].Dist + v.second < Vertices[v.first].Dist)
            {
                Vertices[v.first].Dist = Vertices[vMin].Dist + v.second;
                Vertices[v.first].From = vMin;
            }

        }

        Vertices[vMin].Visited = true;

        MY_DEBUG_ONLY(
            cout << "Number\tDist\tFrom\tVisited:" << endl;
            for (size_t i = 0; i < Vertices.size(); ++i)
            {
                cout << i << "\t" << Vertices[i].Dist << "\t" << Vertices[i].From << "\t" << Vertices[i].Visited;
                cout << endl;
            }
            cout << endl;
        )

    }

    vector<size_t> vPath; // для отладки - дополнительно выводим путь через вершины - как на лекции
    while (_toV != _fromV)
    {
        vPath.emplace_back(_toV);

        int x = _toV;
        int y = Vertices[_toV].From;
        _toV = y;

        res.emplace_back(x, y);
    }
    vPath.emplace_back(_fromV);

    MY_DEBUG_ONLY( // для отладки - дополнительно выводим путь через вершины - как на лекции
        reverse(vPath.begin(), vPath.end());
        cout << "Shortest Path (Vertices):" << endl;
        for (size_t i = 0; i < vPath.size(); ++i)
        {
            cout << vPath[i] << ((i!=vPath.size()-1)?" - ":"\n");
            //cout << endl;
        }
        cout << endl;
    )

    reverse(res.begin(), res.end());
    return res;
}
//---------------------------------------------------------

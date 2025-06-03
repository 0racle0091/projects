#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include <set>
#include <stack>
#include <map>

using namespace std;

const int INF = INT_MAX;

// Функция для поиска минимального остовного дерева с помощью алгоритма Прима
vector<pair<int, int>> findMST(const vector<vector<int>>& graph) {
    int n = graph.size();
    vector<bool> inMST(n, false);
    vector<int> key(n, INF);
    vector<int> parent(n, -1);
    vector<pair<int, int>> mstEdges;

    key[0] = 0;

    for (int count = 0; count < n; ++count) {
        int u = -1;

        for (int i = 0; i < n; ++i) {
            if (!inMST[i] && (u == -1 || key[i] < key[u])) {
                u = i;
            }
        }

        inMST[u] = true;

        if (parent[u] != -1) {
            mstEdges.emplace_back(u, parent[u]);
        }

        for (int v = 0; v < n; ++v) {
            if (graph[u][v] != 0 && !inMST[v] && graph[u][v] < key[v]) {
                key[v] = graph[u][v];
                parent[v] = u;
            }
        }
    }

    return mstEdges;
}

// Функция для поиска нечётных вершин
vector<int> findOddDegreeVertices(const vector<pair<int, int>>& mstEdges, int n) {
    vector<int> degree(n, 0);
    for (const auto& edge : mstEdges) {
        degree[edge.first]++;
        degree[edge.second]++;
    }

    vector<int> oddVertices;
    for (int i = 0; i < n; ++i) {
        if (degree[i] % 2 != 0) {
            oddVertices.push_back(i);
        }
    }

    return oddVertices;
}

// Функция для нахождения минимального совершенного паросочетания
vector<pair<int, int>> findMinPerfectMatching(const vector<int>& oddVertices, const vector<vector<int>>& graph) {
    vector<pair<int, int>> matching;
    set<int> unmatched(oddVertices.begin(), oddVertices.end());

    while (!unmatched.empty()) {
        auto it = unmatched.begin();
        int u = *it;
        unmatched.erase(it);

        int v = -1;
        int minWeight = INF;
        for (int x : unmatched) {
            if (graph[u][x] < minWeight) {
                minWeight = graph[u][x];
                v = x;
            }
        }

        if (v != -1) {
            unmatched.erase(v);
            matching.emplace_back(u, v);
        }
    }

    return matching;
}

// Построение эйлерова цикла
vector<int> findEulerianCircuit(const vector<vector<int>>& graph, const vector<pair<int, int>>& mstEdges, const vector<pair<int, int>>& matching) {
    map<int, vector<int>> adjList;
    for (const auto& edge : mstEdges) {
        adjList[edge.first].push_back(edge.second);
        adjList[edge.second].push_back(edge.first);
    }

    for (const auto& edge : matching) {
        adjList[edge.first].push_back(edge.second);
        adjList[edge.second].push_back(edge.first);
    }

    vector<int> circuit;
    stack<int> stack;
    map<int, multiset<int>> multigraph;

    // Создаём многомножество рёбер
    for (auto it = adjList.begin(); it != adjList.end(); ++it) {
        for (int v : it->second) {
            multigraph[it->first].insert(v);
        }
    }

    stack.push(0);

    while (!stack.empty()) {
        int u = stack.top();
        if (multigraph[u].empty()) {
            circuit.push_back(u);
            stack.pop();
        }
        else {
            int v = *multigraph[u].begin();
            multigraph[u].erase(multigraph[u].find(v));
            multigraph[v].erase(multigraph[v].find(u));
            stack.push(v);
        }
    }

    return circuit;
}

// Преобразование эйлерова цикла в гамильтонов путь
vector<int> makeHamiltonianPath(const vector<int>& eulerianCircuit) {
    vector<bool> visited(eulerianCircuit.size(), false);
    vector<int> hamiltonianPath;

    for (int v : eulerianCircuit) {
        if (!visited[v]) {
            hamiltonianPath.push_back(v);
            visited[v] = true;
        }
    }

    return hamiltonianPath;
}

// Вычисление длины пути
int calculatePathLength(const vector<int>& path, const vector<vector<int>>& graph) {
    int length = 0;
    for (int i = 0; i < path.size() - 1; ++i) {
        length += graph[path[i]][path[i + 1]];
        cout << "Дистанция между " << path[i] << " и " << path[i + 1] << " = " << graph[path[i]][path[i + 1]] << endl;
    }
    length += graph[path.back()][path[0]]; // Замкнуть путь
    cout << "Дистанция между " << path.back() << " и " << path[0] << " = " << graph[path.back()][path[0]] << endl;
    return length;
}

// Реализация алгоритма Кристофидиса
vector<int> christofides(const vector<vector<int>>& graph) {
    int n = graph.size();

    // Шаг 1: Построение минимального остовного дерева
    auto mstEdges = findMST(graph);

    // Шаг 2: Поиск нечётных вершин
    auto oddVertices = findOddDegreeVertices(mstEdges, n);

    // Шаг 3: Минимальное совершенное паросочетание
    auto matching = findMinPerfectMatching(oddVertices, graph);

    // Шаг 4: Построение эйлерова цикла
    auto eulerianCircuit = findEulerianCircuit(graph, mstEdges, matching);

    // Шаг 5: Преобразование в гамильтонов путь
    return makeHamiltonianPath(eulerianCircuit);
}

// Пример использования
int main() {
    setlocale(LC_ALL, "Russian");
    vector<vector<int>> graph = {
    {0, 10, 25, 20},
    {10, 0, 5, 25},
    {25, 5, 0, 300},
    {20, 25, 300, 0}
    };

    auto result = christofides(graph);

    cout << "Приближённый маршрут: ";
    for (int v : result) {
        cout << v << " ";
    }
    cout << endl;

    // Вычисление длины пути
    int pathLength = calculatePathLength(result, graph);
    cout << "Длина пути: " << pathLength << endl;

    return 0;
}

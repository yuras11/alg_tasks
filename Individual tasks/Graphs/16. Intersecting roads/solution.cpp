#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <fstream>

std::ifstream fin;
std::ofstream fout;

std::vector<long long> way;

void FillAdjacencyList(std::vector<std::vector<std::pair<long long, long long>>> &adjacencyList, const std::vector<long long> &U, const std::vector<long long> &V,
                       const std::vector<long long> &W)
{
    for (long long i = 1; i < U.size(); i++)
    {
        adjacencyList[U[i]].push_back(std::make_pair(V[i], W[i]));
        adjacencyList[V[i]].push_back(std::make_pair(U[i], W[i]));
    }
}

void Dijkstra(long long start, std::priority_queue<std::pair<long long, long long>> &queue, std::vector<bool> &processed,
              std::vector<long long> &dist, std::vector<std::vector<std::pair<long long, long long>>> &adjacencyList,
              long long finish, std::vector<long long> &prev)
{
    queue.push(std::make_pair(0, start));
    while (!queue.empty())
    {
        std::pair<long long, long long> pair = queue.top();
        queue.pop();
        long long dv = -pair.first;
        long long v = -pair.second;
        if (processed[v])
        {
            continue;
        }
        else
        {
            processed[v] = true;
            dist[v] = dv;
            long long u, cu;

            for (long long i = 0; i < adjacencyList[v].size(); i++)
            {
                u = adjacencyList[v][i].first;
                cu = adjacencyList[v][i].second;

                if (!processed[u] && (dv + cu + adjacencyList[u].size()) < dist[u])
                {
                    dist[u] = dv + cu + adjacencyList[u].size();
                    prev[u] = v;
                    queue.push(std::make_pair(-(dv + cu + adjacencyList[u].size()), -u));
                }
            }
        }
    }
}

void MakeTheWay(std::vector<long long> &prev, long long start, long long finish)
{
    long long index = finish;
    way.push_back(index);
    while (index != start && prev[index] != -1)
    {
        index = prev[index];
        way.push_back(index);
    }
}

//long long Count(std::vector<std::vector<std::pair<long long, long long>>> &adjacencyList)
//{
//    long long c = 0;
//    for (long long i = 1; i < way.size() - 1; i++)
//    {
//        c += adjacencyList[way[i]].size();
//    }
//    return c;
//}

int main()
{
    fin.open("input.in");
    long long N, K;
    fin >> N >> K;
    long long start, finish;
    fin >> start >> finish;
    std::vector<long long> U(K + 1, 0), V(K + 1, 0), W(K + 1, 0);
    for (long long i = 1; i <= K; i++)
    {
        fin >> U[i] >> V[i] >> W[i];
    }
    U[0] = LONG_LONG_MIN;
    V[0] = LONG_LONG_MIN;
    W[0] = LONG_LONG_MIN;
    fin.close();
    fout.open("output.out");
    std::vector<bool> processed(N + 1, false);
    std::priority_queue<std::pair<long long, long long>> queue;
    std::vector<long long> dist(N + 1, LONG_LONG_MAX);
    std::vector<std::vector<std::pair<long long, long long>>> adjacencyList(N + 1);
    FillAdjacencyList(adjacencyList, U, V, W);
    std::vector<long long> prev(N + 1, -1);
    Dijkstra(-start, queue, processed, dist, adjacencyList, finish, prev);
    MakeTheWay(prev, start, finish);
    std::reverse(way.begin(), way.end());

    fout << dist[finish] - adjacencyList[finish].size() << '\n';
    for (long long i = 0; i < way.size(); i++)
    {
        fout << way[i] << " ";
    }
    fout.close();
    return 0;
}

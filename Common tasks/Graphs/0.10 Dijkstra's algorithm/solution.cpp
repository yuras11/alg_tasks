#include <iostream>
#include <fstream>
#include <vector>
#include <queue>

std::ifstream fin;
std::ofstream fout;

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
              std::vector<long long> &dist, std::vector<std::vector<std::pair<long long, long long>>> &adjacencyList)
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

            for (long long i = 0; i < adjacencyList[v].size(); i++)
            {
                long long u = adjacencyList[v][i].first;
                long long cu = adjacencyList[v][i].second;
                if (!processed[u] && (dv + cu) < dist[u])
                {
                    queue.push(std::make_pair(-(dv + cu), -u));
                }
            }
        }
    }

}

int main()
{
    fin.open("input.txt");
    long long n, m;
    fin >> n >> m;
    std::vector<long long> U(m + 1, 0), V(m + 1, 0), W(m + 1, 0);
    for (long long i = 1; i <= m; i++)
    {
        fin >> U[i] >> V[i] >> W[i];
    }
    U[0] = LONG_LONG_MIN;
    V[0] = LONG_LONG_MIN;
    W[0] = LONG_LONG_MIN;
    fin.close();
    fout.open("output.txt");
    std::vector<bool> processed(n + 1, false);
    std::priority_queue<std::pair<long long, long long>> queue;
    std::vector<long long> dist(n + 1, LONG_LONG_MAX);
    std::vector<std::vector<std::pair<long long, long long>>> adjacencyList(n + 1);
    FillAdjacencyList(adjacencyList, U, V, W);
    Dijkstra(-1, queue, processed, dist, adjacencyList);
    fout << dist[n];
    fout.close();
    return 0;
}

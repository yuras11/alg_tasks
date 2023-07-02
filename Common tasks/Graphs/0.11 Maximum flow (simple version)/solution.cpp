#include <iostream>
#include <vector>

struct Edge
{
    long long source;
    long long target;
    long long capacity;
    long long flow;

    Edge() : source(LONG_LONG_MIN), target(LONG_LONG_MIN), capacity(LONG_LONG_MIN), flow(LONG_LONG_MIN){}

    Edge(long long source_, long long target_, long long capacity_, long long flow_) :
    source(source_), target(target_), capacity(capacity_), flow(flow_){}
};

std::vector<Edge> flowEdges;
std::vector<bool> visited;
std::vector<long long> pred;

void FillInAdjacencyList(std::vector<long long> &U, std::vector<long long> &V, std::vector<long long> &W,
                         std::vector<std::vector<std::pair<long long, long long>>> &adjacencyList)
{
    for (long long i = 1; i < U.size(); i++)
    {
        adjacencyList[U[i]].push_back(std::make_pair(W[i], V[i]));
        adjacencyList[V[i]].push_back(std::make_pair(0, U[i]));
    }
}

long long Available(long long index)
{
    return flowEdges[index].capacity - flowEdges[index].flow;
}

long long Target(long long index)
{
    return flowEdges[index].target;
}

long long Source(long long index)
{
    return flowEdges[index].source;
}


void FindPath(long long s, std::vector<std::vector<long long>> &network)
{
    visited[s] = true;
    for (auto e : network[s])
    {
        long long u = Target(e);
        if(!visited[u] && Available(e) > 0)
        {
            pred[u] = e;
            FindPath(u, network);
        }
    }
}

std::vector<long long> RestorePath(long long f)
{
    std::vector<long long> path;
    while (pred[f] != -1)
    {
        long long e = pred[f];
        path.push_back(e);
        f = Source(e);
    }
    return path;
}

long long PathCapacity(std::vector<long long> &path)
{
    long long min = Available(path[0]);
    for (auto edge : path)
    {
        min = std::min(min, Available(edge));
    }
    return min;
}

void Push(long long e, long long flow)
{
    flowEdges[e].flow += flow;
    flowEdges[e ^ 1].flow -= flow;
}

void PushPath(std::vector<long long> &path, long long flow)
{
    for (long long e : path)
    {
        Push(e, flow);
    }
}

void BuildNetwork(std::vector<std::vector<long long>> &network, std::vector<std::vector<std::pair<long long, long long>>> &adjacencyList)
{
    for (long long i = 1; i < adjacencyList.size(); i++)
    {
        for (auto pair : adjacencyList[i])
        {
            network[i].push_back(flowEdges.size());
            Edge edge1(i, pair.second, pair.first, 0);
            flowEdges.push_back(edge1);
            network[pair.second].push_back(flowEdges.size());
            Edge edge2(pair.second, i, 0, 0);
            flowEdges.push_back(edge2);
        }
    }
}

long long ReturnMaxFlow(long long s, long long f, std::vector<std::vector<long long>> &network)
{
    long long maxFlow = 0;

    while (true)
    {
        for (int i = 1; i < network.size(); i++)
        {
            visited[i] = false;
            pred[i] = -1;
        }

        FindPath(s, network);
        if (!visited[f])
        {
            break;
        }

        std::vector<long long> path = RestorePath(f);
        long long flow = PathCapacity(path);
        PushPath(path, flow);
        maxFlow += flow;
    }

    return maxFlow;
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    long long n, m;
    std::cin >> n >> m;
    std::vector<long long> U(m + 1, 0), V(m + 1, 0), W(m + 1, 0);
    U[0] = LONG_LONG_MIN;
    V[0] = LONG_LONG_MIN;
    W[0] = LONG_LONG_MIN;
    for (long long i = 1; i <= m; i++)
    {
        std::cin >> U[i] >> V[i] >> W[i];
    }

    for (long long i = 0; i <= n; i++)
    {
        visited.push_back(false);
        pred.push_back(-1);
    }
    std::vector<std::vector<std::pair<long long, long long>>> adjacencyList(n + 1, std::vector<std::pair<long long, long long>>());
    std::vector<std::vector<long long>> network(n + 1, std::vector<long long>());
    FillInAdjacencyList(U, V, W, adjacencyList);

    BuildNetwork(network, adjacencyList);
    std::cout << ReturnMaxFlow(1, n, network);

    return 0;
}

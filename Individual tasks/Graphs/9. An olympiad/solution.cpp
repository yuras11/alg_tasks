#include <iostream>
#include <vector>
#include <queue>
#include <fstream>

std::ifstream fin;
std::ofstream fout;

void BFS(int start, std::vector<std::vector<int>> &adjacencyMatrix, std::vector<bool> &visited)
{
    std::queue<int> queue;
    visited[start] = true;
    queue.push(start);
    while (!queue.empty())
    {
        int v = queue.front();
        queue.pop();
        for (int i = 1; i < visited.size(); i++)
        {
            if (adjacencyMatrix[v][i] && !visited[i])
            {
                visited[i] = true;
                queue.push(i);
            }
        }
    }
}

int main()
{
    fin.open("input.in");
    long long N;
    fin >> N;
    std::vector<std::vector<int>> adjacencyMatrix(N + 1, std::vector<int>(N + 1, 0));

    for (int i = 1; i <= N; i++)
    {
        for (int j = 1; j <= N; j++)
        {
            fin >> adjacencyMatrix[i][j];
        }
    }
    fin.close();
    fout.open("output.out");
    std::vector<bool> visited(N + 1, false);

    BFS(1, adjacencyMatrix, visited);
    bool flag = false;

    for (int i = 1; i < visited.size(); i++)
    {
        if (!visited[i])
        {
            flag = true;
            break;
        }
    }

    if (flag)
    {
        fout << "NO";
    }
    else
    {
        fout << "YES";
    }
    fout.close();
    return 0;
}

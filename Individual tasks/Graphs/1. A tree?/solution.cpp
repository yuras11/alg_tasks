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
    fin.open("input.txt");
    int N;
    int counter(0);
    fin >> N;
    std::vector<std::vector<int>> adjacencyMatrix(N + 1, std::vector<int>(N + 1, 0));

    for (int i = 1; i <= N; i++)
    {
        for (int j = 1; j <= N; j++)
        {
            fin >> adjacencyMatrix[i][j];
            if (adjacencyMatrix[i][j] == 1)
            {
                counter++;
            }
        }
    }
    counter >>= 1;
    fin.close();
    fout.open("output.txt");
    std::vector<std::vector<bool>> processed(N + 1, std::vector<bool>(N + 1, false));
    std::vector<bool> visited(N + 1, false);
    bool flag = false;
    BFS(1, adjacencyMatrix, visited);
    for (int i = 1; i < visited.size(); i++)
    {
        if (!visited[i])
        {
            flag = true;
            break;
        }
    }

    if (!flag)
    {
        if (counter == N - 1)
        {
            fout << "YES";
        }
        else
        {
            fout << "NO";
        }
    }
    else
    {
        fout << "NO";
    }
    fout.close();
    return 0;
}

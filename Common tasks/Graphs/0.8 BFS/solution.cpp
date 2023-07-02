#include <iostream>
#include <fstream>
#include <vector>
#include <queue>

std::ifstream fin;
std::ofstream fout;

int next_index = 1;

void BFS(int start, std::queue<int> &queue, std::vector<int> &orders, std::vector<std::vector<int>> &matrix, std::vector<bool> &visited)
{
    orders[start] = next_index;
    next_index++;
    visited[start] = true;
    queue.push(start);
    while (!queue.empty())
    {
        int v = queue.front();
        queue.pop();
        for (int i = 1; i < visited.size(); i++)
        {
            if (matrix[v][i] && !visited[i])
            {
                visited[i] = true;
                orders[i] = next_index;
                next_index++;
                queue.push(i);
            }
        }
    }
}


int main()
{
    fin.open("input.txt");
    int n;
    fin >> n;
    std::vector<std::vector<int>> adjacencyMatrix(n + 1, std::vector<int>(n + 1, 0));
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            fin >> adjacencyMatrix[i][j];
        }
    }
    fin.close();
    fout.open("output.txt");
    std::queue<int> queue;
    std::vector<int> orders(n + 1, 0);
    std::vector<bool> visited(n + 1, false);
    orders[0] = INT_MIN;
    BFS(1, queue, orders, adjacencyMatrix, visited);
    for (int i = 1; i < visited.size(); i++)
    {
        if (!visited[i])
        {
            BFS(i, queue, orders, adjacencyMatrix, visited);
        }
    }
    for (int i = 1; i < orders.size(); i++)
    {
        fout << orders[i] << " ";
    }

    fout.close();
    return 0;
}

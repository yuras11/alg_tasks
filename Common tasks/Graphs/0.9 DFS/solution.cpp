#include <iostream>
#include <fstream>
#include <vector>

std::ifstream fin;
std::ofstream fout;

int next_index = 1;

void DFS(int start, std::vector<int> &orders, std::vector<std::vector<int>> &matrix, std::vector<bool> &visited)
{
    visited[start] = true;
    orders[start] = next_index;
    next_index++;

    for (int i = 1; i < visited.size(); i++)
    {
        if (matrix[start][i] && !visited[i])
        {
            DFS(i, orders, matrix, visited);
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
    std::vector<int> orders(n + 1, 0);
    std::vector<bool> visited(n + 1, false);
    orders[0] = INT_MIN;
    DFS(1, orders, adjacencyMatrix, visited);
    for (int i = 1; i < visited.size(); i++)
    {
        if (!visited[i])
        {
            DFS(i, orders, adjacencyMatrix, visited);
        }
    }
    for (int i = 1; i < orders.size(); i++)
    {
        fout << orders[i] << " ";
    }

    fout.close();
    return 0;
}

#include <iostream>
#include <fstream>
#include <vector>

std::ifstream fin;
std::ofstream fout;

int main()
{
    fin.open("input.txt");
    long long n, m;
    fin >> n >> m;
    std::vector<long long> firstVertexes(m, 0), secondVertexes(m, 0);
    for (long long i = 0; i < m; i++)
    {
        fin >> firstVertexes[i] >> secondVertexes[i];
    }
    fin.close();
    fout.open("output.txt");
    std::vector<std::vector<long long>> adjacencyMatrix(n, std::vector<long long>(n, 0));
    for (long long i = 0; i < m; i++)
    {
        adjacencyMatrix[firstVertexes[i] - 1][secondVertexes[i] - 1] = 1;
        adjacencyMatrix[secondVertexes[i] - 1][firstVertexes[i] - 1] = 1;
    }
    for (long long i = 0; i < n; i++)
    {
        for (long long j = 0; j < n; j++)
        {
            fout << adjacencyMatrix[i][j] << " ";
        }
        fout << '\n';
    }
    fout.close();
    return 0;
}

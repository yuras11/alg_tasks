#include <iostream>
#include <fstream>
#include <vector>

std::ifstream fin;
std::ofstream fout;

int main()
{
    fin.open("input.txt");
    long long n;
    fin >> n;
    std::vector<std::vector<long long>> adjacencyMatrix(n, std::vector<long long>(n, 0));
    std::vector<long long> firstVertexes, secondVertexes;
    for (long long i = 0; i < n; i++)
    {
        for (long long j = 0; j < n; j++)
        {
            fin >> adjacencyMatrix[i][j];
        }
    }
    fin.close();
    fout.open("output.txt");
    for (long long i = 0; i < n; i++)
    {
        for (long long j = 0; j < n; j++)
        {
            if (adjacencyMatrix[i][j] == 1)
            {
                firstVertexes.push_back(i + 1);
                secondVertexes.push_back(j + 1);
            }
        }
    }
    std::vector<long long> P(n + 1, 0);
    P[0] = LONG_LONG_MIN;
    for (long long i = 0; i < firstVertexes.size(); i++)
    {
        long long index = secondVertexes[i];
        P[index] = firstVertexes[i];
    }
    for (long long i = 1; i <= n; i++)
    {
        fout << P[i] << " ";
    }
    fout.close();
    return 0;
}

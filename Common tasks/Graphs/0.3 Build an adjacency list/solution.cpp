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

    std::vector<std::vector<long long>> vertexes(n, std::vector<long long>());

    for (long long i = 0; i < m; i++)
    {
        vertexes[firstVertexes[i] - 1].push_back(secondVertexes[i]);
        vertexes[secondVertexes[i] - 1].push_back(firstVertexes[i]);
    }

    for (long long i = 0; i < n; i++)
    {
        fout << vertexes[i].size() << " ";
        if (vertexes[i].size() != 0)
        {
            for (long long j = 0; j < vertexes[i].size(); j++)
            {
                fout << vertexes[i][j] << " ";
            }
        }
        fout << '\n';
    }

    fout.close();
    return 0;
}

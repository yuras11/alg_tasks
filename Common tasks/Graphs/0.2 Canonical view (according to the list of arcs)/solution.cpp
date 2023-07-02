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
    std::vector<long long> firstVertexes(n - 1, 0), secondVertexes(n - 1, 0);
    for (long long i = 0; i < n - 1; i++)
    {
        fin >> firstVertexes[i] >> secondVertexes[i];
    }
    fin.close();
    fout.open("output.txt");
    std::vector<long long> P(n + 1, 0);
    P[0] = LONG_LONG_MIN;
    for (long long i = 0; i < n - 1; i++)
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

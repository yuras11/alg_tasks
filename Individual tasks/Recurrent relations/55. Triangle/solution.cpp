#include <iostream>
#include <fstream>
#include <vector>

std::ifstream fin;
std::ofstream fout;

long long returnMax(const std::vector<long long> &vec)
{
    long long max = vec[0];
    for (long long i = 1; i < vec.size(); i++)
    {
        if (max < vec[i])
        {
            max = vec[i];
        }
    }
    return max;
}


int main()
{
    fin.open("input.txt");
    long long k;
    fin >> k;
    std::vector<std::vector<long long>> triangle(k, std::vector<long long>());

    long long value;

    for (long long i = 0; i < k; i++)
    {
        for (long long j = 0; j < i + 1; j++)
        {
            fin >> value;
            triangle[i].push_back(value);
        }
    }
    fin.close();
    fout.open("output.txt");

    std::vector<std::vector<long long>> F(k, std::vector<long long>(k, 0));

    if (k == 1)
    {
        fout << triangle[0][0];
    }
    else if (k == 2)
    {
        F[0][0] = triangle[0][0];
        F[1][0] = triangle[0][0] + triangle[1][0];
        F[1][1] = triangle[0][0] + triangle[1][1];
        fout << std::max(F[1][0], F[1][1]);
    }
    else
    {
        F[0][0] = triangle[0][0];
        F[1][0] = triangle[0][0] + triangle[1][0];
        F[1][1] = triangle[0][0] + triangle[1][1];
        for (long long i = 2; i < k; i++)
        {
            F[i][0] = F[i-1][0] + triangle[i][0];
            for (long long j = 1; j < i + 1; j++)
            {
                F[i][j] = std::max(F[i-1][j-1], F[i-1][j]) + triangle[i][j];
            }
        }
        fout << returnMax(F[k-1]);
    }
    fout.close();
    return 0;
}

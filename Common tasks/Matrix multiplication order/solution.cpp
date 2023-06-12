#include <iostream>
#include <fstream>
#include <vector>

long long GetMinElement(std::vector<long long> &vector)
{
    long long min = vector[0];
    for (long long i = 0; i < vector.size(); i++)
    {
        if (min > vector[i])
        {
            min = vector[i];
        }
    }
    return min;
}

int main()
{
    long long amountOfMatrixes = 0;
    std::ifstream fin;
    std::ofstream fout;
    std::string inputPath = "input.txt";
    std::string outputPath = "output.txt";
    fin.open(inputPath);
    fin >> amountOfMatrixes;
    std::vector<long long> sizes;
    long long n = 0, m = 0;
    fin >> n;
    sizes.push_back(n);
    fin >> m;
    sizes.push_back(m);
    for (long long i = 2; i <= amountOfMatrixes; i++)
    {
        fin >> n;
        fin >> m;
        sizes.push_back(m);
    }
    fin.close();

    long long sizeOfF = sizes.size() - 1;

    std::vector<std::vector<long long>> F;
    F.reserve(sizeOfF);
    for (long long i = 0; i < sizeOfF; i++)
    {
        F.emplace_back();
    }
    for (long long i = 0; i < sizeOfF; i++)
    {
        for (long long j = 0; j < sizeOfF; j++)
        {
            F[i].push_back(0);
        }
    }


for (long long i = 0; i < sizeOfF; i++)
{
    F[i][i] = 0;
}
    for (long long i = 0; i < sizeOfF-1; i++)
    {
        F[i][i+1] = sizes[i] * sizes[i+1] * sizes[i+2];
    }

    std::vector<long long> elements;
    for (long long i = 1; i < sizeOfF; i++)
    {
        for (long long j = 0; j < sizeOfF-i; j++)
        {
            long long l = i + j;
            for (long long k = j; k < l; k++)
            {
                elements.push_back(F[j][k] + F[k+1][l] + sizes[j] * sizes[k+1] * sizes[l+1]);
            }
            F[j][l] = GetMinElement(elements);
            elements.clear();
        }
    }
    fout.open(outputPath);
    if(fout.is_open())
    {
        fout << F[0][sizeOfF-1];
    }
    fout.close();
    return 0;
}

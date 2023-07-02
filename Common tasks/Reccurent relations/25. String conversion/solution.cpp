#include <iostream>
#include <fstream>
#include <vector>

int delta(char x, char y)
{
    if (x != y)
    {
        return 1;
    }
    return 0;
}

int main()
{
    long long x = 0, y = 0, z = 0;
    std::string A, B;
    std::ifstream fin;
    std::ofstream fout;
    std::string inputPath = "in.txt";
    std::string outputPath = "out.txt";
    fin.open(inputPath);
    fin >> x;
    fin >> y;
    fin >> z;
    fin >> A;
    fin >> B;
    fin.close();
    fout.open(outputPath);
    long long n = A.size(), m = B.size();
    std::vector<std::vector<long long>> F(n + 1, std::vector<long long>(m + 1, 0));
    for (long long i = 1; i <= n; i++)
    {
        F[i][0] = i * x;
    }
    for (long long i = 1; i <= m; i++)
    {
        F[0][i] = i * y;
    }

    for (long long i = 1; i <= n; i++)
    {
        for (long long j = 1; j <= m; j++)
        {
            F[i][j] = std::min(std::min(F[i-1][j] + x, F[i][j-1] + y) , F[i-1][j-1] + delta(A[i-1], B[j-1])*z);
        }
    }
    fout << F[n][m];
    fout.close();
    return 0;
}

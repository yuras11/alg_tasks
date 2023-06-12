#include <iostream>
#include <vector>

const extern long long M = 1000000007;

long long Cnk(long long n, long long k, std::vector<std::vector<long long>> &F)
{

    for (int i = 0; i <= n; i++)
    {
        F[i][i] = 1;
        F[i][0] = 1;
    }
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= i-1; j++)
        {
            F[i][j] = (F[i-1][j-1]%M + F[i-1][j]%M)%M;
        }
    }
    return F[n][k];
}

int main()
{
    long long n, k;
    std::cin >> n >> k;
    std::vector<std::vector<long long>> F;
    F.reserve(n);
    for (int i = 0; i < n+1; i++)
    {
        F.emplace_back();
    }
    for (int i = 0; i < n+1; i++)
    {
        for (int j = 0; j < n+1; j++)
        {
            F[i].push_back(0);
        }
    }

    std::cout << Cnk(n, k, F)%M;
    return 0;
}

#include <iostream>

const extern long long M = 1000000007;

long long BinaryPow(long long number, long long power)
{
    long long result = 1;
    while (power != 0)
    {
        if (power % 2 == 0)
        {
            number = (number%M * number%M)%M;
            power >>= 1;
        }
        else
        {
            result = (result%M * number%M)%M;
            power--;
        }
    }
    return result%M;
}

int main()
{
    long long n = 0, k = 0;
    std::cin >> n >> k;
    long long m = n - k;
    long long N_fact = 1, K_fact = 1, M_fact = 1;
    long long n_ = n, m_ = m, k_ = k;

    while (n_ != 0)
    {
        N_fact = (N_fact%M * n_%M)%M;
        n_--;
    }
    while (m_ != 0)
    {
        M_fact = (M_fact%M * m_%M)%M;
        m_--;
    }
    while (k_ != 0)
    {
        K_fact = (K_fact%M * k_%M)%M;
        k_--;
    }
    std::cout << N_fact%M * BinaryPow(K_fact%M * M_fact%M, (M-2))%M;
}

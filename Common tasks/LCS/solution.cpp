#include <iostream>
#include <vector>

int main()
{
    unsigned int n;
    std::cin >> n;

    std::vector<unsigned int> A;
    std::vector<unsigned int> B;
    A.push_back(0);
    B.push_back(0);
    unsigned int element;
    for (int i = 0; i < n; i++)
    {
        std::cin >> element;
        A.push_back(element);
    }
    for (int i = 0; i < n; i++)
    {
        std::cin >> element;
        B.push_back(element);
    }

    std::vector<std::vector<unsigned int>> F;
    F.reserve(n + 1);
    for (int i = 0; i < n + 1; i++)
    {
        F.emplace_back();
    }
    for (int i = 0; i < n + 1; i++)
    {
        for (int j = 0; j < n + 1; j++)
        {
            F[i].push_back(0);
        }
    }

    for (unsigned int i = 1; i < n + 1; i++)
    {
        for (unsigned int j = 1; j < n + 1; j++)
        {
            if (A[i] == B[j])
            {
                F[i][j] = F[i - 1][j - 1] + 1;
            } else
            {
                F[i][j] = std::max(F[i - 1][j], F[i][j - 1]);
            }
        }
    }
    unsigned int k = F[n][n];

    if (k == 0)
    {
        std::cout << 0;
        return 0;
    }

    std::vector<unsigned int> I, J;

    unsigned int i = n, j = n;

    while (i > 0 && j > 0)
    {
        if (A[i] == B[j])
        {
            I.push_back(i - 1);
            J.push_back(j - 1);
            i--;
            j--;
        } else
        {
            if (F[i][j] == F[i - 1][j])
            {
                i--;
            }
            else
            {
                j--;
            }
        }
    }

        std::cout << k;
        std::cout << '\n';
        for (unsigned int l = k - 1; l > 0; l--)
        {
            std::cout << I[l] << " ";
        }
        std::cout << I[0];
        std::cout << '\n';
        for (unsigned int l = k - 1; l > 0; l--)
        {
            std::cout << J[l] << " ";
        }
        std::cout << J[0];

        return 0;
}

#include <iostream>
#include <vector>

void TheWayOfTheFrog(int n, std::vector<int> &F, std::vector<int>& waterLilies)
{
    waterLilies.push_back(n);
    int index = n;
    while (index != 1)
    {
        if(F[index - 2] > F[index - 3])
        {
            waterLilies.push_back(index-2);
            index -= 2;
        }
        else
        {
            waterLilies.push_back(index-3);
            index -= 3;
        }
    }
}

int main()
{
    int n = 0;
    std::cin >> n;
    if (n == 2)
    {
        std::cout << -1;
        return 0;
    }
    std::vector<int> waterLilies;
    std::vector<int> mosquitoes(n+1);
    for (int i = 0; i <= n; i++)
    {
        mosquitoes.push_back(0);
    }
    for (int i = 1; i <= n; i++)
    {
        std::cin >> mosquitoes[i];
    }

    std::vector<int> F(n+1);
    for (int i = 0; i <= n; i++)
    {
        F.push_back(0);
    }
    F[0] = INT_MIN;
    F[1] = mosquitoes[1];
    F[2] = INT_MIN;
    F[3] = F[1] + mosquitoes[3];
    for (int i = 3; i <= n; i++)
    {
        F[i] = std::max(F[i-2], F[i-3]) + mosquitoes[i];
    }
    std::cout << F[n];
    TheWayOfTheFrog(n, F, waterLilies);
    std::cout << '\n';
    for (int i = waterLilies.size() - 1; i > 0; i--)
    {
        std::cout << waterLilies[i] << " ";
    }
    std::cout << waterLilies[0];
    return 0;
}

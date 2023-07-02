#include <iostream>
#include <fstream>
#include <vector>

std::ifstream fin;
std::ofstream fout;

long long FindSum(const std::vector<long long> &vec)
{
    long long sum = 0;
    for (long long i : vec)
    {
        sum += i;
    }
    return sum;
}


int main()
{
    fin.open("input.txt");

    long long n, m, s;
    fin >> n >> m >> s;
    std::vector<long long> buyer, seller;

    long long value;
    for (long long i = 0; i < n; i++)
    {
        fin >> value;
        buyer.push_back(value);
    }
    for (long long i = 0; i < m; i++)
    {
        fin >> value;
        seller.push_back(value);
    }
    fin.close();
    fout.open("output.txt");
    long long buyerSum = FindSum(buyer), sellerSum = FindSum(seller);

    if (s > buyerSum)
    {
        fout << "No";
        return 0;
    }

    long long sumToReturn = buyerSum + sellerSum - s;

    std::vector<long long> allTheCoins;

    for (long long & i : buyer)
    {
        allTheCoins.push_back(i);
    }

    for (long long & i : seller)
    {
        allTheCoins.push_back(i);
    }

    long long sumOfAllCoins = FindSum(allTheCoins);
    std::vector<bool> F(sumOfAllCoins, false);
    F[0] = true;

    for (long long allTheCoin : allTheCoins)
    {
        for (long long j = sumOfAllCoins - allTheCoin; j >= 0; j--)
        {
            if (F[j])
            {
                F[j + allTheCoin] = true;
            }
        }
    }

    if (F[buyerSum - s])
    {
        fout << "Yes";
    }
    else
    {
        fout << "No";
    }
    fout.close();
    return 0;
}
